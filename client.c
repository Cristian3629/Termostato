#include <stdio.h>

#include "client.h"


int client(int argc, char* argv[]){
  int cantidadDeArgumentos = 2;
  if (cantidadDeArgumentos != argc){
    printf("La cantidad de argumentos no es la esperada\n");
    return 1;
  }
  return 0;
}
