#include <stdio.h> //printf() sscanf()
#include <time.h> //time()
//#include <stdlib.h> //atoi()
#include <unistd.h> //sleep()

//Este módulo se encarga de obtener la hora y si los segundos son igual a 0
//entonces por STDIN


void printTime(int (*lista)[3]){
    printf("El tiempo actual:%02d:%02d:00\n",(*lista)[0],(*lista)[1]);
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
  //printf("El año es:%d mes:%d dia:%d\n",anio,mes,dia);
  //printTime(lista);
  return 0;
}


int incrementMinute(int (*lista)[3]){
  if ( (*lista)[1] < 59 ){
    (*lista)[1] = (*lista)[1] +1;
    return 1;
  }else{
    (*lista)[1] = 0;
    return 0;
  }
}

int incrementHour(int (*lista)[3]){
  if ((*lista)[0] < 23){
    (*lista)[0] = (*lista)[0] + 1;
    return 1;
  }else{
    (*lista)[0] = 0;
    return 0;
  }
}

int wait(int (*lista)[3]){
  (*lista)[2] = 0;
  if (!incrementMinute(lista)){
    incrementHour(lista);
  }
  printTime(lista);
  return 0;
}
