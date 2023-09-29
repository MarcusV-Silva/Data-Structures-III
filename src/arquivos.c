#include "registro.h"

void checkFile(FILE *arquivo){
    if (arquivo == NULL) {
        printf("Falha no processamento do arquivo.\n");
        exit(0);
    }
}