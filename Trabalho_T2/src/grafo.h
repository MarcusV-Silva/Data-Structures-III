#ifndef GRAFO_H
#define GRAFO_H


typedef struct grafo{
    int iVertice;
    int iGrupo;
    int grauEntrada;
    int grauSaida;
    int grauGeral; 
    char *nomeOrigem;
    lista *iAdjacente; 
}grafo;

typedef struct lista{
    char *nomeDestino;
    int pesoAresta;
    struct lista *prox;
}lista;



grafo *criarGrafo(int numVertices);
lista *criarNo(registro r);

void adicionarElemento(grafo *grafo, registro r, int numVertice);
void adicionarVertice(grafo *grafo, registro r, int numVertice);



#endif