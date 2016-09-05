#include "client.h"


conectador_t* client_create(char *ip,char *puerto){
  printf("cliente_create\n");
  printf("ip:%s port:%s\n",ip,puerto);
	conectador_t *self = socket_conectador_create();
	int port = atoi(puerto);
  printf("el int del puerto es:%d\n",port);
	int aux = socket_conectador_connect(self,ip,port);
	if (aux == -1){
		printf("Error al conectar con el server\n");
		socket_conectador_close(self);
		return NULL;
	}
	return self;
}

int getQuantity(int segundos, float velocidad){
  int diferencia = 60 - segundos;
  float cantidad = velocidad*diferencia;
  return (int)(cantidad + 0.5);
}

int obtenterTemperatura(file_t* file, char temperatura[5]){
  char hexa[5] = "";
  unsigned short int buffer = 0;
  int cantidadBytes = file_read(file,&buffer);
  buffer = htons(buffer);
  snprintf(hexa,sizeof(hexa),"%04X",buffer);
  calcular(hexa,temperatura);
  return cantidadBytes;
}

//esta funcion se encarga de enviar todos los datos respecto al tiempo
int send_time(conectador_t* conectador,int (*list)[6],char* time_char,int cant){
  snprintf(time_char,cant,"%d.%d.%d-%d:%d:00",
  (*list)[0],(*list)[1],(*list)[2],(*list)[3],(*list)[4]);
  printf("time_char:%s\n",time_char);
  socket_conectador_send(conectador,time_char,cant);
  return 0;
}

int client_free_memory(file_t* file, conectador_t *conect,char* date){
	socket_conectador_close(conect);
	file_close(file);
  free(date);
	return 0;
}


//tp client ip port id frencuencia time file
//   1      2   3    4    5        6   7
int client(int argc, char* argv[]){
  int cantArguments = 8;
  int timeArray[6]; //aca se guarda la hora,minuto y segundo
  char charTemperatura[5]; //aca se guarda el temperatura
  //comprobar cant parametros
  if (cantArguments != argc){
    printf("Tengo %d argumentos y espero %d argumentos\n",argc,cantArguments);
    return 1;
  }
  printf("Se entró correctamente a client y la cantidad de parametros ok\n");

  // conectandome con el servidor
  conectador_t* conectador = client_create(argv[2],argv[3]);
  //envio mi nombre
  socket_conectador_send(conectador,argv[4],6);
  //Lectura
  file_t* file = file_open(argv[7],"rb");

  //la velocidad es mediciones por segundo
  int frecuencia = atoi(argv[5]);
  float velocidad = calcularVelocidad(frecuencia);

  //parseo la hora y lo guardo en el array
  getHrMinSec(argv[6],&timeArray);

  //envio la fecha y hora
  int long_format_time = 19;
	char* time_char = malloc(sizeof(char)*long_format_time);
  send_time(conectador,&timeArray,time_char,long_format_time);
  int cantidad;
  int n = 0; //es el contador de datos que se enviaron

  printTime(&timeArray);
  cantidad = getQuantity(timeArray[5],velocidad);
  while (obtenterTemperatura(file,charTemperatura)){
    //envio la temperatura al socket
    n++;
    if (n == cantidad){
      //tengo que enviar un barra n
      printf("Enviando %d muestras\n",n);
      wait(&timeArray);
      printTime(&timeArray); //esto es para el proximo envio
      n = 0; //reinicio el contador;
      cantidad = getQuantity(timeArray[5],velocidad);
    }else{
      //envio un espacio;
    }
  }
  printf("Enviando %d muestras\n",n);

  //cierro conexion
  client_free_memory(file,conectador,time_char);


  return 0;
}
