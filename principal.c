#include <stdio.h> //printf()
#include <string.h> //strcmp()
#include <stdlib.h> //malloc()

#include "client.h"
#include "server.h"

//supongo que el segundo argumento es el nombre del archivo
int main(int argc, char *argv[]){
  if (strcmp(argv[1],"client") == 0){
    client(argc,argv);
  }
	if (strcmp(argv[1],"server") == 0){
    server(argc,argv);
  }
  return 0;
}
