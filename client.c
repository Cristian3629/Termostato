#include <stdio.h>
#include <netinet/in.h> //htons()
#include <stdlib.h> //atoi()

#include "time.h"
#include "client.h"
#include "file.h"
#include "calculateTemp.h"


int getQuantity(int segundos, float velocidad){
  int diferencia = 60 - segundos;
  float cantidad = velocidad*diferencia;
  return (int)(cantidad + 0.5);
}

int obtenterTemperatura(file_t* file, char temperatura[5]){
  char hexa[5];
  unsigned short int buffer;
  int cantidadBytes = file_read(file,&buffer);
  //printf("Cantidad de bytes leidos:%d\n",cantidadBytes);
  buffer = htons(buffer);
  snprintf(hexa,sizeof(hexa),"%04X",buffer);
  calcular(hexa,temperatura);
  return cantidadBytes;
}

//tp client ip port id frencuencia time file
//   1      2   3    4    5        6   7
int client(int argc, char* argv[]){
  int cantArguments = 8;
  int timeArray[6]; //aca se guarda la hora,minuto y segundo
  char charTemperatura[5]; //aca se guarda el temperatura
  //comprobar cant parametros
  if (cantArguments != argc){
    printf("Tengo %d argumentos y espero %d argumentos\n",argc,cantArguments);
    return 1;
  }
  printf("Se entró correctamente a client y la cantidad de parametros ok\n");
  //Lectura
  file_t* file = file_open(argv[7],"rb");
  //la velocidad es mediciones por segundo
  int frecuencia = atoi(argv[5]);
  float velocidad = calcularVelocidad(frecuencia);
  printf("La velocidad es:%.2f\n",velocidad);
  //int velocidadInt = (int)velocidad;
  //parseo la hora y lo guardo en el array
  getHrMinSec(argv[6],&timeArray);
  int cantidad;
  int n = 0; //es el contador de datos que se enviaron

  printTime(&timeArray);
  cantidad = getQuantity(timeArray[5],velocidad);
  while(obtenterTemperatura(file,charTemperatura)){
    //envio la temperatura al socket
    n++;
    if (n == cantidad){
      //tengo que enviar un barra n
      printf("Enviando %d muestras\n",n);
      wait(&timeArray);
      printTime(&timeArray); //esto es para el proximo envio
      n = 0; //reinicio el contador;
      cantidad = getQuantity(timeArray[5],velocidad);
    }
    else{
      //envio un espacio;
    }
  }
  printf("Enviando %d muestras\n",n);
  //cierro conexion


  file_close(file);
  return 0;
}
