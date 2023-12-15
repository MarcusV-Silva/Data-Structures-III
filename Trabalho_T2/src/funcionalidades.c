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

    int numVertices = rC.nroTecnologias;
    grafo *grafoFinal = criarGrafo(numVertices);
    
    criarVetElementos(grafoFinal, numVertices, dataFile);
    criarListaAdjacencia(grafoFinal, numVertices, dataFile);

    calculaGrau(grafoFinal, numVertices);

    imprimirGrafo(grafoFinal, numVertices);

    fclose(dataFile);
}


void funcionalidade9(){}
void funcionalidade10(){}
void funcionalidade11(){}
void funcionalidade12(){}