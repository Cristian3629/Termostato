#include "date.h"

//Este struct modela el la hora ingresada y que se manipula constantemente
struct date{
	int year,month,day,hour,minute,second;
};


//Pre:El char tiene formato yy.mm.dd-hh:mm:ss
//Post: Devuelve un date_t* con sus campos seteados
date_t* date_create(char* date_chr){
  date_t* date = malloc(sizeof(date_t));
  if (date == NULL){
    printf("Error create date_t\n");
    return NULL;
  }
  sscanf(date_chr,"%d.%d.%d-%d:%d:%d",&(date->year),&(date->month),&(date->day),
  &(date->hour),&(date->minute),&(date->second));
  return date;
}

date_t* date_create_empty(){
	date_t* date = malloc(sizeof(date_t));
  if (date == NULL){
    printf("Error create date_t\n");
    return NULL;
  }
	return date;
}

int date_set(date_t* date,char* date_chr){
	sscanf(date_chr,"%d.%d.%d-%d:%d:%d",&(date->year),&(date->month),&(date->day),
  &(date->hour),&(date->minute),&(date->second));
	return 0;
}

//Pre:Recibe un date_t*
//Post:Aumenta en 1 el minuto o lo lleva a 0 si son 60 minutos
static int date_increment_minute(date_t* date){
  if ( date->minute < 59 ){
    date->minute++;
    return 1;
  }else{
    date->minute = 0;
    return 0;
  }
}

//Pre:Recibe un date_t*
//Post:Aumenta en 1 la hora o lo lleva a 0 si son 24 horas
static int date_increment_hour(date_t* date){
  if (date->hour < 23){
    date->hour++;
    return 1;
  }else{
    date->hour = 0;
    return 0;
  }
}
//Pre:Recibe un date_t*
//Post:Aumenta en 1 el dia o lo lleva a 1 si 31 dias
static int date_increment_day(date_t* date){
  if (date->day < 31){
    date->day++;
    return 1;
  }else{
    date->day = 1;
    return 0;
  }
}

//Funcion no generica
//Pre:Recibe un date_t*
//Post:Setea los segundos a 0
static void date_set_second(date_t* date){
  date->second = 0;
}


//Pre:Recibe un date_t*
//Post:Aumenta en 1 el minuto y si corresponde la hora al igual que el dia
int date_increment(date_t* date){
  int cambioHora = 1; //false
  date_set_second(date);
  if (date_increment_minute(date)==0){
    cambioHora = date_increment_hour(date);
  }
  if (cambioHora == 0){
    date_increment_day(date);
  }
  return 0;
}

//Pre:Recibe un date_t*
//Post:Imprime por stdin el date con el siguiente formato
//yy.mm.dd-hh:mm:00
void date_print(date_t* date){
  fprintf(stderr,"%d.%02d.%02d-%02d:%02d:00 - ",date->year,date->month,date->day
  ,date->hour,date->minute);
}

//Pre:Recibe un date_t*
//Post:Devuelve el anio
int date_get_year(date_t* date){
	return date->year;
}
//Pre:Recibe un date_t*
//Post:Devuelve el mes
int date_get_month(date_t* date){
	return date->month;
}
//Pre:Recibe un date_t*
//Post:Devuelve el dia
int date_get_day(date_t* date){
	return date->day;
}
//Pre:Recibe un date_t*
//Post:Devuelve la hora
int date_get_hour(date_t* date){
	return date->hour;
}
//Pre:Recibe un date_t*
//Post:Devuelve los minutos
int date_get_minute(date_t* date){
	return date->minute;
}

int date_get_second(date_t* date){
	return date->second;
}
//Pre:Recibe un date_t*
//Post:Libera los recursos utilizado por date_t* y devuelvo 0
int date_destroit(date_t* date){
  free(date);
  return 0;
}
