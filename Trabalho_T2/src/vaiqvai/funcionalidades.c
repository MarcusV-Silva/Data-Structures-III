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

    grafo *grafoTransposto = criarGrafo(numVertices);
    criarVetElementos(grafoTransposto, numVertices, dataFile); //
    criaGrafoTransposto(grafoInicial, grafoTransposto, numVertices);
    calculaGrau(grafoTransposto, numVertices);

    for(int i = 0; i<n; i++){
        char tmp[MAX_STRING];
        scan_quote_string(tmp);
        printf("%s: ", tmp);

        int aux = encontrarTecnologiasOrigem(grafoTransposto, numVertices, tmp);

        if(!aux)
            printf("Registro inexistente.");

        printf("\n");
    }
    
    fclose(dataFile);
}


void funcionalidade11(){
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

    int aux = verificarFortementeConexo(grafoInicial, grafoTransposto, numVertices);

    if(aux == 1)
        printf("Sim, o grafo é fortemente conexo e possui 1 componente.");
    else
        printf("Não, o grafo não é fortemente conexo e possui %d componentes.", aux);

    fclose(dataFile);
}


void funcionalidade12(){
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
        char *tmp1 = malloc(sizeof(char)*MAX_STRING);
        char *tmp2 = malloc(sizeof(char)*MAX_STRING);
        scan_quote_string(tmp1);
        scan_quote_string(tmp2);

        //printf("%s %s:\n", tmp1, tmp2);
        int aux = algoritmoDijkstra(grafoInicial, tmp1, tmp2, numVertices);

        if(aux == -1)
            printf("%s %s: CAMINHO INEXISTENTE\n", tmp1, tmp2);
        else
            printf("%s %s: %d\n", tmp1, tmp2, aux);
    }
    
    fclose(dataFile);
}