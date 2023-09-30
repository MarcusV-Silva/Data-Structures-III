#include "funcionalidades.h"
#include "funcoesFornecidas.h"
#include "cabecalho.h"
#include "registro.h"

//Função que inicializa as variáveis do cabeçalho
registroCab createCabecalho(){
    registroCab rC;
    rC.status = '0';
    rC.proxRRN = 0;
    rC.nroTecnologias = 0;
    rC.nroParesTecnologias = 0;
    return rC;
}

//Função que atualiza o número de pares assim como o número de tecnologias do arquivo
void setCabecalho(registroCab *rC, int numParesUnicos, int numTecnologiasUnicas){
    rC->status = '1';
    rC->nroParesTecnologias = numParesUnicos;
    rC->nroTecnologias = numTecnologiasUnicas;
}

//Função que acessa e armazena os dados do cabeçalho no arquivo binário
void writeCabecalho(FILE *binFile, registroCab *rC){
    fseek(binFile, 0, SEEK_SET);
    fwrite(&rC->status, sizeof(char), 1, binFile);
    fwrite(&rC->proxRRN, sizeof(int), 1, binFile);
    fwrite(&rC->nroTecnologias, sizeof(int), 1, binFile);
    fwrite(&rC->nroParesTecnologias, sizeof(int), 1, binFile);
}

//Função que lê os campos do cabeçalho
void readCabecalho(registroCab *r, FILE *dataBinFile){
    fread(&r->status, sizeof(char), 1, dataBinFile);
    fread(&r->proxRRN, sizeof(int), 1, dataBinFile);
    fread(&r->nroTecnologias, sizeof(int), 1, dataBinFile);
    fread(&r->nroParesTecnologias, sizeof(int), 1, dataBinFile);
}