#ifndef CONECTADOR_H
#define CONECTADOR_H


typedef struct conectador conectador_t;


conectador_t* socket_conectador_init(int descriptor);
conectador_t* socket_conectador_create();
int socket_conectador_send(conectador_t *conectador, void *buffer,int longitud);
int socket_conectador_receive(conectador_t *conect, void *buffer,int longitud);
int socket_conectador_close(conectador_t *conectador);
int socket_conectador_connect(conectador_t *conectador, char *ip, int port);

#endif
