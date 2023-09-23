#include "header.h"

void funcionalidade1(){
    char buf[TAMREGISTRO];

    FILE *csv = fopen("dados1.csv", "r");

    if(!csv){
        printf("Erro ao abrir arquivo\n");
    }

    FILE *bin = fopen("dados2.bin", "wb");
    
    if(!bin){
        printf("Erro ao abrir arquivo\n");
    }

    while(fgets(buf, sizeof(buf),csv)!=NULL){
        fwrite(buf, sizeof(buf), 1, bin);
    }

    fclose(csv);
    fclose(bin);
}

