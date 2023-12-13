#ifndef GRAFO_H
#define GRAFO_H

typedef struct lista{
    char *nomeDestino;
    int pesoAresta;
    struct lista *prox;
}lista;

typedef struct grafo{
    int iVertice;
    int iGrupo;
    int grauEntrada;
    int grauSaida;
    int grauGeral; 
    char *nomeOrigem;
    lista *iAdjacente; 
}grafo;


grafo *criarGrafo(int numVertices);
lista *criarNo(registro r);

void adicionarElemento(grafo *grafo, registro r, int numVertice);
void adicionarVertice(grafo *grafo, registro r, int numVertice);

void inserirLista(lista **listaAdj, registro r);
void inserirVertice(grafo *grafo, registro r, int numVertice);

int particionarVertice(grafo *g, int baixo, int topo);
void quickSort(grafo *g, int baixo, int topo);


void imprimirGrafo(grafo *g, int numVertices);
#endif