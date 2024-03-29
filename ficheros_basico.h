
//Includes
#include "bloques.h"
#include "limits.h"

//Define
#define posSB 0 // el superbloque se escribe en el primer bloque de nuestro FS
#define tamSB 1
#define INODOSIZE 128 //tamaño en bytes de un inodo

#define NPUNTEROS (BLOCKSIZE / sizeof(unsigned int))   // 256 punteros por bloque
#define DIRECTOS 12
#define INDIRECTOS0 (NPUNTEROS + DIRECTOS)    // 268
#define INDIRECTOS1 (NPUNTEROS * NPUNTEROS + INDIRECTOS0)    // 65.804
#define INDIRECTOS2 (NPUNTEROS * NPUNTEROS * NPUNTEROS + INDIRECTOS1) // 16.843.020

struct superbloque{
unsigned int posPrimerBloqueMB;         //Posicion absoluta del primer bloque del mapa de bits
  unsigned int posUltimobloqueMB;       //Posicion absoluta del ultimo bloque del mapa de bits
  unsigned int posPrimerBloqueAI;       //Posicion absoluta del primer bloque de array de inodos
  unsigned int posUltimoBloqueAI;       //Posicion absoluta del ultimo bloque de array de inodos
  unsigned int posPrimerBloqueDatos;    //Posicion absoluta del primer bloque de datos
  unsigned int posUltimoBloqueDatos;    //Posicion absoluta del ultimo bloque de datos
  unsigned int posInodoRaiz;            //Posicion del inodo del directorio raiz (relativa al AI)
  unsigned int posPrimerInodoLibre;     //Posicion del primer inodo libre (relativa al AI)
  unsigned int cantBloquesLibres;       //Cantidad de bloques libres (en todo el disco)
  unsigned int cantInodosLibres;        //Cantidad de inodos libres (en el AI)
  unsigned int totBloques;              //Cantidad total de bloques en el disco
  unsigned int totInodos;               //Cantidad total de inodos (heuristica)
  char padding[BLOCKSIZE-12*sizeof(unsigned int)]; //Relleno para ocupar el bloque completo
};

struct inodo{
    unsigned char tipo; //Tipo('l':libre, 'd':directorio o 'f': fichero)
    unsigned char permisos; //Permisos (lectura y/o escritura y/o ejecucion)

    unsigned char reservado_alineacion1[6];

    time_t atime;   //Fecha y hora del ultimo acceso a datos
    time_t mtime;   //Fecha y hora de la ultima modificacion de datos
    time_t ctime;   //Fecha y hora de la ultima modificacion de inodo

    unsigned int nlinks;    //Cantidad de enlaces de entrada en directorio
    unsigned int tamEnBytesLog; //Tamaño en bytes logicos (EOF)
    unsigned int numBloquesOcupados;    //Cantidad de bloques ocupados zona de datos

    unsigned int punterosDirectos[12];  //12 punteros a bloques directos
    unsigned int punterosIndirectos[3]; /*3 punteros a bloques indirectos:
    1 indirecto simple, 1 indirecto doble, 1 indirecto triple */

    char padding[INODOSIZE - 2*sizeof(unsigned char)- 3*sizeof(time_t)-18*sizeof(unsigned int)-6*sizeof(unsigned char)];
};