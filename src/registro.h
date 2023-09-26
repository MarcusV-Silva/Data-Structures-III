#ifndef HEADER_H
#define HEADER_H

#define REMOVIDO '1'
#define NAOREMOVIDO '0'
#define TAMREGISTRO 76
#define LIXO "$"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct registroDados{
    char removido;
    int grupo;
    int popularidade;
    int peso;
    int tamTecnologiaOrigem;
    char *nmTecnologiaOrigem;
    int tamTecnologiaDestino;
    char *nmTecnologiaDestino;
}registroDados;

typedef struct registroCabecalho{
    char status;
    int proxRRN;
    int nroTecnologias;
    int nroParesTecnologias;
}registroCab;

void binarioNaTela(char *nomeArquivoBinario);
void funcionalidade1();
void funcionalidade2();
char *lenCampo(char *linha,int *posicao);
void armTec(registroDados *r1, char paresUnicos[][2][40], char tecnologiasUnicas[][40], int *numTecnologiasUnicas, int *numParesUnicos) ;

registroCab *createHeader();
void writeHeaderBin(FILE *binFile, registroCab *rC);
void setHeader(registroCab *rC, int numParesUnicos, int numTecnologiasUnicas);

#endif

