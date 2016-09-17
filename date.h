#ifndef DATE_H
#define DATE_H

#include <stdlib.h> //malloc()
#include <stdio.h> //printf() sscanf()

typedef struct date date_t;

//Funciones
date_t* date_create(char* date);
date_t* date_create_empty();
int date_destroit(date_t* date);
int date_set(date_t*date,char* date_chr);
//private
// int date_increment_minute(date_t* date);
// int date_increment_hour(date_t* date);
// int date_increment_day(date_t* date);
// void date_set_second(date_t* date);
//get
int date_get_year(date_t* date);
int date_get_month(date_t* date);
int date_get_day(date_t* date);
int date_get_hour(date_t* date);
int date_get_minute(date_t* date);
int date_get_second(date_t* date);

int date_increment(date_t* date);
void date_print(date_t* date);




#endif /*DATE_H*/
