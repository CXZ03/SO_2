#include <stdio.h>  //printf(), fprintf(), stderr, stdout, stdin
#include <fcntl.h> //O_WRONLY, O_CREAT, O_TRUNC
#include <sys/stat.h> //S_IRUSR, S_IWUSR
#include <stdlib.h>  //exit(), EXIT_SUCCESS, EXIT_FAILURE, atoi()
#include <unistd.h> // SEEK_SET, read(), write(), open(), close(), lseek()
#include <errno.h>  //errno
#include <string.h> // strerror()
#include "bloques.h"

unsigned char buffer_memoria[BLOCKSIZE];

int main(int argc,char **argv){
    bmount(/*Nombre fichero*/);
    //Iniciar a 0 el buffer de memoria
    memset(buffer_memoria,0,BLOCKSIZE);
    //Bucle para inicializar a 0s el fichero
    for (size_t i = 0; i < atoi(argv[2]); i++)
    {
        bwrite(,buffer_memoria); //No se que pasarle por parámetro
    }

    //Cerramos el fichero
    bumount();
    
}