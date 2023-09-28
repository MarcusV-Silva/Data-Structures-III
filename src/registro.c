#include "registro.h"

registroCab createCabecalho(){
    registroCab rC;
    rC.status = '0';
    rC.proxRRN = 0;
    rC.nroTecnologias = 0;
    rC.nroParesTecnologias = 0;
    return rC;
}

void setCabecalho(registroCab *rC, int numParesUnicos, int numTecnologiasUnicas){
    rC->proxRRN = rC->proxRRN + 1;
    rC->nroParesTecnologias = numParesUnicos;
    rC->nroTecnologias = numTecnologiasUnicas;
}

void writeCabecalho(FILE *binFile, registroCab *rC){
    fseek(binFile, 0, SEEK_SET);
    fwrite(&rC->status, sizeof(char), 1, binFile);
    fwrite(&rC->proxRRN, sizeof(int), 1, binFile);
    fwrite(&rC->nroTecnologias, sizeof(int), 1, binFile);
    fwrite(&rC->nroParesTecnologias, sizeof(int), 1, binFile);
}

void readCabecalho(registroCab *r, FILE *dataBinFile){
    fread(&r->status, sizeof(char), 1, dataBinFile);
    fread(&r->proxRRN, sizeof(int), 1, dataBinFile);
    fread(&r->nroTecnologias, sizeof(int), 1, dataBinFile);
    fread(&r->nroParesTecnologias, sizeof(int), 1, dataBinFile);
}

void writeRegistro(registro *r1, FILE *binFile, int posicao){
    if(r1->grupo == 0){r1->grupo = -1;}
    if(r1->popularidade == 0){r1->popularidade = -1;}
    if(r1->peso == 0){r1->peso = -1;}

    fwrite(&r1->removido, sizeof(char), 1, binFile);
    fwrite(&r1->grupo, sizeof(int), 1, binFile);
    fwrite(&r1->popularidade, sizeof(int), 1, binFile);
    fwrite(&r1->peso, sizeof(int), 1, binFile);
    fwrite(&r1->tamTecnologiaOrigem, sizeof(int), 1, binFile);
    fwrite(r1->nmTecnologiaOrigem, sizeof(char), r1->tamTecnologiaOrigem, binFile);
    fwrite(&r1->tamTecnologiaDestino, sizeof(int), 1, binFile);
    fwrite(r1->nmTecnologiaDestino, sizeof(char), r1->tamTecnologiaDestino, binFile);

    for(int l = TAMREGISTROFIXO + r1->tamTecnologiaDestino + r1->tamTecnologiaOrigem; l < TAMREGISTRO; l++){
        fwrite(LIXO, sizeof(char), 1, binFile);
        posicao++;
    }
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

    int qntLida = TAMREGISTROFIXO + r->tamTecnologiaDestino + r->tamTecnologiaOrigem;
    int i;
    while(qntLida < TAMREGISTRO){
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