#include "header.h"


void funcionalidade2(char *dataBin){

    FILE *dataBInFile = fopen(dataBin,"rb");

    if(!dataBInFile){
        printf("Erro ao abrir arquivo\n");
        return;
    }

    registro *r = (registro*) malloc(sizeof(registro));
    //registro r;
    //char l[256];

    //fread(rc,sizeof(registroCab),1,dataBInFile);
    //fseek(dataBInFile,13, SEEK_CUR);

    free(r);
    fclose(dataBInFile);
}


void lerArquivo(char *dataBinFile){
    registro *r;

    r = malloc(sizeof(registro));

    registroCab *rc = (registroCab*) malloc(sizeof(registroCab));

    fread(rc, sizeof(registroCab), 1, dataBinFile);

    while(fread(&r.removido,1,1,dataBinFile) != 0){
        fread(&r.grupo,sizeof(int),1,dataBinFile);
        fread(&r.popularidade,sizeof(int), 1, dataBinFile);
        fread(&r.peso, sizeof(int), 1, dataBinFile);
        fread(&r.tamTecnologiaOrigem, sizeof(int),1,dataBinFile);
        fread(&r.nmTecnologiaOrigem, sizeof(char),r.tamTecnologiaOrigem, dataBinFile);
        fread(&r.tamTecnologiaDestino, sizeof(int),1,dataBinFile);
        fread(&r.nmTecnologiaDestino, sizeof(char),r.tamTecnologiaDestino, dataBinFile);
    }

    free(rc);
}