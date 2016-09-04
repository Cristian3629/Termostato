#include <stdio.h> //printf() sscanf()
#include <time.h> //time()
//#include <stdlib.h> //atoi()
#include <unistd.h> //sleep()

//Este módulo se encarga de obtener la hora y si los segundos son igual a 0
//entonces por STDIN


void printTime(int (*lista)[3]){
  if ((*lista)[2] > 10){
    printf("El tiempo actual:%d:%d:%d\n",(*lista)[0],(*lista)[1],(*lista)[2]);
  }else{
    printf("El tiempo actual:%d:%d:0%d\n",(*lista)[0],(*lista)[1],(*lista)[2]);
  }
  }

int getHrMinSec(char* hora,int (*lista)[3]){
  int hours,minutes, seconds;
  int mes,dia,anio;
  //char tiempo[10] = "";
  //char hora_char[8] = "";
  //sscanf(hora,"%s-%s",tiempo,hora_char);
  //printf("Fecha:%s hora:%s\n",tiempo,hora_char);
  sscanf(hora,"%d.%d.%d-%d:%d:%d",&anio,&mes,&dia,&hours,&minutes,&seconds);
  (*lista)[0] = hours;
  (*lista)[1] = minutes;
  (*lista)[2] = seconds;
  printf("El año es:%d mes:%d dia:%d\n",anio,mes,dia);
  printTime(lista);
  return 0;
}


int incrementMinute(int (*lista)[3]){
  if ( (*lista)[1] < 59 ){
    (*lista)[1] = (*lista)[1] +1;
  }else{
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
