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

  //la velocidad es mediciones por segundo
  int frecuencia = atoi(argv[5]);
  float velocidad = calcularVelocidad(frecuencia);
  printf("La velocidad es:%.0f\n",velocidad);
  //parseo la hora y lo guardo en el array
  getHrMinSec(argv[6],&timeArray);
  int diferencia = 60 - timeArray[2];
  int cantidad = (int)diferencia*velocidad;
  printf("Cantidad de datos a enviar:%d\n",cantidad);
  wait(&timeArray);
  diferencia = 60 - timeArray[2];
  cantidad = (int)diferencia*velocidad;
  printf("Cantidad de datos a enviar:%.0f\n",diferencia*velocidad);
  wait(&timeArray);
  diferencia = 60 - timeArray[2];
  cantidad = (int)diferencia*velocidad;
  printf("Cantidad de datos a enviar:%.0f\n",diferencia*velocidad);
  wait(&timeArray);
  diferencia = 60 - timeArray[2];
  cantidad = (int)diferencia*velocidad;
  printf("Cantidad de datos a enviar:%.0f\n",diferencia*velocidad);
  wait(&timeArray);
  diferencia = 60 - timeArray[2];
  cantidad = (int)diferencia*velocidad;
  printf("Cantidad de datos a enviar:%.0f\n",diferencia*velocidad);
  wait(&timeArray);
  file_close(file);
  return 0;
}
