#include "registro.h"
#include "cabecalho.h"
#include "funcionalidades.h"
#include "complemento.h"
#include "grafo.h"

void funcionalidade8(){
    char *dataBIN = malloc(sizeof(char) * 40);
    scanf("%s", dataBIN);

    FILE *dataFile = fopen(dataBIN, "rb");
    checkFile(dataFile);

    registroCab rC;
    readCabecalho(&rC, dataFile);
    verifyStatus(rC);
    printf("%d debug 0\n", rC.nroTecnologias);

    grafo *grafoFinal = criarGrafo(rC.nroTecnologias);

    int flag = 0;
    while(flag != -1){
        registro *r = malloc(sizeof(registro));
        int aux = readRegistro(r, dataFile);

        if(aux == 0){
            flag = -1;
            break;
        }

        if(aux == -1)
            continue;
        
        if(r->grupo == -1)
            continue;

        adicionarElemento(grafoFinal, *r, rC.nroTecnologias);
    }
    quickSort(grafoFinal, 0, rC.nroTecnologias-1);
    calculaGrau(grafoFinal, rC.nroTecnologias);
    imprimirGrafo(grafoFinal, rC.nroTecnologias);

    fclose(dataFile);
}


void funcionalidade9(){}
void funcionalidade10(){}
void funcionalidade11(){}
void funcionalidade12(){}