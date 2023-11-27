#ifndef INDICE_H
#define INDICE_H

// Definição de macros para o arquivo de indice
#define ORDEM 4
#define QNT_MAX_CHAVE (ORDEM-1)
#define TAM_PAG_INDEX 205
#define TAM_LIXO_CAB 196
#define TAM_CHAVE 55
#define TAM_PAG_FIXO

#define LIXO "$"

#include "funcionalidades.h"
#include "registro.h"

// Struct utilizado para o armazenamento das informações de uma chave
typedef struct tipoChave{
    int referencia;        // Pr (campo de referência para o registro no arquivo de dados)
    char *chave;           // C  (chave de busca)
}Chave;

// Struct onde serão armazenados os atributos de um Nó do arquivo de índice.
typedef struct No{
    int nroChavesNo;
    int alturaNo;
    int RRNdoNo;

    // Os seguintes campos foram criados com um espaço a mais pois sera necessario durante o split
    Chave vetChaves[QNT_MAX_CHAVE+1];  
    int subArvores[ORDEM+1];   // P (ponteiro que é campo de referência para uma subárvore)
}No;

// Funcao que concatena as strings do arquivo de dados
char *createChave(registro *r);

// Funcao que retorna a posicao correta das chaves em uma pagina
int posicaoChave(No *no, Chave ChaveTmp);

// Manipulação do arquivo de dados
int readPagina(FILE *indexFile, No *no);
void writePagina(FILE *arquivo, No *pagina, int rrn);

#endif