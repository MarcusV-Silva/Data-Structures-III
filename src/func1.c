#include "header.h"

void funcionalidade1(char *dataCSV, char *dataBIN){
    registro *r1 =(registro *) malloc(sizeof(registro));

    registroCab *rC= malloc(sizeof(registroCab));


    FILE *csv = fopen(dataCSV, "r");
    if(!csv){
        printf("Erro ao abrir arquivo\n");
    }

    FILE *bin = fopen(dataBIN, "wb");
    if(!bin){
        printf("Erro ao abrir arquivo\n");
    }

    rC->status = '1';
    rC->proxRRN = 0;
    rC->nroTecnologias = 0;
    rC->nroParesTecnologias = 0;

    fwrite(rC, sizeof(registroCab), 1, bin );

    fseek(csv, 68, SEEK_SET);

    while(fread(r1, sizeof(r1), 1, csv) != 0 ){
        fwrite(r1, sizeof(r1), 1, bin);
    }

    free(r1);
    free(rC);
    fclose(csv);
    fclose(bin);
}
