#include "client.h"

//Este archivo representa todo el comportamiento del cliente, desde leer
//el archivo hasta enviar al server con cierta frecuencia las medidas tomadas

//Pre:Recibe un direccion ip valida la igual con un puerto de formato valido
//Post: Devuelve un conectador que se utilizara para comunicarse con el server
conectador_t* client_create(char *ip,char *puerto){
	conectador_t *self = socket_conectador_create();
	int port = atoi(puerto);
  //printf("el int del puerto es:%d\n",port);
	int aux = socket_conectador_connect(self,ip,port);
	if (aux == -1){
		printf("Error al conectar con el server\n");
		socket_conectador_close(self);
		return NULL;
	}
	return self;
}

//Pre:Recibe cuantos segundos falta para el cambio de minuto y la frecuencia
//Post:Devuelve la cantidad de datos a enviar en los segundos restantes
int client_get_quantity(date_t* date, float velocidad){
  int diferencia = 60 - date_get_second(date);
  float cantidad = velocidad*diferencia;
  return (int)(cantidad + 0.5);
}

//Pre:El archivo se abrio de manera correcta, se recibe un temperatura en
//decimal y el largo corresponde a...

int client_get_temp(file_t* file, char temperatura[5], int largo){
  char hexa[5] = "";
  unsigned short int buffer = 0;
  int cantidadBytes = file_read(file,&buffer);
  buffer = htons(buffer);
  snprintf(hexa,sizeof(hexa),"%04X",buffer);
  calcular(hexa,temperatura,largo);
  return cantidadBytes;
}

//Pre:esta funcion se encarga de enviar todos los datos respecto al tiempo
//correspondiente
//Post:devuelve 0 si salio todo ok
int client_send_time(conectador_t* conectador,date_t* date,char* time_char,int cant){
	int year = date_get_year(date);
	int month = date_get_month(date);
	int day = date_get_day(date);
	int hour = date_get_hour(date);
	int minute = date_get_minute(date);
	snprintf(time_char,cant,"%d.%02d.%02d-%02d:%02d:00",year,month,day,hour,minute);
  socket_conectador_send(conectador,time_char,cant);
  return 0;
}

int client_validate_temperature(char* charMedicion){
	float medicion = atof(charMedicion);
	return (medicion > -17.0 || medicion < 59.7);
}

int client_free_memory(file_t* file, conectador_t *conect,date_t* date){
	socket_conectador_close(conect);
	file_close(file);
	date_destroit(date);
	return 0;
}


//--------------------------FUNCION PRINCIPAL----------------------------

//tp client ip port id frencuencia time file
//   1      2   3    4    5        6   7
int client(int argc, char* argv[]){
  int cantArguments = 8;
	char charAnterior[6] = "0.0";
  char charTemperatura[6] = ""; //aca se guarda el temperatura

  //comprobar cant parametros
  if (cantArguments != argc){
    printf("Tengo %d argumentos y espero %d argumentos\n",argc,cantArguments);
    return 1;
  }

  // conectandome con el servidor
  conectador_t* conectador = client_create(argv[2],argv[3]);

  //envio mi nombre
  socket_conectador_send(conectador,argv[4],7);

	//Lectura
  file_t* file = file_open(argv[7],"rb");

  //la velocidad es mediciones por segundo
  int frecuencia = atoi(argv[5]);
  float velocidad = calcularVelocidad(frecuencia);

  //parseo la hora y lo guardo en date_t
	date_t *date = date_create(argv[6]);
  //getHrMinSec(argv[6],&timeArray);

  //variables para el envio la fecha y hora
  int long_format_time = 20;
	char* time_char = malloc(sizeof(char)*long_format_time);

  int char_tem_long = 6;
  int cantidad;
  int n = 0; //es el contador de datos que se enviaron
  char espacio[] = " "; //se utiliza para indicar que hay datos por enviar
  char barraN[] = "\n"; //se utiliza para indicar que ya no hay datos
  int long_identificador = 1;
  int hayMediciones; //es para indicar si hay mediciones disponibles

  //printTime(&timeArray);
	date_print(date);
  //envio el date
  client_send_time(conectador,date,time_char,long_format_time);
  //calculo cantidad de datos a enviar
  cantidad = client_get_quantity(date,velocidad);
  hayMediciones = client_get_temp(file,charTemperatura,char_tem_long);
  while (hayMediciones){
		if (!client_validate_temperature(charTemperatura)){
			socket_conectador_send(conectador,charAnterior,char_tem_long);
		}else{
			socket_conectador_send(conectador,charTemperatura,char_tem_long);
			strncpy(charAnterior,charTemperatura,6);
		}
    n++;
    //si ya envie la cantidad correspondiente
    hayMediciones = client_get_temp(file,charTemperatura,char_tem_long);
    if (n == cantidad || !hayMediciones){
      socket_conectador_send(conectador,barraN,long_identificador);
      fprintf(stderr,"Enviando %d muestras\n",n);
      date_increment(date);
      if (hayMediciones){
        date_print(date); //esto es para el proximo envio
        client_send_time(conectador,date,time_char,long_format_time);
      }
      n = 0; //reinicio el contador;
      cantidad = client_get_quantity(date,velocidad);
    }else{
      socket_conectador_send(conectador,espacio,long_identificador);
    }
  }
  socket_conectador_send(conectador,barraN,long_identificador);

	//es envio todo, cierro conexion
	free(time_char);
  client_free_memory(file,conectador,date);


  return 0;
}
