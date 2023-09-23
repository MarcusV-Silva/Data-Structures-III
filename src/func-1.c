#include "header.h"

void funcionalidade1(char *dataCSV, char *dataBIN){
    char buf[TAMREGISTRO];

    FILE *csv = fopen(dataCSV, "r");

    if(!csv){
        printf("Erro ao abrir arquivo\n");
    }

    FILE *bin = fopen(dataBIN, "wb");
    if(!bin){
        printf("Erro ao abrir arquivo\n");
    }

    while(fgets(buf, sizeof(buf),csv)!=NULL){
        fwrite(buf, sizeof(buf), 1, bin);
    }

    fclose(csv);
    fclose(bin);
}

