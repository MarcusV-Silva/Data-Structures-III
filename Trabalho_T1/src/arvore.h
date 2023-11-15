#ifndef ARVORE_H
#define ARVORE_H

#define ERRO 0
#define PROMOTION 1
#define NO_PROMOTION 2

#define FOUND 1
#define NOT_FOUND 0


No *criarNo();
void readPagina(FILE *indexFile, No *no);
int posicaoChave(No no, Chave chaveTmp);
int posicaoFilho(No no , Chave chaveTmp);

int buscaArvore(FILE *arquivo, int RRN, Chave busca);
int inserirArvore(FILE *arquivo, int rrnAtual, Chave chave, int filhoPromo, Chave chavePromo);
void splitArvore(FILE *arquivo, Chave iChave, int iRRN, Chave chavePromo, int filhoPromo,  No *newPage);

void defineValorNo(No *no, FILE *dadosBin);

#endif 