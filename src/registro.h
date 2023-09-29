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
void scan_quote_string(char *str);

void funcionalidade1();
void funcionalidade2() ;
void funcionalidade3();
void funcionalidade4();

registroCab createCabecalho();
void readCabecalho(registroCab *r, FILE *dataBinFile);
void setCabecalho(registroCab *rC, int numParesUnicos, int numTecnologiasUnicas);
void writeCabecalho(FILE *binFile, registroCab *rC);

void writeRegistro(registro *r1, FILE *binFile, int posicao);
void readRegistro(registro *r, FILE *dataBinFile);
void printRegistro(registro r1);

char *armCampo(char *linha,int *posicao);
void dataTecnologia(registro *r1, char paresUnicos[][2][40], char tecnologiasUnicas[][40], int *numTecnologiasUnicas, int *numParesUnicos) ;
void adicionarParUnico(char paresUnicos[][2][40], char *origem, char *destino, int *numParesUnicos);
void adicionarTecnologiaUnica(char tecnologiasUnicas[][40], char *tecnologia, int *numTecnologiasUnicas);

void checkFile(FILE *arquivo);
#endif