#ifndef HEADER_H
#define HEADER_H

#define REMOVIDO '1'
#define NAOREMOVIDO '0'
#define TAMREGISTRO 76
#define LIXO '$'

#include <stdio.h>
#include <stdlib.h>

typedef struct RegistersVariable{
    char removido;
    int grupo;
    int popularidade;
    int peso;
    int tamTecnologiaOrigem;
    char nmTecnologiaOrigem[20];
    int tamTecnologiaDestino;
    char nmTecnologiaDestino[20];
}registro;

typedef struct registroCabecalho{
    char status;
    int proxRRN;
    int nroTecnologias;
    int nroParesTecnologias;
}registroCab;

void binarioNaTela(char *nomeArquivoBinario);
void funcionalidade1();

#endif

