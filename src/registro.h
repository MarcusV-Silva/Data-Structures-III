#ifndef REGISTRO_H
#define REGISTRO_H

#define REMOVIDO '1'
#define NAOREMOVIDO '0'
#define TAMREGISTRO 76
#define TAMREGISTROFIXO 21
#define LIXO "$"
#define MAXSTRING 40
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
    char nomeCampo[MAX_TECNOLOGIAS];
    char valorCampo[MAX_TECNOLOGIAS];
}listBuscas;

void writeRegistro(registro *r1, FILE *binFile);
void readRegistro(registro *r, FILE *dataBinFile);
void printRegistro(registro r1);

char *defineCampo(char *linha,int *posicao);
void addTecnologiaUnica(char tecnologiasUnicas[][MAXSTRING], char *tecnologia, int tamanho, int *numTecnologiasUnicas);
void addParUnico(char paresUnicos[][2][MAXSTRING], registro r1, int *numParesUnicos);

#endif