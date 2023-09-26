#include "header.h"


void funcionalidade2(char *dataBIn){

    FILE *dataBInFile = fopen(dataBIn,"rb");

    if(!dataBInFile){
        printf("Erro ao abrir arquivo\n");
        return;
    }

    registroCab *rc = (registroCab*) malloc(sizeof(registroCab));
    registro *r = malloc(sizeof(registro));

    fread(rc,sizeof(registroCab),1,dataBInFile);

    while(fread(r,sizeof(registro),1,dataBInFile) > 0){
        //printf("%c, %d, %d, %c, %d \n", dataBIn[0], dataBIn[1], dataBIn[2], dataBIn[3], dataBIn[4]);
    }

    free(r);
    free(rc);
    fclose(dataBInFile);
}