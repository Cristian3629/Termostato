#ifndef FILE_H
#define FILE_H


typedef struct file file_t;

//Funciones
file_t* file_open(char *direccion, char *modo);
int file_read(file_t *archivo, void* buffer);
int file_end(file_t *archivo);
int file_close(file_t *archivo);


#endif
