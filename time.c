#include <stdio.h> //printf() sscanf()
#include <time.h> //time()
//#include <stdlib.h> //atoi()
#include <unistd.h> //sleep()

//Este módulo se encarga de obtener la hora y si los segundos son igual a 0
//entonces por STDIN


void printTime(int (*lista)[3]){
  if ((*lista)[2] > 10){
    printf(" El tiempo actual es:%d:%d:%d\n",(*lista)[0],(*lista)[1],(*lista)[2]);
  }
  else{
    printf(" El tiempo actual es:%d:%d:0%d\n",(*lista)[0],(*lista)[1],(*lista)[2]);
  }
}

void getHrMinSec(char* hora,int (*lista)[3]){
  int hours,minutes, seconds;
  sscanf(hora,"%d:%d:%d",&hours,&minutes,&seconds);
  (*lista)[0] = hours;
  (*lista)[1] = minutes;
  (*lista)[2] = seconds;
  printTime(lista);
}


int incrementMinute(int (*lista)[3]){
  if ( (*lista)[1] < 59 ){
    (*lista)[1] = (*lista)[1] +1;
  }
  else{
    (*lista)[1] = 0;
  }
  return 0;
}


int incrementSeconds(int (*lista)[3] , int diferencia){
  (*lista)[2] = (*lista)[2] + diferencia;
  if ((*lista)[2] >= 60){
    (*lista)[2] = (*lista)[2] - 60;
  }
  return 0;
}


int wait(int (*lista)[3]){
  printf("Ingresando en wait\n");
  // time_t hora;
  // struct tm * horainfo;
  int diferencia = 60 - (*lista)[2];
  printf("diferencia:%d\n",diferencia);
  sleep(diferencia);
  // time(&hora);
  // horainfo = localtime(&hora);
  // //printf("Hora y Fecha: %s", asctime(horainfo));
  // printf("Enviando...");
  // printf("Hora y Fecha: %s", asctime(horainfo));
  // printf("Cantidad:10\n");
  incrementMinute(lista);
  incrementSeconds(lista,diferencia);
  printTime(lista);
  return 0;
}
