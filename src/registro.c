#include "registro.h"

registroCab *newHeader(){
    registroCab *rC = (registroCab *) malloc(sizeof(registroCab));
    rC->status = '1';
    rC->proxRRN = 0;
    rC->nroTecnologias = 0;
    rC->nroParesTecnologias = 0;

    return rC;
}

void setHeader(registroCab *rC, int numParesUnicos, int numTecnologiasUnicas){
    rC->proxRRN = rC->proxRRN + 1;
    rC->nroParesTecnologias = numParesUnicos;
    rC->nroTecnologias = numTecnologiasUnicas;
}

void writeHeaderBin(FILE *binFile, registroCab *rC){
    fseek(binFile, 1, SEEK_SET);
    fwrite(&rC->proxRRN, sizeof(int), 1, binFile);
    fwrite(&rC->nroTecnologias, sizeof(int), 1, binFile);
    fwrite(&rC->nroParesTecnologias, sizeof(int), 1, binFile);
}


//Função que lê o cabeçalho do arquivo
void readHeaderBin(FILE *dataBinFile){
    
    registroCab *rC;

    rC = malloc(sizeof(registroCab));

    fread(&rC->status, sizeof(char), 1, dataBinFile);
    fread(&rC->proxRRN, sizeof(int), 1, dataBinFile);
    fread(&rC->nroTecnologias, sizeof(int), 1, dataBinFile);
    fread(&rC->nroParesTecnologias, sizeof(int), 1, dataBinFile);

    free(rC);
}