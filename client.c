#include <stdio.h>
#include <netinet/in.h> //htons()
#include <stdlib.h> //atoi()


#include "client.h"
#include "file.h"
#include "calculateTemp.h"

//tp client ip port id frencuencia time file
//   1      2   3    4    5        6   7
int client(int argc, char* argv[]){
  int n = 0;
  int cantidadDeArgumentos = 8;
  unsigned short int buffer;
  char hexa[5];
  //comprobar cant parametros
  if (cantidadDeArgumentos != argc){
    printf("Tengo %d argumentos y espero %d argumentos\n",argc,cantidadDeArgumentos);
    return 1;
  }
  printf("Se entró correctamente a client y la cantidad de parametros ok\n");

  //Lectura

  file_t* file = file_open(argv[7],"rb");
  //printf("archivo abierto correctamente\n");
  while (file_read(file,&buffer) != 0){
    n++;
    buffer = htons(buffer);
    //printf("%04x ",buffer);
    //sprintf(hexa,"%04x",buffer);
    snprintf(hexa,sizeof(hexa),"%04X",buffer);
    //printf("El valor de hexa:%s\n",hexa);
    calcular(hexa);
  }
  //printf("La cantidad de mediciones es:%d\n",n);
  //printf("La frecuencia es:%s\n",argv[7]);
  int frecuencia = atoi(argv[5]);
  //printf("La cantidad de mediciones por segundos:%d\n",calcularVelocidad(frecuencia));
  file_close(file);
  return 0;
}
