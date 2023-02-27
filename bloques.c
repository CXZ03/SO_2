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

int bwrite()