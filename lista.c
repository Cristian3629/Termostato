#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "lista.h"
#include <assert.h>
//#include "nodo.h"

struct lista{
	size_t largo;
	nodo_t* primero;
	nodo_t* ultimo;
	};

//------------------------------------------------------------------------------

lista_t *lista_crear(){
	lista_t *lista_nueva = malloc (sizeof(lista_t));
	if (lista_nueva == NULL){
		return NULL;
		}
	lista_nueva->primero = NULL;
	lista_nueva->ultimo = NULL;
	lista_nueva->largo = 0;
	return lista_nueva;
}


void printList(lista_t* lista){
	//printf("Imprimiendo la lista\n");
	nodo_t *nodo_actual = lista->primero;
	while (nodo_actual != NULL){
		float dato = obtener_dato(nodo_actual);
		printf("%f ",dato);
		nodo_actual = obtener_referencia(nodo_actual);
	}
	printf("\n");
}


void buscar(nodo_t* nodo_ant, nodo_t* nodo_sig,float dato){
	//printf("en buscar con:%f ",dato);
	if (nodo_sig == NULL){
		//printf("llegue al final ");
		float dato_act = obtener_dato(nodo_ant);
		if (dato <= dato_act){
			set_dato_nodo(nodo_ant,dato);
			//printf("dato_act:%f\n",dato_act);
			definir_referencia(nodo_ant,crear_nodo(dato_act,NULL));
			//printf("dato del nodo sa:%f\n",obtener_dato(nodo_ant));
		}else{
			definir_referencia(nodo_ant,crear_nodo(dato,NULL));
		}
	}else{
		//printf("not null\n");
		float num = obtener_dato(nodo_ant);
		if (dato <= num){
			set_dato_nodo(nodo_ant,dato);
			nodo_t* nuevo = crear_nodo(num,nodo_sig);
			definir_referencia(nodo_ant,nuevo);
		}else{
			buscar(nodo_sig,obtener_referencia(nodo_sig),dato);
		}
	}
}

int getLargo(lista_t* lista){
	return lista->largo;
}

bool lista_insertar(lista_t *lista, float dato){
	//printf("insertando el elemento:%.2f\n",dato);
	if (lista->largo == 0){
		//printf("lista vacia ");
		nodo_t *nuevo_nodo = crear_nodo(dato,NULL);
		if (nuevo_nodo != NULL){
			lista->primero = nuevo_nodo;
		}
	}else{
		buscar(lista->primero,obtener_referencia(lista->primero),dato);
	}
	lista->largo++;
	return true;
}

bool lista_esta_vacia(const lista_t *lista){
	return lista->primero == NULL;
}

//devuelvo -1 o la posicion donde se encuentra el dato
float lista_posicion(lista_t *lista,int posicion){
	nodo_t *nodo_actual = lista->primero;
	int posActual = 0;
	while (nodo_actual != NULL){
		if (posicion == posActual){
			return obtener_dato(nodo_actual);
		}else{
			nodo_actual = obtener_referencia(nodo_actual);
			posActual++;
		}
	}
	return 0;
	}



void lista_destruir(lista_t *lista){
	while (!lista_esta_vacia(lista)){
		lista_borrar_primero(lista);
	}
	free(lista);
}


void lista_borrar_primero(lista_t *lista){
	if (lista_esta_vacia(lista) == false){
		nodo_t* primero = lista->primero;
		//int dato_auxiliar = obtener_dato(primero);
		lista->primero = obtener_referencia(primero);
		if (lista->primero==NULL){
			lista->ultimo = NULL;
			}
		destruir_nodo(primero);
		lista->largo--;
	}
}
