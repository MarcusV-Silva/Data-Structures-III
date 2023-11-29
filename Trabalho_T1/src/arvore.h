#ifndef ARVORE_H
#define ARVORE_H

#define ERRO 0
#define PROMOTION 1
#define NO_PROMOTION 2

#define FOUND 1
#define NOT_FOUND -1

#include "funcionalidades.h"

// Função que cria um No da Arvore B
No *criarNo();

/* @brief Realiza busca na Arvore B
* @param arquivoI Arquivo de Indices
* @param arquivoD Arquivo de Dados
* @param RRN RRN do arquivo de indice que guiara a busca
* @param RRNBusca RRN do arquivo que dados que sera definido
* @param busca Chave buscada
* @return Rotina de busca
*/
int buscaArvore(FILE *arquivoI, FILE *arquivoD, int *RRN, int *RRNBusca, Chave* busca);

/*@brief - Função de inserção na Arvore B
* @param arquivo - Arquivo de indice   
* @param rrnAtual - RRN no qual começa a busca   
* @param chave - Chave que será inserida     
* @param promoRFilho - Chave promovida, caso a inserção resulte na promoção da chave
* @param promoChave - Filho promovido, caso a inserção resulte na promoção da chave
* @return - Valor que indica a ocorrencia de Promoção
*/ 
int inserirArvore(FILE *arquivo, int *rrnAtual, Chave *chave, int *promoRFilho, Chave *promoChave);

/*@brief - Função que realiza o Split na Arvore B 
* @param arquivo - Arquivo de indice 
* @param iChave - Chave que será inserida
* @param iRRN - Filho a direita da nova chave a ser inserida
* @param page - Pagina em que ocorrerá o Split
* @param promoChave - Chave que será definida para a promoção
* @param promoRFilho - RRN da Chave que será definida para a promoção
* @param newPage - Nova pagina de Disco com o particionamento à direita
*/
void splitArvore(FILE *arquivo, Chave *iChave, int *iRRN, No **page, Chave *promoChave, int *promoRFilho,  No **newPage);

/* @brief - Função que insera a chave em uma pagina na posição correta 
* @param PAGE - Pagina analisada
* @param pos - Posicao correta da Chave
* @param KEY - Chave inserida
* @param RRN - RRN do Filho a direita
*/
void inserirChave(No *PAGE, int pos, Chave KEY, int RRN);

// Função que reliza a promoção de uma chave em um arquivo de indices
void realizaPromocao(FILE *indexFile, cabIndice *indexCab, int *promoRFilho, Chave *promoChave);

#endif 