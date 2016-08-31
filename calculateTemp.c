#include <stdio.h> //printf()
#include <stdlib.h> //atoi()
#include <math.h> //pow()
#include <string.h>

//Este modulo se encarga de todo lo que respecta al calcula y validación de
//un temperatura recibida en notación hexadecimal


float tranformar(int temp){
  float tempf = (float)temp;
  printf("conversion:%f\n",tempf);
  return (0.1)*tempf - 17.0;
}

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
    //printf("Numero decimal : %d", numDecimal);
    return numDecimal;
}

float validarTemperatura(float anterior, float actual){
  if ((actual > -17.00) &&  (actual < 59.70)){
    return actual;
  }else{
    return anterior;
  }
}



int calcular(int argc, char *argv[]){
  printf("Argumento:%s\n",argv[1]);
  int num = conversionHexDec(argv[1]);
  float numTrans = tranformar(num);
  printf("Tranformacion de la temperatura:%f\n",tranformar(num));
  printf("Validacion:%f\n", validarTemperatura(0,numTrans));
  return 0;
}
