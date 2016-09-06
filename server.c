#include "server.h"

//calcula el máximo de las temperaturas
void getMax(float* maxActual,float* num){
	if ((*num) > (*maxActual)){
		*maxActual = *num;
	}
}

//actualiza el mínimo de las temperaturas
void getMin(float* minActual, float* num){
	if((*num)<(*minActual)){
		*minActual = *num;
	}
}

//actualiza la sumatoria de todas las temperaturas
void refreshSum(float* sumatoria,float* num){
	*sumatoria = *sumatoria + *num;
}

float getFloat(char* charFloat){
	return atof(charFloat);
}


void formatParamaters(float* max,float* min,lista_t* list,int *cantidad){
	*max = -18.0;
	*min = 60.0;
	while(!lista_esta_vacia(list)){
		lista_borrar_primero(list);
	}
	//printf("formatParamaters");
	//printList(list);
	*cantidad = 0;
}

void printInfo(int (*list)[6],char* id,float* max,float* min,lista_t* lista,
int* cantidadPorDia){
	//int posicionMedio = getLargo(lista)/2;
	//printf("La posicion media es:%d\n",posicionMedio);
	float mediana = lista_posicion(lista,getLargo(lista)/2);
	printf("%d.%02d.%02d %s Max=%.1f Min=%.1f Mediana=%.1f Muestras=%d\n",
	(*list)[0],(*list)[1],(*list)[2]-1,id,*max,*min,mediana,*cantidadPorDia);
	//printf("Imprimi la lista\n");
	//printList(lista);
	formatParamaters(max,min,lista,cantidadPorDia);
}



int detectChangeDay(char* dateTime, int (*lista)[6]){
	getHrMinSec(dateTime,lista);
	return (*lista)[3] == 0 && (*lista)[4]==0;
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
int receive_time(conectador_t* canal,char* time_char,int largo){
	int resultado = socket_conectador_receive(canal,time_char,largo);
	//printf("resultado de receive_time:%d\n",resultado);
	return resultado;
}

int server_free_memory(conectador_t *conect,aceptador_t* acept,char* hour){
	socket_conectador_close(conect);
	socket_acept_close(acept);
	free(hour);
	return 0;
}


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
  char id_termostato[6] = "";
	socket_conectador_receive(canal,id_termostato,6);
  printf("Recibiendo termostato. ID=%s\n", id_termostato);

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
	int arrayTime[6]; //aca voy guardado el date
	float number;
	//recibo el date junto con las mediciones
	while (receive_time(canal,time_char,long_format_time) != -1){
		fprintf(stderr, "%s - ",time_char);
		//printf("%s - ", time_char);
		if (detectChangeDay(time_char,&arrayTime)){
			//printf("Hay cambio de dia\n");
			printInfo(&arrayTime,id_termostato,&max,&min,lista,&cantidadPorDia);
		}
		strncpy(identificador," ",long_format_ident);
		while (strncmp(identificador," ",long_format_ident) == 0) {
			socket_conectador_receive(canal,temp_char,long_format_temp);
			number = getFloat(temp_char);
			//printf("El numero flotante es:%f-", number);
			getMin(&min,&number);
			getMax(&max,&number);
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
	printInfo(&arrayTime,id_termostato,&max,&min,lista,&cantidadPorDia);
	printf("Termostato desconectado. ID=%s\n", id_termostato);
	free(identificador);
	free(temp_char);
	lista_destruir(lista);

	server_free_memory(canal,aceptador,time_char);
  return 1;
}
