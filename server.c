#include "server.h"

//calcula el máximo de las temperaturas
void server_get_max(float* maxActual,float* num){
	if ((*num) > (*maxActual)){
		*maxActual = *num;
	}
}

//actualiza el mínimo de las temperaturas
void server_get_min(float* minActual, float* num){
	if((*num)<(*minActual)){
		*minActual = *num;
	}
}

float server_get_float(char* charFloat){
	return atof(charFloat);
}


void server_format_parameter(float* max,float* min,lista_t* list,int *cantidad){
	*max = -18.0;
	*min = 60.0;
	while(!lista_esta_vacia(list)){
		lista_borrar_primero(list);
	}
	*cantidad = 0;
}

void server_print_date(date_t* date,int resta){
	int year = date_get_year(date);
	int month = date_get_month(date);
	int day = date_get_day(date);
	printf("%d.%02d.%02d ",year,month,day-resta);
}

float server_calc_median(lista_t* lista){
	float mediana;
	if (getLargo(lista) % 2 == 0){
		float valor1 = lista_posicion(lista,getLargo(lista)/2);
		float valor2 = lista_posicion(lista,(getLargo(lista)/2) + 1);
		mediana = (valor1 + valor2)/2;
		mediana = mediana - 0.01;
	}else{
		mediana = lista_posicion(lista,getLargo(lista)/2 + 1);
	}
	return mediana;
}

void server_print_info(date_t* date,char* id,float* max,float* min,
	lista_t* lista,int* cantidadPorDia, int resta){
	float mediana = server_calc_median(lista);
	server_print_date(date,resta);
	printf("%s Max=%.1f Min=%.1f Mediana=%.1f Muestras=%d\n",id,*max,*min,mediana,
	*cantidadPorDia);
	server_format_parameter(max,min,lista,cantidadPorDia);
}



int server_detect_change_day(date_t* date,char* dateTime){
	int hour = date_get_hour(date);
	int minute = date_get_minute(date);
	return hour == 0 && minute == 0;
}

int server_prepare_connect(char *prt, conectador_t **conec, aceptador_t **acep){
	int cant_client = 10;
	int port_aux = atoi(prt);
	aceptador_t * acept_aux = socket_acept_create();
	if (acept_aux == NULL) {
		printf(" no obtuve el aceptador\n");
		return -1;}
	*acep = acept_aux;
	if(socket_acept_connect(acept_aux,port_aux ,cant_client,"127.0.0.1") == -1){
		printf(" no pude prepararme para conectarme\n");
		socket_acept_close(acept_aux);
		return -1;
	}
	if (socket_acept_accept(*acep, conec) == -1){
		printf(" no pude conectar\n");
		socket_acept_close(acept_aux);
		return -1;}
	return 1;
}

//la funcion receive devuelve -1 cuando la conexion se cierra
int server_receive_time(conectador_t* canal,char* time_char,int largo){
	int resultado = socket_conectador_receive(canal,time_char,largo);
	return resultado;
}

int server_free_memory(conectador_t *conect,aceptador_t* acept,char* hour){
	socket_conectador_close(conect);
	socket_acept_close(acept);
	free(hour);
	return 0;
}

//---------------Funcion principal--------------//
int server(int argc,char* argv[]){
  if (argc < 3) {
		printf("Falta argumentos\n");
		return -1;
	}
  conectador_t *canal;
	aceptador_t *aceptador;
  if (server_prepare_connect(argv[2],&canal,&aceptador) == -1){
		printf("No pude conectarme con el cliente\n");
		return -1;
	}
  //recibo el id del termostato
  char id_termostato[7] = "";
	socket_conectador_receive(canal,id_termostato,7);
  fprintf(stderr,"Recibiendo termostato. ID=%s\n", id_termostato);

	//variables para el tiempo
	int long_format_time = 20;
	char* time_char = malloc(sizeof(char)*long_format_time);


	//variables para la temperatura

	int long_format_temp = 6;
	char* temp_char = malloc(sizeof(char)*long_format_temp);
	int long_format_ident = 1;
	char* identificador = malloc(sizeof(char)*long_format_ident);

	//variables para la información a mostrar
	float max = -18.0;
	float min = 60.0;
	lista_t* lista = lista_crear();
	int cantidadPorMinuto = 0;
	int cantidadPorDia = 0;

	//aca voy guardado el date
	date_t* date = date_create_empty();
	float number;

	//recibo el date junto con las mediciones
	while (server_receive_time(canal,time_char,long_format_time) != -1){
		fprintf(stderr, "%s - ",time_char);
		date_set(date,time_char);
		if (server_detect_change_day(date,time_char)){
			server_print_info(date,id_termostato,&max,&min,lista,&cantidadPorDia,1);
		}
		strncpy(identificador," ",long_format_ident);
		while (strncmp(identificador," ",long_format_ident) == 0) {
			socket_conectador_receive(canal,temp_char,long_format_temp);
			number = server_get_float(temp_char);
			server_get_min(&min,&number);
			server_get_max(&max,&number);
			lista_insertar(lista,number);
			cantidadPorMinuto++;
			cantidadPorDia++;
			socket_conectador_receive(canal,identificador,long_format_ident);
		}
		//printf("");
		//printf("%s",identificador);
		fprintf(stderr,"Datos recibidos: %d\n",cantidadPorMinuto);
		//printf(,cantidadPorMinuto);
		cantidadPorMinuto = 0;
	}
	//refreshSum(&sumatoria,&number);
	server_print_info(date,id_termostato,&max,&min,lista,&cantidadPorDia,0);
	fprintf(stderr,"Termostato desconectado. ID=%s\n", id_termostato);

	//optimizar
	free(identificador);
	free(temp_char);
	lista_destruir(lista);
	date_destroit(date);
	server_free_memory(canal,aceptador,time_char);
  return 1;
}
