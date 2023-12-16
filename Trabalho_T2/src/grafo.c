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
        
        if(r->peso== -1)
            continue;

        adicionarAresta(g, *r, numVertice);
    }

    fseek(arquivo, TAM_CAB, SEEK_SET);
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

        if(r->peso== -1)
            continue;

        for(int i = 0; i< numVertice; i++){
            if(g[i].nomeOrigem != NULL && strcmp(g[i].nomeOrigem, r->nmTecnologiaOrigem) == 0)
                iOrigem = i;

            if(g[i].nomeOrigem != NULL && strcmp(g[i].nomeOrigem, r->nmTecnologiaDestino) == 0 && r->nmTecnologiaDestino != NULL )
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

    lista *novaAresta = criarNo(r);
    int aux = inserirLista(&grafo[iOrigem].iAdjacente, &novaAresta);

    if(aux){
        grafo[iOrigem].grauSaida++;
        grafo[iDestino].grauEntrada++;
    }
}

void criaGrafoTransposto(grafo *grafoI, grafo *grafoT, int numVertice){
    //imprimirGrafo(grafoI, numVertice);
    
    for(int u = 0; u < numVertice; u++){
        lista *tmp = grafoI[u].iAdjacente;
        
        while(tmp != NULL){
            int v = indiceTecnologia(tmp->nomeDestino, grafoI, numVertice);

            lista *aux = malloc(sizeof(lista));
            aux->nomeDestino = malloc(sizeof(char)*MAX_STRING);
            strcpy(aux->nomeDestino, grafoI[u].nomeOrigem);

            aux->pesoAresta = tmp->pesoAresta;

            int aux2 = inserirLista(&(grafoT[v].iAdjacente), &aux);

            if(aux2){
                grafoT[v].grauSaida++;
                grafoT[u].grauEntrada++;
            }

            tmp = tmp->prox;
        }
    }
}


int indiceTecnologia(char *nome, grafo *g, int numVertice){
    int inicio = 0;
    int fim = numVertice -1;

    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;

        int comparacao = strcmp(nome, g[meio].nomeOrigem);

        if (comparacao == 0) {
            return meio; 
        } else if (comparacao < 0) {
            fim = meio - 1; //  metade inferior
        } else {
            inicio = meio + 1; // metade superior
        }
    }
    return inicio; // Retorna a posição onde esta
}

int inserirLista(lista **listaAdj, lista **novaAresta){

    if(*listaAdj == NULL || strcmp((*novaAresta)->nomeDestino, (*listaAdj)->nomeDestino) < 0) {
        (*novaAresta)->prox = *listaAdj;
        *listaAdj = *novaAresta;   
    }else{
        lista *tmp = *listaAdj;

        if(strcmp((*novaAresta)->nomeDestino, (*listaAdj)->nomeDestino) == 0)
            return 0;

        while(tmp->prox != NULL && strcmp((*novaAresta)->nomeDestino, (*listaAdj)->nomeDestino) > 0)
            tmp = tmp->prox;
        
        (*novaAresta)->prox = tmp->prox;
        tmp->prox = *novaAresta;
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

void imprimirGrafo(grafo *g, int numVertices){
    lista *tmp;
    for(int i = 0; i<numVertices; i++){
        tmp = g[i].iAdjacente;
        while(tmp != NULL){
            printf("%s %d %d %d %d %s %d\n", g[i].nomeOrigem, g[i].iGrupo, g[i].grauEntrada, g[i].grauSaida, g[i].grauGeral, tmp->nomeDestino, tmp->pesoAresta);
            tmp = tmp->prox;
        }
    }
}

int encontrarTecnologiasOrigem(grafo *grafo, int numVertices, char *tecnologiaDestino) {
    int i;
    for (i = 0; i < numVertices; i++) {
        if (strcmp(grafo[i].nomeOrigem, tecnologiaDestino) == 0) {
            lista *adjacente = grafo[i].iAdjacente;
            while (adjacente != NULL) {
                printf("%s, ", adjacente->nomeDestino);
                adjacente = adjacente->prox;
            }
            printf("\n");
            return 1;
        }
    }

    // Se chegou aqui, a tecnologia destino não foi encontrada no grafo
  return 0;
}