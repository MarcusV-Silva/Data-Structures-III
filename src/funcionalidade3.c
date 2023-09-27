#include "registro.h"

void funcionalidade3(char *dataBin, int n){
    FILE *binFile = fopen(dataBin, "rb");

    if (!binFile) {
        printf("Erro ao abrir arquivo\n");
        return;
    }

    for(int i = 0; i<n; i++){
        char tmp1[40];
        char tmp2[40];

        scanf("%s", tmp1);
        scan_quote_string(tmp2);

        registro r1;
        for(int i = 0; i<490; i++) {
            funcLer(&r1, binFile);
            if (strcmp(tmp1, "nomeTecnologiaOrigem") == 0 && strcmp(r1.nmTecnologiaOrigem, tmp2) == 0) {
                printRegistro(r1); break;
            } else if (strcmp(tmp1, "nomeTecnologiaDestino") == 0 && strcmp(r1.nmTecnologiaDestino, tmp2) == 0) {
                printRegistro(r1);  break;
            } else if (strcmp(tmp1, "grupo") == 0 && r1.grupo== atoi(tmp2)){
                printRegistro(r1); break;
            } else if (strcmp(tmp1, "popularidade") == 0 && r1.popularidade == atoi(tmp2)){
                printRegistro(r1); break;
            } else if (strcmp(tmp1, "peso") == 0 && r1.peso == atoi(tmp2)){
                printRegistro(r1); break;
            } 
        }

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
}

void printRegistro(registro r1){
    printf("%s, %d, %d, %s, %d\n", r1.nmTecnologiaDestino, r1.grupo, r1.popularidade, r1.nmTecnologiaOrigem, r1.peso);
}