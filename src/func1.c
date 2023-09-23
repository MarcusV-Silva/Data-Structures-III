#include "header.h"

void funcionalidade1(char *dataCSV, char *dataBIN){
    char buf[TAMREGISTRO];
    registro r1;

    FILE *csv = fopen(dataCSV, "r");
    if(!csv){
        printf("Erro ao abrir arquivo\n");
    }

    FILE *bin = fopen(dataBIN, "wb");
    if(!bin){
        printf("Erro ao abrir arquivo\n");
    }


    while(fread(&r1, sizeof(r1), 1, csv) != 0){
        fwrite(&r1, sizeof(r1), 1, bin);
    }

    fclose(csv);
    fclose(bin);
}

