#ifndef GRAFO_H
#define GRAFO_H

// Struct que define os campos de uma lista de ajacencia
typedef struct lista{
    char *nomeDestino;
    int pesoAresta;
    struct lista *prox; // Ponteiro que aponta para o proximo elemento
}lista;

// Struct que define os campos de cada valor do vetor de elementos de um grafo
typedef struct grafo{
    int iVertice;
    int iGrupo;
    int grauEntrada;
    int grauSaida;
    int grauGeral; 
    char *nomeOrigem;
    lista *iAdjacente; 
}grafo;

// Struct que define a pilha utilizada na Funcionalidade 11
typedef struct pilha{
	int topo; 
	int *vet;
    int capacidade;
}pilhaTAD;

// Inicialização dos campos de um grafo
grafo *criarGrafo(int numVertices);

// Inicialização das listas de ajacencias com base no registro do arquivo binario
lista *criarNo(registro r);

// Funções que definem o vetor de elementos de um grafo
void criarVetElementos(grafo *g, int numVertice, FILE *arquivo);
void inserirVertice(grafo *grafo, char *tecnologia, int grupo, int numVertice);

// Funções que definem as listas de adjacencia do grafo
void criarListaAdjacencia(grafo *g, int numVertice, FILE *arquivo);
void adicionarAresta(grafo *grafo, registro r, int numVertice);
int inserirLista(lista **listaAdj, lista *novaAresta);

// Função que realiza a criação de um grafo transposto
void criaGrafoTransposto(grafo *grafoI, grafo *grafoT, int numVertice);

// Função que imprime o grafo
void imprimirGrafo(grafo *g, int numVertices);

// Função que calcula o grau geral de um grafo
void calculaGrau(grafo *g, int numVertices);

// Função que encontra o índice de um grafo
int indiceTecnologia(char *tecnologia, grafo *g, int numVertice);

//Função que encontra as tecnologias de origem
int encontrarTecnologiasOrigem(grafo *grafo, int numVertices, char *tecnologiaDestino);

// Funções para executar o algoritmo de Kosaraju
void preencherPilhaFinalizacao(grafo *g, int v, int visitado[], pilhaTAD* pilha, int numVertice);
void buscaProfundidade(grafo *g, int v, int visitado[], int numVertice) ;
int verificarFortementeConexo(grafo *g, grafo *grafoTransposto, int numVertice);

// Funções para executar o algoritmo de Dijkstra
int Dijkstra(grafo *g, char *nmOrigem, char *nmDestino, int numVertice);
int menorValorCaminho(int *visitado, int *caminho, int numVertice);
int menorValor(int a, int b);

// Função que libera a memoria alocada do grafo
void liberaGrafo(grafo *g, int numVertice);
#endif