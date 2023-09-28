#include "registro.h"

registroCab *createCabecalho(){
    registroCab *rC = (registroCab *) malloc(sizeof(registroCab));
    rC->status = '1';
    rC->proxRRN = 0;
    rC->nroTecnologias = 0;
    rC->nroParesTecnologias = 0;

    return rC;
}

void setCabecalho(registroCab *rC, int numParesUnicos, int numTecnologiasUnicas){
    rC->proxRRN = rC->proxRRN + 1;
    rC->nroParesTecnologias = numParesUnicos;
    rC->nroTecnologias = numTecnologiasUnicas;
}

void writeCabecalho(FILE *binFile, registroCab rC){
    fseek(binFile, 0, SEEK_SET);
    fwrite(&rC.status, sizeof(char), 1, binFile);
    fwrite(&rC.proxRRN, sizeof(int), 1, binFile);
    fwrite(&rC.nroTecnologias, sizeof(int), 1, binFile);
    fwrite(&rC.nroParesTecnologias, sizeof(int), 1, binFile);
}

void readCabecalho(registroCab *r, FILE *dataBinFile){
    fread(&r->status, sizeof(char), 1, dataBinFile);
    fread(&r->proxRRN, sizeof(int), 1, dataBinFile);
    fread(&r->nroTecnologias, sizeof(int), 1, dataBinFile);
    fread(&r->nroParesTecnologias, sizeof(int), 1, dataBinFile);
}

void readRegistro(registro *r, FILE *dataBinFile){
    r->nmTecnologiaDestino = malloc(r->tamTecnologiaDestino);
    r->nmTecnologiaOrigem = malloc(r->tamTecnologiaOrigem);

    fread(&r->removido, 1, 1, dataBinFile);
    fread(&r->grupo, sizeof(int), 1, dataBinFile);
    fread(&r->popularidade, sizeof(int), 1, dataBinFile);
    fread(&r->peso, sizeof(int), 1, dataBinFile);
    fread(&r->tamTecnologiaOrigem, sizeof(int), 1, dataBinFile);
    fread(r->nmTecnologiaOrigem, 1, r->tamTecnologiaOrigem, dataBinFile);
    fread(&r->tamTecnologiaDestino, sizeof(int), 1, dataBinFile);
    fread(r->nmTecnologiaDestino, 1, r->tamTecnologiaDestino, dataBinFile);

    int qntLida = 21 + r->tamTecnologiaDestino + r->tamTecnologiaOrigem;
    int i;
    while(qntLida < 76){
        fread(&i, 1, 1, dataBinFile);
        qntLida++;
    }
}

void printRegistro(registro r1){
    printf("%s, ", r1.nmTecnologiaOrigem);

    if (r1.grupo != -1) 
        printf("%d, ", r1.grupo);
    else 
        printf("NULO, ");
    
    if (r1.popularidade != -1) 
        printf("%d, ", r1.popularidade);
    else 
        printf("NULO, ");
    
    if (r1.tamTecnologiaDestino != 0)
        printf("%s, ", r1.nmTecnologiaDestino);
    else
        printf("NULO, ");

    if (r1.peso != -1) 
        printf("%d\n", r1.peso);
    else 
        printf("NULO\n");
}