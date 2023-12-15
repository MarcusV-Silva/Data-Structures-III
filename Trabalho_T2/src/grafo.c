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

void criarListaAdjacencia(grafo *g, int numVertice, FILE *arquivo){
    int flag = 0;
    while(flag != -1){
        registro *r = malloc(sizeof(registro));
        int aux = readRegistro(r, arquivo);

        if(aux == 0){
            flag = -1;
            break;
        }

        if(aux == -1)
            continue;
        
        if(r->grupo == -1)
            continue;

        adicionarAresta(g, *r, numVertice);
    }
}
void criarVetElementos(grafo *g, int numVertice, FILE *arquivo){
    int flag = 0;
    while(flag != -1){
        int iOrigem = -1;
        int iDestino = -1;

        registro *r = malloc(sizeof(registro));
        int aux = readRegistro(r, arquivo);

        if(aux == 0){
            flag = -1;
            break;
        }

        if(aux == -1)
            continue;
        
        if(r->grupo == -1)
            continue;

        for(int i = 0; i< numVertice; i++){
            if(g[i].nomeOrigem != NULL && strcmp(g[i].nomeOrigem, r->nmTecnologiaOrigem) == 0)
                iOrigem = i;

            if(g[i].nomeOrigem != NULL && strcmp(g[i].nomeOrigem, r->nmTecnologiaDestino) == 0)
                iDestino = i;
        }

        if(iOrigem != -1 && g[iOrigem].iGrupo == -2)
            g[iOrigem].iGrupo = r->grupo;

        if(iOrigem == -1)
            inserirVertice(g, r->nmTecnologiaOrigem, r->grupo, numVertice);
        
        if(iDestino == -1)
            inserirVertice(g, r->nmTecnologiaDestino, -2, numVertice);
    }

    quickSort(g, 0, numVertice-1);
    fseek(arquivo, TAM_CAB, SEEK_SET);
}

void adicionarAresta(grafo *grafo, registro r, int numVertice){
    int iOrigem = -1;
    int iDestino = -1;

    for(int i = 0; i< numVertice; i++){
        if(grafo[i].nomeOrigem != NULL && strcmp(grafo[i].nomeOrigem, r.nmTecnologiaOrigem) == 0)
            iOrigem = i;

        if(grafo[i].nomeOrigem != NULL && strcmp(grafo[i].nomeOrigem, r.nmTecnologiaDestino) == 0)
            iDestino = i;
    }

    int aux = inserirLista(&grafo[iOrigem].iAdjacente,r);

    if(aux){
        grafo[iOrigem].grauSaida++;
        grafo[iDestino].grauEntrada++;
    }
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
    grafo[index].nomeOrigem = malloc(sizeof(char)*strlen(nome));
    strcpy(grafo[index].nomeOrigem, nome);
    grafo[index].iGrupo = grupo;

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

        int pivo = particionarVertice(g, baixo, topo);

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