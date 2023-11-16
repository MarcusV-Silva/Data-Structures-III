#ifndef INDICE_H
#define INDICE_H

// Definição de macros para o arquivo de indice
#define ORDEM 4
#define QNT_MAX_CHAVE ORDEM-1
#define TAM_PAG_INDEX 205
#define TAM_LIXO_CAB 196
#define TAM_CHAVE 55
#define TAM_PAG_FIXO

#define LIXO "$"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct tipoChave{
    int referencia;        // Pr (campo de referência para o registro no arquivo de dados)
    char *chave;           // C  (chave de busca)
}Chave;

// Struct onde serão armazenados os atributos de um Nó do arquivo de índice.
typedef struct No{
    int nroChavesNo;
    int alturaNo;
    int RRNdoNo;

    Chave vetChaves[QNT_MAX_CHAVE];  
    int subArvores[ORDEM];   // P (ponteiro que é campo de referência para uma subárvore)
}No;

char *createChave(FILE *arquivo);
#endif