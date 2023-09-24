#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "header.h"

#include "header.h"

void funcionalidade1(char *dataCSV, char *dataBIN){
    registro *r1 =(registro *) malloc(sizeof(registro));
    registroCab *rC = (registroCab *) malloc(sizeof(registroCab));
    char *r;

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
    char f;
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

    //escreve os dados do .csv no .bin
    while(fread(&r, sizeof(char), 1, csvFile) != 0 ){
        fwrite(&r, sizeof(char), 1, binFile);
    }

    free(r1);
    free(rC);
    fclose(csvFile);
    fclose(binFile);
}