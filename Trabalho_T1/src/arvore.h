#ifndef ARVORE_H
#define ARVORE_H

#define ERRO 0
#define PROMOTION 1
#define NO_PROMOTION 2

#define FOUND 1
#define NOT_FOUND 0


No *criarNo();
void readPagina(FILE *indexFile, No *no);

int posicaoChave(No *no, Chave ChaveTmp);
int posicaoFilho(No *no , Chave chaveTmp);

int buscaArvore(FILE *arquivo, int RRN, Chave busca);
int inserirArvore(FILE *arquivo, int rrnAtual, Chave chave, int *promoRFilho, Chave *promoChave);
void splitArvore(FILE *arquivo, Chave iChave, int iRRN, No *page, Chave *promoChave, int *promoRFilho,  No *newPage);
void writePagina(FILE *arquivo, No *pagina, int rrn);
void inserirChave(No *PAGE, int pos, Chave KEY, int RRN);
void defineValorNo(No *no, FILE *dadosBin);
int proximoRRNLivre(FILE *arquivo);
void printPagina(No no);

#endif 