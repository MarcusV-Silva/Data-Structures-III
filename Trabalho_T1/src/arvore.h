#ifndef ARVORE_H
#define ARVORE_H

#define PROMOTION 2
#define NO_PROMOTION 3
#define ERROR 0

No *criarNo();
int inserirArvore(int rrnAtual, Chave chave, Chave chavePromo, SubArvore *filhoPromoD, FILE *arquivo);
void defineValorNo(No *no, File *dadosBin);

#endif 