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

    grafo *grafoFinal = criarGrafo(rC.nroTecnologias);

    printf("debug 0");
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
         printf("debug 1");
        adicionarElemento(grafoFinal, *r, rC.nroTecnologias);
    }
    imprimirGrafo(grafoFinal, rC.nroTecnologias);
}





void funcionalidade9(){}
void funcionalidade10(){}
void funcionalidade11(){}
void funcionalidade12(){}