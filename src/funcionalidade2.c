#include "registro.h"

void funcionalidade2(char *dataBin){

    FILE *dataBinFile = fopen(dataBin,"rb");

    if(!dataBinFile){
        printf("Erro ao abrir arquivo\n");
        return;
    }

    registro *r;
    registroCab *rc; 

    r = malloc(sizeof(registro));

    rc = malloc(sizeof(registroCab));

    fread(&rc->status,sizeof(char),1,dataBinFile);
    fread(&rc->proxRRN,sizeof(int),1,dataBinFile);
    fread(&rc->nroTecnologias,sizeof(int),1,dataBinFile);
    fread(&rc->nroParesTecnologias,sizeof(int),1,dataBinFile);

    while(fread(&r->removido,1,1,dataBinFile) != 0){
        fread(&r->grupo,sizeof(int),1,dataBinFile);
        fread(&r->popularidade,sizeof(int), 1, dataBinFile);
        fread(&r->peso, sizeof(int), 1, dataBinFile);
        fread(&r->tamTecnologiaOrigem, sizeof(int),1,dataBinFile);
        fread(&r->nmTecnologiaOrigem, sizeof(char),r->tamTecnologiaOrigem, dataBinFile);
        fread(&r->tamTecnologiaDestino, sizeof(int),1,dataBinFile);
        fread(&r->nmTecnologiaDestino, sizeof(char),r->tamTecnologiaDestino, dataBinFile);
        printf("%s, %d, %d, %s, %d \n", r->nmTecnologiaOrigem, r->grupo, r->popularidade, r->nmTecnologiaDestino, r->peso);
    }

    free(r);
    free(rc);
    fclose(dataBinFile);
}
