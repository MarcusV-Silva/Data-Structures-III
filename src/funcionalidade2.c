#include "registro.h"

void funcionalidade2(char *dataBin) {
    FILE *dataBinFile = fopen(dataBin, "rb");

    if (!dataBinFile) {
        printf("Erro ao abrir arquivo\n");
        return;
    }

    registroCab *rC;

    rC = malloc(sizeof(registroCab));

    readCabecalho(rC, dataBinFile);

    //While que imprime os dados do arquivo
    for (int i = 0; i < 490; i++){
        registro *r;
        r = malloc(sizeof(registro));

        readRegistro(r, dataBinFile);

        printRegistro(*r);

        free(r);
    }

    fclose(dataBinFile);
}
