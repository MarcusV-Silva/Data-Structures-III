#include "registro.h"
void funcionalidade4(char *dataBin, int RRN){
    FILE *binFile = fopen(dataBin, "rb");

    if (!binFile) {
        printf("Erro ao abrir arquivo\n");
        return;
    }

    registroCab rC;
    funcLerCab(&rC, binFile);

    int posicaoAtual = 0;
    int rrnDestino = (RRN-1)* TAMREGISTRO;

    registro *r1 = malloc(sizeof(registro));
    while(posicaoAtual<rrnDestino){
        funcLer(r1, binFile);
        posicaoAtual+=76;
    }

    printRegistro(*r1);

}