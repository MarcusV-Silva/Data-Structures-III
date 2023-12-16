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
    grafo *grafoInicial = criarGrafo(numVertices);

    criarVetElementos(grafoInicial, numVertices, dataFile);
    criarListaAdjacencia(grafoInicial, numVertices, dataFile);
    calculaGrau(grafoInicial, numVertices);

    imprimirGrafo(grafoInicial, numVertices);

    fclose(dataFile);
}


void funcionalidade9(){
    //printf("debug 0\n");
    char *dataBIN = malloc(sizeof(char) * 40);
    scanf("%s", dataBIN);

    FILE *dataFile = fopen(dataBIN, "rb");
    checkFile(dataFile);

    registroCab rC;
    readCabecalho(&rC, dataFile);
    verifyStatus(rC);

    int numVertices = rC.nroTecnologias;

    grafo *grafoInicial = criarGrafo(numVertices);
    criarVetElementos(grafoInicial, numVertices, dataFile);
    criarListaAdjacencia(grafoInicial, numVertices, dataFile);
    calculaGrau(grafoInicial, numVertices);
      
    grafo *grafoTransposto = criarGrafo(numVertices);
    criarVetElementos(grafoTransposto, numVertices, dataFile); //
    criaGrafoTransposto(grafoInicial, grafoTransposto, numVertices);
    calculaGrau(grafoTransposto, numVertices);
    imprimirGrafo(grafoTransposto, numVertices);

    fclose(dataFile);
}

void funcionalidade10(){
    int n;
    char *dataBIN = malloc(sizeof(char) * 40);
    scanf("%s %d", dataBIN, &n);

    FILE *dataFile = fopen(dataBIN, "rb");
    checkFile(dataFile);

    registroCab rC;
    readCabecalho(&rC, dataFile);
    verifyStatus(rC);

    int numVertices = rC.nroTecnologias;

    grafo *grafoInicial = criarGrafo(numVertices);
    criarVetElementos(grafoInicial, numVertices, dataFile);
    criarListaAdjacencia(grafoInicial, numVertices, dataFile);
    calculaGrau(grafoInicial, numVertices);

    for(int i = 0; i<n; i++){
        char tmp[MAX_STRING];
        scan_quote_string(tmp);
        printf("%s: ", tmp);
        int aux = encontrarTecnologiasOrigem(grafoInicial, numVertices, tmp);

        if(!aux)
            printf("Registro inexistente.");

        printf("\n");
    }
    
    fclose(dataFile);
}
void funcionalidade11(){}
void funcionalidade12(){}