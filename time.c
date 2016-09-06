#include <stdio.h> //printf() sscanf()
#include <time.h> //time()
//#include <stdlib.h> //atoi()
#include <unistd.h> //sleep()

//Este módulo se encarga de obtener la hora y si los segundos son igual a 0
//entonces por STDIN

// {año,mes,dia,hora,minutos,segundos}
//   0   1   2   3      4       5
void printTime(int (*list)[6]){
    fprintf(stderr,"%d.%02d.%02d-%02d:%02d:00 - ",(*list)[0],(*list)[1],(*list)[2],
    (*list)[3],(*list)[4]);
  }

int getHrMinSec(char* hora,int (*lista)[6]){
  int anio,mes,dia,hours,minutes,seconds;
  sscanf(hora,"%d.%d.%d-%d:%d:%d",&anio,&mes,&dia,&hours,&minutes,&seconds);
  (*lista)[0] = anio;
  (*lista)[1] = mes;
  (*lista)[2] = dia;
  (*lista)[3] = hours;
  (*lista)[4] = minutes;
  (*lista)[5] = seconds;
  return 0;
}


int incrementMinute(int (*lista)[6]){
  //printf("(*lista)[4]:%d\n",(*lista)[4]);
  if ((*lista)[4] < 59 ){
    (*lista)[4] = (*lista)[4] + 1 ;
    return 1;
  }else{
    (*lista)[4] = 0;
    return 0;
  }
}

int incrementHour(int (*lista)[6]){
  if ((*lista)[3] < 23){
    //printf("Sumo uno a la hora\n");
    (*lista)[3] = (*lista)[3] + 1;
    return 1;
  }else{
    (*lista)[3] = 0;
    //printf("La hora es cero\n");
    return 0;
  }
}

int incrementDay(int (*lista)[6]){
  //printf("Incremento dia\n");
  if ((*lista)[2] < 31){
    (*lista)[2] = (*lista)[2] + 1;
    return 1;
  }else{
    (*lista)[2] = 1;
    return 0;
  }
}

int wait(int (*lista)[6]){
  int cambioHora = 1;
  //printf("wait");
  (*lista)[5] = 0;
  if (incrementMinute(lista) == 0){
    cambioHora = incrementHour(lista);
  }
  if (cambioHora == 0){
    incrementDay(lista);
  }
  //printTime(lista);
  return 0;
}
