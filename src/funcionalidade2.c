#include "registro.h"

void funcionalidade2() {
    char *dataBin = malloc(sizeof(char)*40);
    scanf("%s", dataBin);
    FILE *dataBinFile = fopen(dataBin, "rb");
    checkFile(dataBinFile);

    registroCab *rC = malloc(sizeof(registroCab));
    readCabecalho(rC, dataBinFile);

    for (int i = 0; i < 490; i++){
        registro *r = malloc(sizeof(registro));
        readRegistro(r, dataBinFile);
        printRegistro(*r);

        free(r);
    }
    free(dataBin);
    fclose(dataBinFile);
}