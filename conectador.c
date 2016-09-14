#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 200112L
#endif

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "conectador.h"
#include <stdlib.h>
#include <string.h>

struct conectador{
	int descriptor_file;
};

void error(const char *msg){
    perror(msg);
    exit(1);
}

conectador_t* socket_conectador_init(int descriptor){
	conectador_t* conectador = malloc(sizeof(struct conectador));
	if (conectador != NULL) {
		conectador->descriptor_file = descriptor;
	}
	return conectador;
}

conectador_t* socket_conectador_create(){
	int fd_aux;
	fd_aux = socket(AF_INET,SOCK_STREAM,0);
	if (fd_aux == -1) {
		printf("Error crear socket\n");
		return NULL;
	}
	int enable = 1;
	if(setsockopt(fd_aux, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int))<0){
		error("setsockopt(SO_REUSEADDR) failed");
	}
	conectador_t* conectador = malloc(sizeof(struct conectador));
	if (conectador != NULL) {
		conectador->descriptor_file = fd_aux;
	}
	return conectador;
}



int socket_conectador_send(conectador_t *conectador, void *buffer,int longitud){
	int aux = 0; // Guardaremos el valor devuelto por send() */
	int leido = 0; // Número de caracteres leídos hasta el momento
	//aux es la cantidad de bytes que envie
	//longitud es la longitud del buffer
	while (leido < longitud){
		aux = send(conectador->descriptor_file, buffer,longitud-leido ,MSG_NOSIGNAL);
		if (aux > 0) {
			leido += aux;
		}else {
			if (aux < 0) {
				printf("Error al escribir\n");
				return -1; //por ahora mando sólo -1, después voy a identicar los errores
			}else{
				printf("Socket cerrado\n");
			}
		}
	}
	return 1;
}

int socket_conectador_receive(conectador_t *conect, void *buffer,int longitud){
	int aux = 0; // Guardaremos el valor devuelto por send() */
	int leido = 0; // Número de caracteres leídos hasta el momento
	//aux es la cantidad de bytes que envie
	//longitud es la longitud del buffer
	while (leido < longitud){
		aux = recv(conect->descriptor_file, buffer,longitud-leido, MSG_NOSIGNAL);
		if (aux > 0) {
			leido += aux;
		}else{
			if (aux < 0) {
				printf("Error al leer\n");
				return -1; //por ahora mando sólo -1, después voy a identicar los errores
			}else{
				//printf("Socket cerrado y envio -1\n");
				return -1;
			}
		}
	}
	return 1;
}


int socket_conectador_connect(conectador_t *conect, char *ip, int port){
	struct sockaddr_in addr;
	addr.sin_port = (unsigned long)port;
	inet_pton(AF_INET, ip , &(addr.sin_addr));
	addr.sin_family = AF_INET;
	int aux;

	aux = connect(conect->descriptor_file, (struct sockaddr*)&addr, sizeof(addr));
	if (aux == -1){
		return -1;
	}
	return 1;
}


int socket_conectador_close(conectador_t *conectador){
	shutdown(conectador->descriptor_file, SHUT_RDWR);
	close(conectador->descriptor_file);
	free(conectador);
	return 1;
}
