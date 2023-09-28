#include "registro.h"

void funcionalidade3(){
    char *dataBin = malloc(sizeof(char)*40);
    int n;

    scanf("%s %d", dataBin, &n);
    FILE *binFile = fopen(dataBin, "rb");
    checkFile(binFile);

    free(dataBin);
    registroCab rC;
    readCabecalho(&rC, binFile);

    for(int i = 0; i<n; i++){
        char tmp1[40];
        char tmp2[40];

        scanf("%s", tmp1);
        scan_quote_string(tmp2);
        
        int flag = 0;
        for(int j = 0; j < 490; j++) {
            int registroEncontrado = 0;
            registro *r1 = malloc(sizeof(registro));
            
            readRegistro(r1, binFile);

            if (strcmp(tmp1, "nomeTecnologiaOrigem") == 0 && strcmp(r1->nmTecnologiaOrigem, tmp2) == 0) {
                registroEncontrado = 1;
            } else if (strcmp(tmp1, "nomeTecnologiaDestino") == 0 && strcmp(r1->nmTecnologiaDestino, tmp2) == 0) {
                registroEncontrado = 1;
            } else if (strcmp(tmp1, "grupo") == 0 && r1->grupo == atoi(tmp2)){
                registroEncontrado = 1;
            } else if (strcmp(tmp1, "popularidade") == 0 && r1->popularidade == atoi(tmp2)){
                registroEncontrado = 1;
            } else if (strcmp(tmp1, "peso") == 0 && r1->peso == atoi(tmp2)){
                registroEncontrado = 1;
            }
            if(registroEncontrado){
                printRegistro(*r1);
                flag =1;
            }
            free(r1);
        }
        if(!flag)
            printf("Registro inexistente.\n");

        fseek(binFile, 13, SEEK_SET);
    }
    fclose(binFile);
}