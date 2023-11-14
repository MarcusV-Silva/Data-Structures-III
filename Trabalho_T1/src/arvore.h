#ifndef ARVORE_H
#define ARVORE_H

#define ERRO 0
#define PROMOTION 1
#define NO_PROMOTION 2

#define FOUND 1
#define NOT_FOUND 0


No *criarNo();
int inserirArvore(FILE *arquivo, int rrnAtual, Chave chave, Chave chavePromo, int filhoPromo);
void defineValorNo(No *no, FILE *dadosBin);

#endif 