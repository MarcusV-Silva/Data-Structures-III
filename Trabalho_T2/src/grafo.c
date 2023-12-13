#include "registro.h"
#include "cabecalho.h"
#include "funcionalidades.h"
#include "complemento.h"
#include "grafo.h"

// Direcionado 
// Ponderado

grafo *criarGrafo(int numVertices){
    grafo *novoGrafo = (grafo *) malloc(numVertices*sizeof(grafo));

    if (novoGrafo == NULL) 
        exit(0);
    
    for (int i = 0; i < numVertices; i++) {
        novoGrafo[i].iVertice = -1;
        novoGrafo[i].iAdjacente = NULL;  
        novoGrafo[i].grauEntrada = 0;
        novoGrafo[i].grauGeral = 0;
        novoGrafo[i].grauSaida = 0;
        novoGrafo[i].iGrupo = -1;
        novoGrafo[i].nomeOrigem = NULL;
    }

    return novoGrafo;
}

lista *criarNo(registro r){
    lista *novoNo = (lista *)malloc(sizeof(lista));

    if (novoNo == NULL) 
        exit(0);

    novoNo->nomeDestino = malloc(sizeof(char)*r.tamTecnologiaDestino);
    strcpy(novoNo->nomeDestino, r.nmTecnologiaDestino);
    novoNo->pesoAresta = r.peso;
    novoNo->prox = NULL;

    return novoNo;
}


void adicionarElemento(grafo *grafo, registro r, int numVertice){
    int iOrigem = -1;

    for(int i = 0; i< numVertice; i++){
        if(strcmp(grafo[i].nomeOrigem, r.nmTecnologiaOrigem) == 0){
            iOrigem = i;
            break;
        }
    }

    // Não encontrou tec origem
    if(iOrigem == -1){
        inserirVertice(grafo, r, numVertice);
        return;
    }

    inserirLista(&grafo[iOrigem].iAdjacente,r);
}

void inserirLista(lista **listaAdj, registro r){
    lista *tmp = malloc(sizeof(lista));
    lista *novaAresta = criarNo(r);

    if(*listaAdj == NULL){
        novaAresta->prox = NULL;
        *listaAdj = novaAresta;
    }else if(strcmp(novaAresta->nomeDestino, (*listaAdj)->nomeDestino) < 0){
        novaAresta->prox = *listaAdj;
        *listaAdj = novaAresta;
    }else{
        tmp = *listaAdj;
        while(tmp->prox && strcmp(novaAresta->nomeDestino, tmp->prox->nomeDestino) > 0)
            tmp = tmp->prox;

        novaAresta->prox = tmp->prox;
        tmp->prox = novaAresta;
    }
}

void inserirVertice(grafo *grafo, registro r, int numVertice){
    int index = -1;
    for(int i = 0; i<numVertice; i++){
        if(grafo[i].iVertice == -1)
            index = i;
    }
    //verificar se inedx = -1, em tese nao poderia

    //vai adicionar o novo elemento no fim para depois ordenar
    grafo[index].nomeOrigem = malloc(sizeof(char)*r.tamTecnologiaOrigem);
    strcpy(grafo[index].nomeOrigem, r.nmTecnologiaOrigem);
    grafo[index].iGrupo = r.grupo;

    quickSort(grafo, 0, numVertice - 1); // ordena vetor de vertices
}

int particionarVertice(grafo *g, int baixo, int topo) {
    char pivo[MAX_STRING];
    strcpy(pivo, g[topo].nomeOrigem);

    int i = (baixo - 1);

    for (int j = baixo; j <= topo - 1; j++) {
        if (strcmp(g[j].nomeOrigem, pivo) < 0) {
            i++;
            // Trocar g[i] e g[j]
            grafo temp = g[i];
            g[i] = g[j];
            g[j] = temp;
        }
    }
    // Trocar g[i + 1] e g[topo]
    grafo temp = g[i + 1];
    g[i + 1] = g[topo];
    g[topo] = temp;

    return (i + 1);
}

// Função QuickSort para o vetor de vértices
void quickSort(grafo *g, int baixo, int topo) {
    if (baixo < topo) {
        // Obtém o índice da partição, g[pivo] agora está no lugar correto
        int pivo = particionarVertice(g, baixo, topo);

        // Recursivamente ordena os elementos antes e depois do pivo
        quickSort(g, baixo, pivo - 1);
        quickSort(g, pivo + 1, topo);
    }
}


void imprimirGrafo(grafo *g, int numVertices){
    for(int i = 0; i<numVertices; i++){
        while(g[i].iAdjacente != NULL){
            printf("%s %d %d %d %d %s %d", g[i].nomeOrigem, g[i].iGrupo, g[i].grauEntrada, g[i].grauSaida, g[i].grauGeral, g[i].iAdjacente->nomeDestino, g[i].iAdjacente->pesoAresta);
            g[i].iAdjacente = g[i].iAdjacente->prox;
        }
    }
}