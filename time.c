#include <stdio.h> //printf() sscanf()
#include <time.h> //time()
//#include <stdlib.h> //atoi()
#include <unistd.h> //sleep()

//Este módulo se encarga de obtener la hora y si los segundos son igual a 0
//entonces por STDIN

// {año,mes,dia,hora,minutos,segundos}
//   0   1   2   3      4       5
void printTime(int (*lista)[6]){
    printf("%d.%d.%d-%02d:%02d:00 - ",(*lista)[0],(*lista)[1],(*lista)[2],(*lista)[3],
  (*lista)[4]);
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
  if ( (*lista)[4] < 59 ){
    (*lista)[4] = (*lista)[4] +1;
    return 1;
  }else{
    (*lista)[4] = 0;
    return 0;
  }
}

int incrementHour(int (*lista)[6]){
  if ((*lista)[3] < 23){
    (*lista)[3] = (*lista)[3] + 1;
    return 1;
  }else{
    (*lista)[3] = 0;
    return 0;
  }
}

int wait(int (*lista)[6]){
  (*lista)[5] = 0;
  if (!incrementMinute(lista)){
    incrementHour(lista);
  }
  //printTime(lista);
  return 0;
}
