#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "lista.h"
#include <assert.h>
#include "nodo.h"

struct nodo{
	float dato;
	nodo_t *referencia;
	};

// Crea un nodo.
nodo_t* crear_nodo(float dato,nodo_t *referencia){
	nodo_t *nuevo_nodo = malloc(sizeof(nodo_t));
	if (nuevo_nodo == NULL){
		return NULL;
		}
	nuevo_nodo->dato = dato;
	nuevo_nodo->referencia = referencia;
	return nuevo_nodo;
}

void set_dato_nodo(nodo_t* nodo,float dato_aux){
	nodo->dato = dato_aux;
	//printf("Cambiando el dato, ahora es:%f\n",nodo->dato);
}

void definir_referencia(nodo_t *nodo, nodo_t * nodo_referencia){
	nodo->referencia = nodo_referencia;
}

nodo_t* obtener_referencia(nodo_t *nodo){
	return nodo->referencia;
}

float obtener_dato(nodo_t *nodo){
	return nodo->dato;
}



// Destruye el nodo
void destruir_nodo(nodo_t *nodo){
	free(nodo);
}
