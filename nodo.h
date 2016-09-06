#ifndef NODO_H
#define NODO_H

#include <stdlib.h>
#include <stdbool.h>

typedef struct nodo nodo_t;

// Crea un nodo.
nodo_t* crear_nodo(float dato,nodo_t *referencia);
nodo_t* obtener_referencia(nodo_t *nodo);
float obtener_dato(nodo_t *nodo);
void definir_referencia(nodo_t *nodo, nodo_t * nodo_referencia);
void set_dato_nodo(nodo_t* nodo,float dato);

// Destruye el nodo
void destruir_nodo(nodo_t *nodo);


#endif
