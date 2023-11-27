#ifndef CABECALHO_H
#define CABECALHO_H

#include "funcionalidades.h"

// Struct referente aos dados do cabeçalho do arquivo
typedef struct cabecalhoIndice{
    char status;
    int noRaiz;
    int RRNproxNo;
}cabIndice;

cabIndice *createCabecalhoIndice();
void writeCabecalhoIndice(FILE *arquivo, cabIndice *rI);
void readCabIndice(FILE *arquivo, cabIndice *rI);
void verificarTecnologias(FILE *dataFile, registro registroInsercao);
void verifyStatusIndice(cabIndice r);


//--------------------TRABALHO 0------------------------

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

// Função que atualiza as informações da sctruct cabecalho 
void setCabecalho(registroCab *rC, int numParesUnicos, int numTecnologiasUnicas);

// Função que escreve os dados no cabeçalho do arquivo binário
void writeCabecalho(FILE *binFile, registroCab *rC);

// Função que verifica o campo status do cabeçalho
void verifyStatus(registroCab rC);

// Função que adiciona e armazena uma nova tecnologia 
void addTecnologiaUnica(char tecUnic[][MAX_STRING], char *tecnologia, int tamanho, int *numTec);

// Função que adiciona e armazena um novo par de tecnologias
void addParUnico(char parUnic[][2][MAX_STRING], registro r1, int *numPares);
#endif