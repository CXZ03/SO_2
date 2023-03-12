
#include "bloques.h"

unsigned char buffer_memoria[BLOCKSIZE];

int main(int argc,char **argv){

    if (argc != 3)
    {
        fprintf(stderr, "Error de sintaxis. Sintaxis correcta: ./mi_mkfs <nombre del fichero> <numero de bloques>\n");
        return FALLO;
    }
    bmount(argv[1]);

    //Iniciar a 0 el buffer de memoria
    memset(buffer_memoria,0,BLOCKSIZE);

    //Bucle para inicializar a 0s el fichero
    for (size_t i = 0; i < atoi(argv[2]); i++)
    {
        bwrite(i,buffer_memoria); //No se que pasarle por parámetro
    }

    //Cerramos el fichero
    bumount();
    
}