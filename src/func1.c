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
    rC->nroTecnologias = 115;
    rC->nroParesTecnologias = 490;

  
    fwrite(&rC->status, sizeof(char), 1, binFile);
    fwrite(&rC->proxRRN, sizeof(int), 1, binFile);
    fwrite(&rC->nroTecnologias, sizeof(int), 1, binFile);
    fwrite(&rC->nroParesTecnologias, sizeof(int), 1, binFile);
    

    char linha[256];
    while (fgets(linha, sizeof(linha), csvFile)) {
        int posicao = 0;
        registro *r1 = malloc(sizeof(registro));

        r1->nmTecnologiaOrigem = armCampo(linha, &posicao);
        r1->grupo = atoi(armCampo(linha, &posicao));
        r1->popularidade = atoi(armCampo(linha, &posicao));
        r1->nmTecnologiaDestino = armCampo(linha, &posicao);
        r1->peso = atoi(armCampo(linha, &posicao));
        r1->removido = '0';
        r1->tamTecnologiaOrigem = strlen(r1->nmTecnologiaOrigem);
        r1->tamTecnologiaDestino = strlen(r1->nmTecnologiaDestino);

        fwrite(&r1->removido, sizeof(char), 1, binFile);

        if(r1->grupo == 0){r1->grupo = -1;}
        fwrite(&r1->grupo, sizeof(int), 1, binFile);

        if(r1->popularidade == 0){r1->popularidade = -1;}
        fwrite(&r1->popularidade, sizeof(int), 1, binFile);
        
        if(r1->peso == 0){r1->peso = -1;}
        fwrite(&r1->peso, sizeof(int), 1, binFile);

        fwrite(&r1->tamTecnologiaOrigem, sizeof(int), 1, binFile);
        fwrite(r1->nmTecnologiaOrigem, sizeof(char), r1->tamTecnologiaOrigem, binFile);
        fwrite(&r1->tamTecnologiaDestino, sizeof(int), 1, binFile);
        fwrite(r1->nmTecnologiaDestino, sizeof(char), r1->tamTecnologiaDestino, binFile);

        for(int l = 21+r1->tamTecnologiaDestino+r1->tamTecnologiaOrigem; l<76; l++){
            fwrite("$", sizeof(char), 1, binFile);
            posicao++;
        }
        free(r1);
    }
    
    fclose(csvFile);
    fclose(binFile);
}

char *armCampo(char *linha, int *posicao) {
    char *campo = malloc(256); 
    int i = 0;
    while (linha[*posicao] != ',' && linha[*posicao] != '\0') {
        campo[i++] = linha[(*posicao)++];
    }
    
    (*posicao)++; 
    return campo;
}

