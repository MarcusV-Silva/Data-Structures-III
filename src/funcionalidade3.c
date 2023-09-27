#include "registro.h"

void funcionalidade3(char *dataBin, int n){
    FILE *binFile = fopen(dataBin, "rb");

    if (!binFile) {
        printf("Erro ao abrir arquivo\n");
        return;
    }

    registroCab rC;
    funcLerCab(&rC, binFile);

    for(int i = 0; i<n; i++){
        char tmp1[40];
        char tmp2[40];

        scanf("%s", tmp1);
        scan_quote_string(tmp2);
        
        int registroEncontrado = 0;
        registro r1;
        for(int j = 0; j < rC.nroTecnologias; j++) {
            funcLer(&r1, binFile);
            if (strcmp(tmp1, "nomeTecnologiaOrigem") == 0 && strcmp(r1.nmTecnologiaOrigem, tmp2) == 0) {
                registroEncontrado = 1;
            } else if (strcmp(tmp1, "nomeTecnologiaDestino") == 0 && strcmp(r1.nmTecnologiaDestino, tmp2) == 0) {
                registroEncontrado = 1;
            } else if (strcmp(tmp1, "grupo") == 0 && r1.grupo == atoi(tmp2)){
                registroEncontrado = 1;
            } else if (strcmp(tmp1, "popularidade") == 0 && r1.popularidade == atoi(tmp2)){
                registroEncontrado = 1;
            } else if (strcmp(tmp1, "peso") == 0 && r1.peso == atoi(tmp2)){
                registroEncontrado = 1;
            }

            if(registroEncontrado){
                printRegistro(r1);
                break;
            }
        }
        if(!registroEncontrado)
            printf("Registro não encontrado");        

    }
    fclose(binFile);
}


void funcLer(registro *r, FILE *dataBinFile){
    fread(&r->removido, 1, 1, dataBinFile);
    fread(&r->grupo, sizeof(int), 1, dataBinFile);
    fread(&r->popularidade, sizeof(int), 1, dataBinFile);
    fread(&r->peso, sizeof(int), 1, dataBinFile);
    fread(&r->tamTecnologiaOrigem, sizeof(int), 1, dataBinFile);
    r->nmTecnologiaOrigem = malloc(r->tamTecnologiaOrigem);
    fread(r->nmTecnologiaOrigem, 1, r->tamTecnologiaOrigem, dataBinFile);
    fread(&r->tamTecnologiaDestino, sizeof(int), 1, dataBinFile);
    r->nmTecnologiaDestino = malloc(r->tamTecnologiaDestino);
    fread(r->nmTecnologiaDestino, 1, r->tamTecnologiaDestino, dataBinFile);
    int qntLida = 21 + r->tamTecnologiaDestino + r->tamTecnologiaOrigem;

    int i;
    while(qntLida < 76){
        fread(&i, 1, 1, dataBinFile);
        qntLida++;
    }
}

void funcLerCab(registroCab *r, FILE *dataBinFile){
    fread(&r->status, sizeof(char), 1, dataBinFile);
    fread(&r->proxRRN, sizeof(int), 1, dataBinFile);
    fread(&r->nroTecnologias, sizeof(int), 1, dataBinFile);
    fread(&r->nroParesTecnologias, sizeof(int), 1, dataBinFile);
}

void printRegistro(registro r1){
    printf("%s, %d, %d, %s, %d\n",  r1.nmTecnologiaOrigem, r1.grupo, r1.popularidade,r1.nmTecnologiaDestino, r1.peso);
}