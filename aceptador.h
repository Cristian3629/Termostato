#ifndef ACEPTADOR_H
#define ACEPTADOR_H


#include "conectador.h"

typedef struct aceptador aceptador_t;
//typedef struct conectador conectador_t;

aceptador_t* socket_acept_create();
int socket_acept_connect(aceptador_t *aceptador, int port, int cant, char *ip);
int socket_acept_accept(aceptador_t *aceptador, conectador_t ** conectador);
int socket_acept_close(aceptador_t *aceptador);

#endif
