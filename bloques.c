/* Includes */
#include "fcntl.h"
#include "unistd.h"
/* Constantes */
#define BLOCKSIZE 1024;

/* Variables */
int descriptor;

int bmount(const char *camino){
    descriptor = open(camino, O_RDWR|O_CREAT, 0666);
    if (descriptor == -1){
        return descriptor;  // Error
    }else{
        return descriptor;    
    }
}

/* función para desmontar el dispositivo virtual*/
int bumount(){
    return close(descriptor);
}

int bwrite(unsigned int nbloque, const void *buf){
    int desp = nbloque*BLOCKSIZE;
    Iseek(descriptor,desp,SEEK_SET);
    if (write(descriptor,&buf,BLOCKSIZE)>=0){
        return -1;
    }
    return BLOCKSIZE;

}