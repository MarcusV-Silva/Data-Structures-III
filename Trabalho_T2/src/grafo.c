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

    novoNo->nomeDestino = malloc(sizeof(char)*(r.tamTecnologiaDestino));
    strcpy(novoNo->nomeDestino, r.nmTecnologiaDestino);
    novoNo->pesoAresta = r.peso;
    novoNo->prox = NULL;

    return novoNo;
}


void adicionarElemento(grafo *grafo, registro r, int numVertice){
    int iOrigem = -1;
    int iDestino = -1;
    int index = 0;

    for(int i = 0; i< numVertice; i++){
        if(grafo[i].nomeOrigem != NULL && strcmp(grafo[i].nomeOrigem, r.nmTecnologiaOrigem) == 0)
            iOrigem = i;

        if(grafo[i].nomeOrigem != NULL && strcmp(grafo[i].nomeOrigem, r.nmTecnologiaDestino) == 0)
            iDestino = i;
    }

    //Encontra a ultima posicao 
    for(int i = 0; i<numVertice; i++){
        if(grafo[i].nomeOrigem == NULL){
            index = i;
            break;
        }
    }

    // Não encontrou tec origem
    if(iOrigem == -1){
        inserirVertice(grafo, r.nmTecnologiaOrigem, r.grupo, numVertice);
        iOrigem = index;
    }



    int aux = inserirLista(&grafo[iOrigem].iAdjacente,r);

    if(aux){
        grafo[iOrigem].grauSaida++;
        grafo[iDestino].grauEntrada++;
    }
    
    //printf("%s %s %s %s\n ", r.nmTecnologiaOrigem, r.nmTecnologiaDestino, grafo[iOrigem].nomeOrigem, grafo[iDestino].nomeOrigem);
}

int inserirLista(lista **listaAdj, registro r){
    lista *novaAresta = criarNo(r);

    if(*listaAdj == NULL || strcmp(novaAresta->nomeDestino, (*listaAdj)->nomeDestino) < 0) {
        novaAresta->prox = *listaAdj;
        *listaAdj = novaAresta;   
    }else{
        lista *tmp = *listaAdj;

        if(strcmp(novaAresta->nomeDestino, (*listaAdj)->nomeDestino) == 0)
            return 0;

        while(tmp->prox != NULL && strcmp(novaAresta->nomeDestino, (*listaAdj)->nomeDestino) > 0)
            tmp = tmp->prox;
        
        novaAresta->prox = tmp->prox;
        tmp->prox = novaAresta;
    }
    return 1;
}

void inserirVertice(grafo *grafo, char*nome, int grupo, int numVertice){
    int index = -1;
    for(int i = 0; i<numVertice; i++){
        if(grafo[i].nomeOrigem == NULL){
            index = i;
            break;
        }
    }
    //verificar se inedx = -1, em tese nao poderia

    //vai adicionar o novo elemento no fim para depois ordenar
    grafo[index].nomeOrigem = malloc(sizeof(char)*strlen(nome));
    strcpy(grafo[index].nomeOrigem, nome);
    grafo[index].iGrupo = grupo;

    quickSort(grafo, 0, index - 1); // ordena vetor de vertices
}


void calculaGrau(grafo *g, int numVertices){
    for(int i = 0; i<numVertices; i++){
        g[i].grauGeral = g[i].grauEntrada + g[i].grauSaida;
    }
}
int particionarVertice(grafo *g, int baixo, int topo) {
    char *pivo = malloc(sizeof(char)*strlen(g[topo].nomeOrigem));
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
            printf("%s %d %d %d %d %s %d\n", g[i].nomeOrigem, g[i].iGrupo, g[i].grauEntrada, g[i].grauSaida, g[i].grauGeral, g[i].iAdjacente->nomeDestino, g[i].iAdjacente->pesoAresta);
            g[i].iAdjacente = g[i].iAdjacente->prox;
        }
    }
}