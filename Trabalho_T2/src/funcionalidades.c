#include "registro.h"
#include "cabecalho.h"
#include "funcionalidades.h"
#include "complemento.h"
#include "grafo.h"

void funcionalidade8(){
    // Inicializa e abre o arquivo binário com base na entrada
    char *arquivoBIN = malloc(sizeof(char) * 40);
    scanf("%s", arquivoBIN);

    FILE *arquivo = fopen(arquivoBIN, "rb");
    checkFile(arquivo);

    // Verificação do Cabeçalho do arquivo binario
    registroCab rC;
    readCabecalho(&rC, arquivo);
    verifyStatus(rC);

    // Atribuição do numero total de vertices
    int numVertices = rC.nroTecnologias;

    // Criação e definição do grafo
    grafo *grafoOriginal = criarGrafo(numVertices);
    criarVetElementos(grafoOriginal, numVertices, arquivo);
    criarListaAdjacencia(grafoOriginal, numVertices, arquivo);
    calculaGrau(grafoOriginal, numVertices);

    // Impressão do grafo
    imprimirGrafo(grafoOriginal, numVertices);

    // Fechando o arquivo
    fclose(arquivo);
    free(arquivoBIN);
}


void funcionalidade9(){
    // Inicializa e abre o arquivo binário com base na entrada
    char *arquivoBIN = malloc(sizeof(char) * 40);
    scanf("%s", arquivoBIN);

    FILE *arquivo = fopen(arquivoBIN, "rb");
    checkFile(arquivo);

    // Verificação do Cabeçalho do arquivo binario
    registroCab rC;
    readCabecalho(&rC, arquivo);
    verifyStatus(rC);

    // Atribuição do numero total de vertices
    int numVertices = rC.nroTecnologias;

    // Criação e definição do grafo original
    grafo *grafoOriginal = criarGrafo(numVertices);
    criarVetElementos(grafoOriginal, numVertices, arquivo);
    criarListaAdjacencia(grafoOriginal, numVertices, arquivo);
    calculaGrau(grafoOriginal, numVertices);
      
    // Criação e definição do grafo transposto com base no grafo original
    grafo *grafoTransposto = criarGrafo(numVertices);
    criarVetElementos(grafoTransposto, numVertices, arquivo); 
    criaGrafoTransposto(grafoOriginal, grafoTransposto, numVertices);
    calculaGrau(grafoTransposto, numVertices);

    // Impressão do grafo transposto
    imprimirGrafo(grafoTransposto, numVertices);

    // Fechando o arquivo
    fclose(arquivo);
    free(arquivoBIN);
}

void funcionalidade10(){
    // Inicializa e abre o arquivo binário com base na entrada e no numero de execucoes da funcionalidade
    int n;
    char *arquivoBIN = malloc(sizeof(char) * 40);
    scanf("%s %d", arquivoBIN, &n);

    FILE *arquivo = fopen(arquivoBIN, "rb");
    checkFile(arquivo);

    // Verificação do Cabeçalho do arquivo binario
    registroCab rC;
    readCabecalho(&rC, arquivo);
    verifyStatus(rC);

    // Atribuição do numero total de vertices
    int numVertices = rC.nroTecnologias;

    // Criação e definição do grafo original
    grafo *grafoOriginal = criarGrafo(numVertices);
    criarVetElementos(grafoOriginal, numVertices, arquivo);
    criarListaAdjacencia(grafoOriginal, numVertices, arquivo);
    calculaGrau(grafoOriginal, numVertices);

    // Criação e definição do grafo transposto com base no grafo original
    grafo *grafoTransposto = criarGrafo(numVertices);
    criarVetElementos(grafoTransposto, numVertices, arquivo); //
    criaGrafoTransposto(grafoOriginal, grafoTransposto, numVertices);
    calculaGrau(grafoTransposto, numVertices);

    // Loop de execução da funcionalidade
    for(int i = 0; i<n; i++){
        char tecnologia[MAX_STRING];
        scan_quote_string(tecnologia);
        printf("%s: ", tecnologia);

        // Encontra as tecnologias que originaram o clique a tecnologia destino
        int aux = encontrarTecnologiasOrigem(grafoTransposto, numVertices, tecnologia);

        if(!aux)
            printf("Registro inexistente.");

        printf("\n");
    }
    
    // Fechando o arquivo
    fclose(arquivo);
    free(arquivoBIN);
}


