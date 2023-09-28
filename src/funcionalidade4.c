#include "registro.h"
void funcionalidade4(){
    char *dataBin = malloc(sizeof(char)*40);
    int RRN;
    scanf("%s %d", dataBin, &RRN);

    FILE *binFile = fopen(dataBin, "rb");

    if (!binFile) {
        printf("Erro ao abrir arquivo\n");
        return;
    }

    free(dataBin);
    registroCab rC;
    readCabecalho(&rC, binFile);

    int rrnDestino = (RRN*TAMREGISTRO) ;

    registro *r1 = malloc(sizeof(registro));
    for(int posicaoAtual = 0; posicaoAtual<=rrnDestino; posicaoAtual+=76){
        readRegistro(r1, binFile);
    }

    printRegistro(*r1);

    fclose(binFile);

}