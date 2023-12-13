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

    if(iOrigem == -1){
        adicionarVertice(grafo, r, numVertice);
        return;
    }


    lista *novaAresta = criarNo(r);
    novaAresta->prox = grafo[iOrigem].iAdjacente;
    grafo[iOrigem].iAdjacente = novaAresta;
}

void adicionarVertice(grafo *grafo, registro r, int numVertice){
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
}




void quick_sort(lista l){
    recursive_quick(l, 0, l.size-1);
}

void recursive_quick(lista l, long ini, long end){
    long j, i, aux;

    if(ini >= end)
        return;

    i = ini;

    for(j = ini; j < end; j++)
        if(l.data[j] < l.data[end]){
            
            aux = l.data[i];
            l.data[i] = l.data[j];
            l.data[j] = aux;
            i++;
        }

    aux = l.data[i];
    l.data[i] = l.data[end];
    l.data[end] = aux;

    recursive_quick(l, ini, i-1);
    recursive_quick(l, i+1, end);
}