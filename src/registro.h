#ifndef REGISTRO_H
#define REGISTRO_H

#define REMOVIDO '1'
#define NAOREMOVIDO '0'
#define TAMREGISTRO 76
#define TAMREGISTROFIXO 21
#define LIXO "$"
#define MAX_TECNOLOGIAS 1000

typedef struct RegistersVariable{
    char removido;
    int grupo;
    int popularidade;
    int peso;
    int tamTecnologiaOrigem;
    char *nmTecnologiaOrigem;
    int tamTecnologiaDestino;
    char *nmTecnologiaDestino;
}registro;

typedef struct dataBuscas{
    char nomeCampo[40];
    char valorCampo[40];
}listBuscas;

void writeRegistro(registro *r1, FILE *binFile, int posicao);
void readRegistro(registro *r, FILE *dataBinFile);
void printRegistro(registro r1);

char *defineCampo(char *linha,int *posicao);
void addTecnologiaUnica(char tecnologiasUnicas[][40], char *tecnologia, int *numTecnologiasUnicas);

#endif