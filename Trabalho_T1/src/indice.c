#include "indice.h"
#include "registro.h"
#include "cabecalho.h"
#include "arvore.h"
#include "funcionalidades.h"
#include "complemento.h"

char *createChave(registro *r){

    char *concatenada = (char *)malloc(r->tamTecnologiaDestino + r->tamTecnologiaOrigem + 1); 
    concatenada[0] = '\0';
    
    strncpy(concatenada, r->nmTecnologiaOrigem, r->tamTecnologiaOrigem);
    strncat(concatenada, r->nmTecnologiaDestino, r->tamTecnologiaDestino);

    freeRegistro(r);

    return concatenada;
}