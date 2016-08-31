#include "file.h"
#include <stdlib.h> //malloc()
#include <stdio.h> //funciones de file

struct file{
	FILE* fd; //file descriptor
};

file_t* file_open(char *direccion, char *modo){
	file_t *file = malloc(sizeof(file_t));
	FILE* file_aux = fopen(direccion, modo);
	if (file_aux == NULL){
		printf("Is NULL");
		return NULL;
	}
	file->fd = file_aux;
	return file;
}

//cada vez que llamo a la función voy leyendo 5 bytes es decir una medición
int file_read(file_t *archivo, void* buffer){
	int num = (int)fread(buffer, sizeof(short int), 1, archivo->fd);
	return num;
}

int file_end(file_t *archivo){
	return feof(archivo->fd);
}


int file_close(file_t *archivo){
	fclose(archivo->fd);
	free(archivo);
	return 0;
}
