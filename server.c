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


int receive_time(conectador_t* canal,char* time_char){
	printf("El time_char ocupa:%d\n",(int)sizeof(*time_char));
	socket_conectador_receive(canal,time_char,19);
	return 0;
}

int server_free_memory(conectador_t *conect,aceptador_t* acept){
	socket_conectador_close(conect);
	socket_acept_close(acept);
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
	char time_char[19] = "";
	receive_time(canal,time_char);
	printf("El tiempo es:%s\n", time_char);
	server_free_memory(canal,aceptador);
  return 1;
}
