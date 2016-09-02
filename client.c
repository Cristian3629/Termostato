#include <stdio.h>
#include <netinet/in.h> //htons()

#include "client.h"
#include "file.h"
#include "calculateTemp.h"


int client(int argc, char* argv[]){
  int n = 0;
  int cantidadDeArgumentos = 3;
  unsigned short int buffer;
  char hexa[5];
  //comprobar cant parametros
  if (cantidadDeArgumentos != argc){
    printf("La cantidad de argumentos no es la esperada\n");
    return 1;
  }
  printf("Se entró correctamente a client y la cantidad de parametros ok\n");

  //Lectura

  file_t* file = file_open(argv[2],"rb");
  while (file_read(file,&buffer) != 0){
    n++;
    buffer = htons(buffer);
    //printf("%04x ",buffer);
    //sprintf(hexa,"%04x",buffer);
    snprintf(hexa,sizeof(hexa),"%04X",buffer);
    //printf("El valor de hexa:%s\n",hexa);
    calcular(hexa);
  }
  printf("La cantidad de mediciones es:%d\n",n);
  file_close(file);
  return 0;
}
