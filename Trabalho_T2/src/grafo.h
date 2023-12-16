#ifndef GRAFO_H
#define GRAFO_H

#define BRANCO 0
#define CINZA 1
#define PRETO 2

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
void criarListaAdjacencia(grafo *g, int numVertice, FILE *arquivo);
void criarVetElementos(grafo *g, int numVertice, FILE *arquivo);

void adicionarAresta(grafo *grafo, registro r, int numVertice);

int inserirLista(lista **listaAdj, registro r);
void inserirVertice(grafo *grafo, char*nome, int grupo, int numVertice);

int particionarVertice(grafo *g, int baixo, int topo);
void quickSort(grafo *g, int baixo, int topo);

void imprimirGrafo(grafo *g, int numVertices);
void calculaGrau(grafo *g, int numVertices);

//void calculaMin(int a, int b);
void buscaEmProfundidade(grafo *g, int numVertices, int *ehFortementeConexo, int* numComponentes);
void visitaVertice(grafo* g, int i, int numVertices,int* cor, int* pre, int* low, int* ehFortementeConexo, int* numComponentes);
void algoritmoDeTarjan(grafo* g, int numVertices);

#endif