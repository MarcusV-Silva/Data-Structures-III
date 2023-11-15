#include "indice.h"
#include "registro.h"
#include "cabecalho.h"
#include "arvore.h"
#include "funcionalidades.h"
#include "complemento.h"

cabIndice *createCabecalhoIndice(){
    cabIndice *cabecalho = malloc(sizeof(cabIndice));

    cabecalho->status = '0';
    cabecalho->noRaiz = -1;
    cabecalho->RRNproxNo = 0;

    return cabecalho;
}

void writeCabecalhoIndice(FILE *arquivo, cabIndice *rI){
    fwrite(&rI->status, sizeof(char), 1, arquivo);
    fwrite(&rI->noRaiz, sizeof(int), 1, arquivo);
    fwrite(&rI->RRNproxNo, sizeof(int), 1, arquivo);
    
    for(int i = 0; i<TAM_LIXO_CAB; i++) {
        fwrite(LIXO, sizeof(char), 1, arquivo);
    }
}


// TRABALHO 0
// Função que inicializa as variáveis do cabeçalho
int createCabecalho(registroCab *rC){
    rC->status = '0';
    rC->proxRRN = 0;
    rC->nroTecnologias = 0;
    rC->nroParesTecnologias = 0;

    return 0;
}

// Função que atualiza o número de pares assim como o número de tecnologias do arquivo
void setCabecalho(registroCab *rC, int numParesUnicos, int numTecnologiasUnicas){
    rC->status = '1';
    rC->nroParesTecnologias = numParesUnicos;
    rC->nroTecnologias = numTecnologiasUnicas;
}

// Função que escreve os dados no cabeçalho do arquivo binário
void writeCabecalho(FILE *binFile, registroCab *rC){
    fseek(binFile, 0, SEEK_SET);
    fwrite(&rC->status, sizeof(char), 1, binFile);
    fwrite(&rC->proxRRN, sizeof(int), 1, binFile);
    fwrite(&rC->nroTecnologias, sizeof(int), 1, binFile);
    fwrite(&rC->nroParesTecnologias, sizeof(int), 1, binFile);
}

// Função que lê os campos do cabeçalho
void readCabecalho(registroCab *rC, FILE *dataBinFile){
    fread(&rC->status, sizeof(char), 1, dataBinFile);
    fread(&rC->proxRRN, sizeof(int), 1, dataBinFile);
    fread(&rC->nroTecnologias, sizeof(int), 1, dataBinFile);
    fread(&rC->nroParesTecnologias, sizeof(int), 1, dataBinFile);
}

// Verifica o campo status do cabeçalho
void verifyStatus(registroCab rC){
    if(strcmp(&rC.status, "0") == 0){
        printf("Falha no processamento do arquivo.");
        exit(0);
    }
}

// Função que adiciona e armazena uma nova tecnologia
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

// Função que adiciona e armazena um novo par de tecnologias
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