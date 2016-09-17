#ifndef CLIENT_H
#define CLIENT_H


#include <stdio.h> //printf()
#include <netinet/in.h> //htons()
#include <stdlib.h> //atoi()
#include <string.h> //srtlen()

#include "time.h"
#include "date.h"
#include "client.h"
#include "file.h"
#include "calculateTemp.h"
#include "conectador.h"


//Funciones

int client(int argc,char* argv[]);

#endif
