#include <stdio.h> //printf()
#include <stdlib.h> //atoi()
#include <math.h> //pow()
#include <string.h>

//Este modulo se encarga de todo lo que respecta al calcula y validación de
//un temperatura recibida en notación hexadecimal


//Pre:recibe un int que representa el milli-sec­time-­step
//Post:Devuelve la frecuencia de mediciones por segundo
float calcularVelocidad(int frecuencia){
  return 1000.0/frecuencia;
  }


//Pre:Recibe un int que representa el numero en sistema decimal
//Post:Devuelve un float con la transformacion aplicada
float tranformar(int temp){
  float tempf = (float)temp;
  return (0.1)*tempf - 17.0;
}

//Pre:Recibe un char que es un hexadecimal
//Post:Devuelve un entero con el numero en hexadecimal pasado a decimal
int conversionHexDec(char* hexadecimal) {
    int numDecimal = 0;
    char hexDigitos[16]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D'
    ,'E','F'};
    int i, j;
    int potencia = 0; // potencia a la que se eleva el numero 16

    /* Converting hexadecimal number to decimal number */
    for (i = strlen(hexadecimal)-1; i >= 0; i--) {
        for (j = 0; j < 16; j++){
            if (hexadecimal[i] == hexDigitos[j]){
                numDecimal += j*pow(16, potencia);
            }
        }
        potencia++;
    }
    return numDecimal;
}

//Punto de entrada a este modulo, donde dado el numero en hexa, se devuelve
//el numero en decimal
//Pre:Recibe 2 cadena,una representa el hexadecimal leido del archivo y el otro
//es donde se guarda la temperatura
//Post:Devuelve 0 si todo salio ok 
int calcular(char hexa[5],char temp[5],int largo){
  int num = conversionHexDec(hexa);
  float numTrans = tranformar(num);
  snprintf(temp,largo,"%.2f",numTrans);
  return 0;
}
