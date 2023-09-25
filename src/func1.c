#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "header.h"

void funcionalidade1(char *dataCSV, char *dataBIN){
    registroCab *rC = (registroCab *) malloc(sizeof(registroCab));

    FILE *csvFile = fopen(dataCSV, "r");
    if(!csvFile){
        printf("Erro ao abrir arquivo\n");
    }

    FILE *binFile = fopen(dataBIN, "wb");
    if(!binFile){
        printf("Erro ao abrir arquivo\n");
    }

    //ignora a primeira linha do .csv
    int c;
    while ((c = fgetc(csvFile)) != EOF && c != '\n') {
    }

    //inicializa registro de cabeçalho .bin
    rC->status = '1';
    rC->proxRRN = 490;
    rC->nroTecnologias = 142;
    rC->nroParesTecnologias = 490;

  
    fwrite(&rC->status, sizeof(char), 1, binFile);
    fwrite(&rC->proxRRN, sizeof(int), 1, binFile);
    fwrite(&rC->nroTecnologias, sizeof(int), 1, binFile);
    fwrite(&rC->nroParesTecnologias, sizeof(int), 1, binFile);
    
        char linha[256];
        fgets(linha, sizeof(linha), csvFile) ;
        int posicao = 0;
        registro *r1 = malloc(sizeof(registro));

        
        r1->nmTecnologiaOrigem = armCampo(linha,lenCampo(linha, posicao), &posicao);
        r1->grupo = atoi(armCampo(linha,lenCampo(linha, posicao), &posicao));
        r1->popularidade = atoi(armCampo(linha,lenCampo(linha, posicao), &posicao));
        r1->nmTecnologiaDestino= armCampo(linha,lenCampo(linha, posicao), &posicao);
        r1->peso= atoi(armCampo(linha,lenCampo(linha, posicao), &posicao));
        r1->removido = '0';
        r1->tamTecnologiaOrigem = strlen(r1->nmTecnologiaOrigem);
        r1->tamTecnologiaDestino = strlen(r1->nmTecnologiaDestino);

        fwrite(&r1->removido, sizeof(char), 1, binFile );
        fwrite(&r1->grupo, sizeof(int), 1, binFile );
        fwrite(&r1->popularidade, sizeof(int), 1, binFile );
        fwrite(&r1->peso, sizeof(int), 1, binFile );
        fwrite(&r1->tamTecnologiaOrigem, sizeof(int), 1, binFile );
        fwrite(&r1->nmTecnologiaOrigem, sizeof(char), r1->tamTecnologiaOrigem, binFile );
        fwrite(&r1->tamTecnologiaDestino, sizeof(int), 1, binFile );
        fwrite(&r1->nmTecnologiaDestino,  sizeof(char), r1->tamTecnologiaDestino, binFile );

        printf("\nremovido: %c\n", r1->removido);
        printf("grupo: %d\n", r1->grupo);
        printf("popularidade: %d \n", r1->popularidade);
        printf("peso: %d\n", r1->peso);
        printf("tamTecnologiaOrigem: %d\n", r1->tamTecnologiaOrigem);
        printf("nmTecnologiaOrigem: %s\n", r1->nmTecnologiaOrigem);
        printf("tamTecnologiaDestino: %d\n", r1->tamTecnologiaDestino);
        printf("nmTecnologiaDestino: %s\n", r1->nmTecnologiaDestino);

        free(r1);
    

    fclose(csvFile);
    fclose(binFile);
}

int lenCampo(char *linha, int posicao) {
    int tamanhoCampo = 0;

    while (linha[posicao] != '\0' && linha[posicao] != ',') {
        tamanhoCampo++;
    }
    return tamanhoCampo;
}

char *armCampo(char *linha, int tamanho, int *posicao){
    char *tmp = malloc(sizeof(char) * (tamanho + 1));
    for(int i = 0; i<tamanho; i++){
        tmp[i] = linha[*posicao];
        (*posicao)++;
    }
    tmp[tamanho] = '\0';
    return tmp;
}

