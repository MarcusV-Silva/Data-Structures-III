#ifndef ARVORE_H
#define ARVORE_H

#define ERRO 0
#define PROMOTION 1
#define NO_PROMOTION 2

#define FOUND 1
#define NOT_FOUND -1


No *criarNo();
int readPagina(FILE *indexFile, No *no);

int posicaoChave(No *no, Chave ChaveTmp);
int posicaoFilho(No *no , Chave chaveTmp);

int buscaArvore(FILE *arquivoI, FILE *arquivoD, int *RRN, int *RRNBusca, Chave* busca);
int inserirArvore(FILE *arquivo, int *rrnAtual, Chave *chave, int *promoRFilho, Chave *promoChave);
void splitArvore(FILE *arquivo, Chave *iChave, int *iRRN, No **page, Chave *promoChave, int *promoRFilho,  No **newPage);
void writePagina(FILE *arquivo, No *pagina, int rrn);
void inserirChave(No *PAGE, int pos, Chave KEY, int RRN);
int proximoRRNLivre(FILE *arquivo);
void printPagina(No no);
int ultimoRRN(FILE *arquivo);
void printArvore(FILE *arquivo);
#endif 