#include <ficheros_basico.h>

#define DEBUG3 1

int bw = 0;

/*
*   Funcion tamMB()
*   Calcula la cantidad de bloques que necesitara el mapa de bits
*   Input: nbloques = num de bloques del disco
*   Output: tamaño del mapa de bits en bloques
*/

int tamMB(unsigned int nbloques)
{
if (((nbloques/8) % BLOCKSIZE) == 0)
{
    return (nbloques/8)/BLOCKSIZE;
}
else
{
    return ((nbloques/8) / BLOCKSIZE)+1;
}
}

/*
*   Funcion tamAI()
*   Calcula la cantidad de bloques necesaria para la array de inodos
*   Input: ninodos = num de inodos
*   Output: tamaño de la array de inodos en bloques
*/
int tamAI(unsigned int ninodos){
    if (((ninodos*INODOSIZE) % BLOCKSIZE) == 0)
    {
        return (ninodos*INODOSIZE)/BLOCKSIZE;
    }
    else
    {
        return ((ninodos*INODOSIZE)/BLOCKSIZE)+1;
    }    
}

int initSB(unsigned int nbloques, unsigned int ninodos){
    struct superbloque SB;
    SB.posPrimerBloqueMB = posSB + tamSB;
    SB.posUltimobloqueMB = SB.posPrimerBloqueMB + tamMB(nbloques) - 1;
    SB.posPrimerBloqueAI = SB.posUltimobloqueMB + 1;
    SB.posUltimoBloqueAI = SB.posPrimerBloqueAI + tamAI(ninodos) -1;
    SB.posPrimerBloqueDatos = SB.posUltimoBloqueAI + 1;
    SB.posUltimoBloqueDatos = nbloques -1;
    SB.posInodoRaiz = 0;
    SB.cantBloquesLibres = nbloques;
    SB.cantInodosLibres = ninodos;
    SB.totBloques = nbloques;
    SB.totInodos = ninodos;
    
   if (bwrite(posSB, &SB) == FALLO)
   {
    return FALLO;
   }

    return EXITO;
}

/*
*   Funcion: initMB()
*   Inicializa el mapa de bits
*   Input:  None
*   Output: EXITO = 0: sin errores
*           FALLO = -1: error en la ejecucion
*/
int initMB(){
    
    unsigned char buffer[BLOCKSIZE];

    if (memset(buffer, 0, BLOCKSIZE) == NULL)
    {
        return FALLO;
    }
    
    struct superbloque SB;
    if (bread(posSB, &SB) == FALLO)
    {
        return FALLO;
    }

    for(int i = 0; i <= SB.posUltimoBloqueAI; i++)
    {
        if (escribir_bit(i, 1) == FALLO)
        {
            return FALLO;
        }
    }
    SB.cantBloquesLibres = SB.cantBloquesLibres - (SB.posUltimoBloqueAI + 1);
    bw = bwrite(posSB, &SB);
    if (bw < 0)
    {
        return FALLO;
    }
    return EXITO;
}

int initAI()
{

unsigned char buffer[BLOCKSIZE];

if (memset(buffer, 0, BLOCKSIZE) == NULL)
{
    return FALLO;
}

struct inodo inodos[BLOCKSIZE/INODOSIZE];
struct superbloque SB;

if (bread(posSB, &SB) == FALLO)
{
    return FALLO;
}


int contInodos = SB.posPrimerInodoLibre + 1;

for (int i = SB.posPrimerBloqueAI; i <= SB.posUltimoBloqueAI; i++)
{
    for (int j = 0; i < (BLOCKSIZE / INODOSIZE); j++)
    {
        inodos[j].tipo = 'l';
        if (contInodos < SB.totInodos)
        {
            inodos[j].punterosDirectos[0] = contInodos;
            contInodos++;
        }
        else
        {
            inodos[j].punterosDirectos[0] = UINT_MAX;
            break;
        }
    }
    if (bwrite(i, inodos) < 0)
    {
        fprintf(stderr, "Error al inicializar AI\n");
        return FALLO;
    }
}
return EXITO;
}




int escribir_bit(unsigned int nbloque, unsigned int bit)
{
    int posbyte, posbit, nbloqueMB, nbloqueabs;
    unsigned char *bufferMB = malloc(BLOCKSIZE);
    unsigned char mascara = 128;

    struct superbloque SB;
    bread(posSB, &SB);

    posbyte = nbloque / 8;
    posbit = nbloque % 8;
    nbloqueMB = posbyte / BLOCKSIZE;
    nbloqueabs = SB.posPrimerBloqueMB + nbloqueMB;

    if (bread(nbloqueabs, bufferMB) < 0)
    {
        return FALLO;
    }

    posbyte = posbyte % BLOCKSIZE;

    mascara >>= posbit;

    if (bit == 1)
    {
        bufferMB[posbyte] |= mascara;
    }
    else
    {
        bufferMB[posbyte] &= ~mascara;
    }

    if (bwrite(nbloqueabs, bufferMB) < 0)
    {
        return FALLO;
    }
    return EXITO;
}