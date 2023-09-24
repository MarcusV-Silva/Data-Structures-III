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
    while (fgets(linha, sizeof(linha), csvFile) != NULL) {
        registro *r1 = malloc(sizeof(registro));
        
        memset(r1, 0, sizeof(registro)); // Inicialize a estrutura

        char *token = strtok(linha, ",");
        if (token == NULL) {
            continue; 
        }
        r1->tamTecnologiaOrigem = strlen(token);
        strcpy(r1->nmTecnologiaOrigem, token);
        
        token = strtok(NULL, ",");
        if (token != NULL) {
           r1->grupo = atoi(token);
        }

        token = strtok(NULL, ",");
        if (token != NULL) {
            r1->popularidade = atoi(token);
        }

        token = strtok(NULL, ",");
        if (token != NULL) {
            r1->tamTecnologiaDestino = strlen(token);
            strcpy(r1->nmTecnologiaDestino,token);
        }

        token = strtok(NULL, ",");
        if (token != NULL) {
            r1->peso = atoi(token);
        }

        
        r1->removido = '0';

        fwrite(&r1->removido, sizeof(char), 1, binFile );
        fwrite(&r1->grupo, sizeof(int), 1, binFile );
        fwrite(&r1->popularidade, sizeof(int), 1, binFile );
        fwrite(&r1->peso, sizeof(int), 1, binFile );
        fwrite(&r1->tamTecnologiaOrigem, sizeof(int), 1, binFile );
        fwrite(&r1->nmTecnologiaOrigem, sizeof(char), r1->tamTecnologiaOrigem, binFile );
        fwrite(&r1->tamTecnologiaDestino, sizeof(int), 1, binFile );
        fwrite(&r1->nmTecnologiaDestino,  sizeof(char), r1->tamTecnologiaDestino, binFile );
        
        int byteoffsets = 21 + r1->tamTecnologiaOrigem + r1->tamTecnologiaDestino;
        char *lixo = "$";
        
        while(byteoffsets < 76){ 
            fwrite(lixo, sizeof(char), 1, binFile );
            byteoffsets++;
        }
        
        /*
        printf("\nremovido: %c\n", r1->removido);
        printf("grupo: %d\n", r1->grupo);
        printf("popularidade: %d \n", r1->popularidade);
        printf("peso: %d\n", r1->peso);
        printf("tamTecnologiaOrigem: %d\n", r1->tamTecnologiaOrigem);
        printf("nmTecnologiaOrigem: %s\n", r1->nmTecnologiaOrigem);
        printf("tamTecnologiaDestino: %d\n", r1->tamTecnologiaDestino);
        printf("nmTecnologiaDestino: %s\n", r1->nmTecnologiaDestino);
        */
        free(r1);
    }

    fclose(csvFile);
    fclose(binFile);

}

