#ifndef CABECALHO_H
#define CABECALHO_H

#include "registro.h"

// Struct referente aos dados do cabeçalho do arquivo
typedef struct registroCabecalho{
    char status;
    int proxRRN;
    int nroTecnologias;
    int nroParesTecnologias;
}registroCab;

// Função que cria o cabeçalho, inicializando as suas variáveis
int createCabecalho(registroCab *rC);

// Função que lê os arquivos do cabeçalho
void readCabecalho(registroCab *rC, FILE *dataBinFile);

// Função que atualiza o número de pares de tecnologias,
// como também o número de tecnologias
void setCabecalho(registroCab *rC, int numParesUnicos, int numTecnologiasUnicas);

// Função que acessa os dados do cabeçalho do arquivo binário
void writeCabecalho(FILE *binFile, registroCab *rC);

// Função que verifica o campo status do cabeçalho
void verifyStatus(registroCab rC);

// Função que adiciona e armazena uma nova tecnologia 
void addTecnologiaUnica(char tecUnic[][MAX_STRING], char *tecnologia, int tamanho, int *numTec);

// Função que adiciona e armazena um novo par de tecnologias
void addParUnico(char parUnic[][2][MAX_STRING], registro r1, int *numPares);

#endif