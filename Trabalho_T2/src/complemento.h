#ifndef COMPLEMENTO_H
#define COMPLEMENTO_H

#include "funcionalidades.h"
#include "grafo.h"

// Função que verifica se o arquivo existe
void checkFile(FILE *arquivo);

// Função que libera o ponteiro do arquivo, como também fecha o arquivo
int closeFile(FILE *arquivoPonteiro, char *nomeArquivo);

// Funções fornecidas para o desenvolvimento do trabalho
void binarioNaTela(char *nomeArquivoBinario);
int scan_quote_string(char *str);

// Função de atualização das tecnologias do arquivo de dados, com base em um registro 
void verificarTecnologias(FILE *arquivo, registro r);

// Funções utilizadas para captação das entradas na funcionalidade 7
void scanfEntrada(registro *r);
void retiraVirgula(char *str);

//QuickSort para o Ordenamento dos Vertices
int particionarVertice(grafo *g, int baixo, int topo);
void quickSort(grafo *g, int baixo, int topo);

//QuickSort para o Ordanamento das Listas de Adjacencias
lista* ultimoNo(lista *l);
lista *particionarLista(lista *primeiro, lista *ultimo);
void trocaLista(lista *l1, lista *l2);
void quickSortLista(lista *primeiro, lista *ultimo);

pilhaTAD* criarPilha(int capacidade);
int pilhaVazia(pilhaTAD* pilha);
void empilhar(pilhaTAD* pilha, int item);
int desempilhar(pilhaTAD* pilha);
int topoPilha(pilhaTAD* pilha);
void liberarPilha(pilhaTAD* pilha);
#endif