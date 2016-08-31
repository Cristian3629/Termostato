#include <stdio.h> //printf()
#include <string.h> //strcmp()
#include <stdlib.h> //malloc()
#include <netinet/in.h> //htons()

#include "file.h"
#include "time.h"

//supongo que el segundo argumento es el nombre del archivo
int main(int argc, char *argv[]){
  int n = 0;
  unsigned short int buffer;
  char hexa[5];
  if (argc != 2){
    printf("La cantidad de argumentos no es la esperada\n");
    return 1;
  }

  char algo[3] = "AB";
  printf("La cantidad de bytes que ocupa algo es:%d\n",(int)sizeof(algo));
  if (strcmp(argv[1],"client") == 0){printf("Hola soy un cliente\n");}
	if (strcmp(argv[1],"server") == 0){printf("Hola soy un servidor\n");}
  file_t* file = file_open("values.dat","rb");
  //printf("El tamaño de buffer:%d\n", (int)sizeof(buffer));
  //printf("El tamaño de hexa:%d\n", (int)sizeof(hexa));
  while (file_read(file,&buffer) != 0){
    n++;
    buffer = htons(buffer);
    printf("%04x ",buffer);
    //sprintf(hexa,"%04x",buffer);
    snprintf(hexa,sizeof(hexa),"%04x",buffer);
    printf("El valor de hexa:%s\n",hexa);
  }
  printf("La cantidad de mediciones es:%d\n",n);
  file_close(file);
  return 0;
}