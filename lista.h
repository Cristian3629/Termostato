#ifndef LISTA_ENLAZADA_H
#define LISTA_ENLAZADA_H

#include <stdbool.h>
#include <stddef.h>
#include "nodo.h"



typedef struct lista lista_t;


//estas son las funciones que voy a utilizar

lista_t *lista_crear();
bool lista_insertar(lista_t *lista, float dato);
float lista_posicion(lista_t *lista,int posicion);
int getLargo(lista_t* lista);
void printList(lista_t* lista);
//estas son necesarias de forma interna
bool lista_esta_vacia(const lista_t *lista);
void lista_destruir(lista_t *lista);
void lista_borrar_primero(lista_t *lista);




#endif
