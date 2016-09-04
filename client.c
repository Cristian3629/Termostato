#include <stdio.h>
#include <netinet/in.h> //htons()
#include <stdlib.h> //atoi()

#include "time.h"
#include "client.h"
#include "file.h"
#include "calculateTemp.h"

//tp client ip port id frencuencia time file
//   1      2   3    4    5        6   7
int client(int argc, char* argv[]){
  int n = 0;
  int cantArguments = 8;
  unsigned short int buffer;
  char hexa[5];
  int timeArray[3]; //aca se guarda la hora,minuto y segundo

  //comprobar cant parametros
  if (cantArguments != argc){
    printf("Tengo %d argumentos y espero %d argumentos\n",argc,cantArguments);
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
  printf("La velocidad es:%d\n",calcularVelocidad(frecuencia));
  printf("El tiempo es %s\n",argv[6]);
  getHrMinSec(argv[6],&timeArray);
  file_close(file);
  return 0;
}
