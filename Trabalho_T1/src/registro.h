#ifndef REGISTRO_H
#define REGISTRO_H

// Definição de macros
#define ORDEM 4
#define MAX_CHAVE ORDEM-1
#define TAM_PAG_DISCO 205
#define TAM_CHAVE 55

#define LIXO "$"

// Struct onde serão armazenados os atributos de um Nó do arquivo de índice.
typedef struct No{
    int nroChavesNo;
    int alturaNo;
    int RRNdoNo;

    Chave vetChaves[MAX_CHAVE];  
    SubArvore vetSubArvores[ORDEM];   
}No;

typedef struct tipoChave{
    int referencia;        // Pr (campo de referência para o registro no arquivo de dados)
    char chave[TAM_CHAVE]; // C  (chave de busca)
}Chave;

typedef struct tipoSubArvore{
    int *subArvore;       // P   (ponteiro que é campo de referência para uma subárvore)
}SubArvore;

#endif