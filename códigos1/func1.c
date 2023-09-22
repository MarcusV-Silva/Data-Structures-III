#include "header.h"

int main(){
    char buf[TAMREGISTRO];
    sVariable *svar;

    FILE *csv = fopen("dados1.csv", "r");

    if(!csv){
        printf("Erro ao abrir arquivo\n");
        return 1;
    }

    FILE *bin = fopen("dados2.bin", "wb");
    
    if(!bin){
        printf("Erro ao abrir arquivo\n");
        return 1;
    }

    while (fgets(buf, sizeof(buf),csv)!=NULL){
        
        registro rg;

        //fscanf("%s,%d,%d,%s, %d", svar->value, &rg.grupo, &rg.popularidade, svar->value, &rg.peso);


        fwrite(&rg, sizeof(registro), 1, bin);
    }
    

    fclose(csv);
    fclose(bin);

    return 0;
}

