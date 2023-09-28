#include "registro.h"

void funcionalidade4(){
    char *dataBin = malloc(sizeof(char)*40);
    int RRN;
    scanf("%s %d", dataBin, &RRN);

    FILE *binFile = fopen(dataBin, "rb");
    checkFile(binFile);

    int rrnDestino = (RRN*TAMREGISTRO) +13;
    registro *r1 = malloc(sizeof(registro));

    fseek(binFile, rrnDestino, SEEK_SET);
    readRegistro(r1, binFile);
    printRegistro(*r1);

    free(r1);
    fclose(binFile);
}