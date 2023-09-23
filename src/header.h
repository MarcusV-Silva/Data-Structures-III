#ifndef HEADER_H
#define HEADER_H

#define REMOVIDO '1'
#define NAOREMOVIDO '0'
#define TAMREGISTRO 76
#define LIXO '$'

#include <stdio.h>
#include <stdlib.h>

typedef struct stringVariable{
    char* value;
    int length;
}sVariable;

typedef struct RegistersVariable{
    char removido;
    int grupo;
    int popularidade;
    int peso;
    int tamTecnologiaOrigem;
    sVariable *nmTecnologiaOrigem;
    int tamTecnologiaDestino;
    sVariable *nmTecnologiaDestino;
}registro;

typedef struct registroCabecalho{
    char status;
    int proxRRN;
    int nroTecnologias;
    int nroParesTecnologias;
}registroCab;


void funcionalidade1();
void criarRegistroCab(registroCab *rC);
#endif

