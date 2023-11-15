#include "indice.h"
#include "registro.h"
#include "cabecalho.h"
#include "arvore.h"
#include "funcionalidades.h"
#include "complemento.h"

char *createChave(FILE *arquivo, int RRN){
    registro *r = malloc(sizeof(registro));
    
    registroCab rC;
    readCabecalho(&rC, arquivo);
    verifyStatus(rC);

    fseek(arquivo, RRN, SEEK_SET);
    readRegistro(r, arquivo);

    char *concatenada = (char *)malloc(r->tamTecnologiaDestino + r->tamTecnologiaOrigem + 1); 

    strcpy(concatenada, r->nmTecnologiaOrigem);
    strcat(concatenada, r->nmTecnologiaDestino);

    freeRegistro(r);

    return concatenada;
}