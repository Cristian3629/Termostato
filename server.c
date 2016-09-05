#include "server.h"


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
	printf("resultado de receive_time:%d\n",resultado);
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
	int long_format_time = 19;
	char* time_char = malloc(sizeof(char)*long_format_time);


	//variables para la temperatura
	int cantidad = 0;
	int long_format_temp = 6;
	char* temp_char = malloc(sizeof(char)*long_format_temp);
	int long_format_ident = 1;
	char* identificador = malloc(sizeof(char)*long_format_ident);


	//recibo el date junto con las mediciones
	while (receive_time(canal,time_char,long_format_time) != -1){
		printf("%s - ", time_char);
		strncpy(identificador," ",long_format_ident);
		while (strncmp(identificador," ",long_format_ident) == 0) {
			socket_conectador_receive(canal,temp_char,long_format_temp);
			//recibo la temperatura
			cantidad++;
			printf("%s", temp_char);
			//printf("%s",identificador);
			printf(" ");
			//recibo el identificador
			socket_conectador_receive(canal,identificador,long_format_ident);
		}
		printf("\n");
		//printf("%s",identificador);
		printf("Datos recibidos: %d ",cantidad);
		cantidad = 0;
	}
	printf("Termostato desconectado. ID=%s\n", id_termostato);
	free(identificador);
	free(temp_char);


	server_free_memory(canal,aceptador,time_char);
  return 1;
}
