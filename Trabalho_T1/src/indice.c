#include "indice.h"
#include "registro.h"
#include "cabecalho.h"
#include "arvore.h"
#include "funcionalidades.h"
#include "complemento.h"

char *createChave(FILE *arquivo){
    registro *r = malloc(sizeof(registro));
    readRegistro(r, arquivo);

    char *concatenada = (char *)malloc(r->tamTecnologiaDestino + r->tamTecnologiaOrigem + 1); 

    strcpy(concatenada, r->nmTecnologiaOrigem);
    strcat(concatenada, r->nmTecnologiaDestino);

    freeRegistro(r);

    return concatenada;
}