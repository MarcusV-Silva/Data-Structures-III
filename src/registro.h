#ifndef HEADER_H
#define HEADER_H

#define REMOVIDO '1'
#define NAOREMOVIDO '0'
#define TAMREGISTRO 76
#define TAMREGISTROFIXO 21
#define LIXO "$"
#define MAX_TECNOLOGIAS 1000

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct RegistersVariable{
    char removido;
    int grupo;
    int popularidade;
    int peso;
    int tamTecnologiaOrigem;
    char *nmTecnologiaOrigem;
    int tamTecnologiaDestino;
    char *nmTecnologiaDestino;
}registro;

typedef struct registroCabecalho{
    char status;
    int proxRRN;
    int nroTecnologias;
    int nroParesTecnologias;
}registroCab;

void binarioNaTela(char *nomeArquivoBinario);

void funcionalidade1(char *dataCSV, char *dataBIN);
void funcionalidade2(char *dataBin) ;
void funcionalidade3(char *dataBin, int n);
void funcionalidade4(char *dataBin, int RRN);

void *alocarMemoria (size_t dado);
char *armCampo(char *linha,int *posicao);
void armTec(registro *r1, char paresUnicos[][2][40], char tecnologiasUnicas[][40], int *numTecnologiasUnicas, int *numParesUnicos) ;
void newRegCab(FILE *binFile, registroCab *r1);
void scan_quote_string(char *str);
void funcLer(registro *r, FILE *dataBinFile);
void printRegistro(registro r1);
void funcLerCab(registroCab *r, FILE *dataBinFile);
#endif