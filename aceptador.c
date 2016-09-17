#include "aceptador.h"

#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
struct aceptador{
	int descriptor;
};


//--------------------------------------------------


aceptador_t* socket_acept_create(){
	int aux = socket(AF_INET,SOCK_STREAM,0);
	if (aux == -1) {
		printf("Error en crear socket aceptador");
		return NULL;
	}
	aceptador_t *aceptador = malloc(sizeof(aceptador_t));
	aceptador->descriptor = aux;
	return aceptador;
}



int socket_acept_connect(aceptador_t *acept, int port, int cant, char *ip){
	struct sockaddr_in address;
	//inet_pton(AF_INET,INADDR_ANY, &(address.sin_addr));
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = (unsigned long)port;
	address.sin_family = AF_INET;

	int yes=1;
	setsockopt(acept->descriptor,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(int));
	//aviso al sistema que asocie mi programa con el socket que abrí
	if (bind(acept->descriptor,(struct sockaddr *)&address,sizeof(address))==-1){
		printf("%d\n",errno);
		strerror(errno);
		printf("Error en bind()\n");
		return -1;
	}
	// aviso al sistema que ya puede empezar a reservar clientes, los encola
	if(listen(acept->descriptor,cant) == -1){
		printf("Error en listen()\n");
		return -1;
	}
	return 1;
}


int socket_acept_accept(aceptador_t *aceptador,conectador_t **conectador){
	int descriptor_comunicador = accept(aceptador->descriptor,NULL,NULL);
	if(descriptor_comunicador == -1){
		printf("Error en accept()\n");
	}
	*conectador = socket_conectador_init(descriptor_comunicador);
	return 1;
}


int socket_acept_close(aceptador_t *aceptador){
	shutdown(aceptador->descriptor,SHUT_RDWR);
	close(aceptador->descriptor);
	free(aceptador);
	return 1;
}
