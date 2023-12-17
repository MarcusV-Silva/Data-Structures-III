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


typedef struct pilha{
	int topo; 
	int *array;
    int capacidade;
}pilhaTAD;

grafo *criarGrafo(int numVertices);
lista *criarNo(registro r);
void criarListaAdjacencia(grafo *g, int numVertice, FILE *arquivo);
void criarVetElementos(grafo *g, int numVertice, FILE *arquivo);
void criaGrafoTransposto(grafo *grafoI, grafo *grafoT, int numVertice);


void adicionarAresta(grafo *grafo, registro r, int numVertice);

int inserirLista(lista **listaAdj, lista *novaAresta);
void inserirVertice(grafo *grafo, char*nome, int grupo, int numVertice);

int particionarVertice(grafo *g, int baixo, int topo);
void quickSort(grafo *g, int baixo, int topo);

void imprimirGrafo(grafo *g, int numVertices);
void calculaGrau(grafo *g, int numVertices);

int indiceTecnologia(char *nome, grafo *g, int numVertice);
int encontrarTecnologiasOrigem(grafo *grafo, int numVertices, char *tecnologiaDestino);

void preencherPilhaFinalizacao(grafo *g, int v, int visitado[], pilhaTAD* pilha, int numVertice);
void buscaProfundidade(grafo *g, int v, int visitado[], int currentComponent, int numVertice) ;
int verificarFortementeConexo(grafo *g, grafo *grafoTransposto, int numVertice);

int Dijkstra(grafo *g, char *nmOrigem, char *nmDestino, int numVertice);
int menorValorCaminho(int *visitado, int *caminho, int numVertice);
int menorValor(int a, int b);
#endif