#include "registro.h"

void funcionalidade4(){
    char *dataBin = malloc(sizeof(char)*40);
    int RRN;
    scanf("%s %d", dataBin, &RRN);

    FILE *binFile = fopen(dataBin, "rb");
    checkFile(binFile);

    int rrnDestino = (RRN*TAMREGISTRO) + 13;
    registro *r1 = malloc(sizeof(registro));

    if(fseek(binFile, rrnDestino, SEEK_SET) == 0){
        readRegistro(r1, binFile);
        int byteLido = fgetc(binFile);
        if (byteLido == EOF){
            printf("Registro inexistente.");
        }else
            printRegistro(*r1);
    }else{
        printf("Registro inexistente.");
    }

    free(r1);
    fclose(binFile);
}