void funcionalidade11(){
    // Inicializa e abre o arquivo binário com base na entrada e no numero de execucoes da funcionalidade
    char *arquivoBIN = malloc(sizeof(char) * 40);
    scanf("%s", arquivoBIN);

    FILE *arquivo = fopen(arquivoBIN, "rb");
    checkFile(arquivo);

    // Verificação do Cabeçalho do arquivo binario
    registroCab rC;
    readCabecalho(&rC, arquivo);
    verifyStatus(rC);

    // Atribuição do numero total de vertices
    int numVertices = rC.nroTecnologias;

    // Criação e definição do grafo original
    grafo *grafoOriginal = criarGrafo(numVertices);
    criarVetElementos(grafoOriginal, numVertices, arquivo);
    criarListaAdjacencia(grafoOriginal, numVertices, arquivo);
    calculaGrau(grafoOriginal, numVertices);

    // Criação e definição do grafo transposto com base no grafo original
    grafo *grafoTransposto = criarGrafo(numVertices);
    criarVetElementos(grafoTransposto, numVertices, arquivo); //
    criaGrafoTransposto(grafoOriginal, grafoTransposto, numVertices);
    calculaGrau(grafoTransposto, numVertices);

    //Verifica se o grafo é fortemente conexo e quantos componentes ele possui
    int aux = verificarFortementeConexo(grafoOriginal, grafoTransposto, numVertices);

    if(aux == 1)
        printf("Sim, o grafo é fortemente conexo e possui 1 componente.");
    else
        printf("Não, o grafo não é fortemente conexo e possui %d componentes.", aux);

    // Fechando o arquivo
    fclose(arquivo);
    free(arquivoBIN);
}


void funcionalidade12(){
    // Inicializa e abre o arquivo binário com base na entrada e no numero de execucoes da funcionalidade
    int n;
    char *arquivoBIN = malloc(sizeof(char) * 40);
    scanf("%s %d", arquivoBIN, &n);

    FILE *arquivo = fopen(arquivoBIN, "rb");
    checkFile(arquivo);

    // Verificação do Cabeçalho do arquivo binario
    registroCab rC;
    readCabecalho(&rC, arquivo);
    verifyStatus(rC);

    // Atribuição do numero total de vertices
    int numVertices = rC.nroTecnologias;

    // Criação e definição do grafo original
    grafo *grafoOriginal = criarGrafo(numVertices);
    criarVetElementos(grafoOriginal, numVertices, arquivo);
    criarListaAdjacencia(grafoOriginal, numVertices, arquivo);
    calculaGrau(grafoOriginal, numVertices);

    // Loop de execução da funcionalidade
    for(int i = 0; i<n; i++){
        char *tmp1 = malloc(sizeof(char)*MAX_STRING);
        char *tmp2 = malloc(sizeof(char)*MAX_STRING);
        scan_quote_string(tmp1);
        scan_quote_string(tmp2);

        // Encontra qual é o menor caminho entre os dois vértices
        int aux = Dijkstra(grafoOriginal, tmp1, tmp2, numVertices);

        if(aux == -1 || aux == INT_MAX)
            printf("%s %s: CAMINHO INEXISTENTE.\n", tmp1, tmp2);
        else
            printf("%s %s: %d\n", tmp1, tmp2, aux);
    }
    
    // Fechando o arquivo
    fclose(arquivo);
    free(arquivoBIN);
}