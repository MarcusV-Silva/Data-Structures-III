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
    rC->proxRRN = 0;
    rC->nroTecnologias = 0;
    rC->nroParesTecnologias = 0;

    //escreve os dados da struct de cabeçalho no .bin 
    //(ISSUE: esta escrevendo em 3 bytes a mais)
    fwrite(rC, sizeof(registroCab), 1, binFile);
    
    char linha[256];
    while (fgets(linha, sizeof(linha), csvFile) != NULL) {
        registro *r1 = malloc(sizeof(registro));
        
        memset(r1, 0, sizeof(registro)); // Inicialize a estrutura

        char *token = strtok(linha, ",");
        if (token == NULL) {
            continue; // Linha vazia
        }
        r1->nmTecnologiaOrigem = malloc(sizeof(token));
        r1->tamTecnologiaOrigem = strlen(token);
        strcpy(r1->nmTecnologiaOrigem, token);
        
        
        r1->removido = '1';

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
            r1->nmTecnologiaDestino = malloc(sizeof(token));
            r1->tamTecnologiaDestino = strlen(token);
            strcpy(r1->nmTecnologiaDestino,token);
        }

        token = strtok(NULL, ",");
        if (token != NULL) {
            r1->peso = atoi(token);
        }

        
        fwrite(r1, sizeof(registro), 1, binFile);
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
        free(r1->nmTecnologiaOrigem);
        free(r1->nmTecnologiaDestino);
        free(r1);
    }

    fclose(csvFile);
    fclose(binFile);

}

