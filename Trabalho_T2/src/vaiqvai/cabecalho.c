#include "registro.h"
#include "cabecalho.h"
#include "funcionalidades.h"
#include "complemento.h"
#include "grafo.h"

// ------------------TRABALHO 0--------------------------
// Função que inicializa as variáveis do cabeçalho dados
int createCabecalho(registroCab *rC){
    rC->status = '0';
    rC->proxRRN = 0;
    rC->nroTecnologias = 0;
    rC->nroParesTecnologias = 0;

    return 0;
}

// Função que atualiza o número de pares assim como o número de tecnologias do arquivo de dados
void setCabecalho(registroCab *rC, int numParesUnicos, int numTecnologiasUnicas){
    rC->status = '1';
    rC->nroParesTecnologias = numParesUnicos;
    rC->nroTecnologias = numTecnologiasUnicas;
}

// Função que escreve os dados no cabeçalho do arquivo binário de dados
void writeCabecalho(FILE *binFile, registroCab *rC){
    fseek(binFile, 0, SEEK_SET);
    fwrite(&rC->status, sizeof(char), 1, binFile);
    fwrite(&rC->proxRRN, sizeof(int), 1, binFile);
    fwrite(&rC->nroTecnologias, sizeof(int), 1, binFile);
    fwrite(&rC->nroParesTecnologias, sizeof(int), 1, binFile);
}

// Função que lê os campos do cabeçalho do arquivo de dados
void readCabecalho(registroCab *rC, FILE *dataBinFile){
    fread(&rC->status, sizeof(char), 1, dataBinFile);
    fread(&rC->proxRRN, sizeof(int), 1, dataBinFile);
    fread(&rC->nroTecnologias, sizeof(int), 1, dataBinFile);
    fread(&rC->nroParesTecnologias, sizeof(int), 1, dataBinFile);
}

// Verifica o campo status do cabeçalho do arquivo de dados
void verifyStatus(registroCab rC){
    if(strcmp(&rC.status, "0") == 0){
        printf("Falha no processamento do arquivo.");
        exit(0);
    }
}

// Função que adiciona e armazena uma nova tecnologia usada na funcionalidade 1
void addTecnologiaUnica(char tecUnic[][MAX_STRING], char *tecnologia, int tamanho, int *numTec) {
    if(tamanho == 0){
        return;
    }
    for (int i = 0; i < *numTec; i++) {
        if (strcmp(tecnologia, tecUnic[i]) == 0) {
            return; 
        }
    }
    strcpy(tecUnic[*numTec], tecnologia);
    (*numTec)++;
}

// Função que adiciona e armazena um novo par de tecnologias usada na funcionalidade 1
void addParUnico(char parUnic[][2][MAX_STRING], registro r1, int *numPares) {
    if(r1.tamTecnologiaDestino == 0){
        return;
    }

    for (int i = 0; i < *numPares; i++) {
        if (strcmp(r1.nmTecnologiaOrigem, parUnic[i][0]) == 0 && strcmp(r1.nmTecnologiaDestino, parUnic[i][1]) == 0) {
            return; 
        }
    }
    strcpy(parUnic[*numPares][0], r1.nmTecnologiaOrigem);
    strcpy(parUnic[*numPares][1], r1.nmTecnologiaDestino);
    (*numPares)++;
}