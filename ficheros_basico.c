#include <ficheros_basico.h>

#define DEBUG3 1


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


int initMB(){
    int MDsize=tamSB+tamMB()+tamAI();
    char bufferMD[MDsize/8];

}


int initAI()
{
    
}