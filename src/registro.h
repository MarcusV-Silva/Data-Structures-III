#ifndef REGISTRO_H
#define REGISTRO_H

// Definição de macros

#define TAMREGISTRO 76
#define TAMREGISTROFIXO 21
#define LIXO "$"

// Define um valor maximo para o tamanho das strings no registro
#define MAX_STRING 55

// Define um valor maximo para o numero de Tecnologias no arquivo .CSV 
// Não foi usado como condição de parada, mas sim como limite de dados
#define MAX_TECNOLOGIAS 1000

// Struct registro onde serão armazenados os atributos de cada registro
typedef struct registroDados{
    char removido;
    int grupo;
    int popularidade;
    int peso;
    int tamTecnologiaOrigem;
    char *nmTecnologiaOrigem;
    int tamTecnologiaDestino;
    char *nmTecnologiaDestino;
}registro;

// Lista para o armazenamento das entradas da funcionalidade 3
typedef struct dadosBuscas{
    char nomeCampo[MAX_STRING];
    char valorCampo[MAX_STRING];
}listBuscas;

// Manipulação de Registros
void createRegistro(registro *r);
void writeRegistro(registro *r1, FILE *binFile);
void printRegistro(registro r1);
void setRegistro(registro *r1,char *linha, int *posicao);
int readRegistro(registro *r, FILE *dataBinFile);
int freeRegistro(registro *r);

// Difinição dos campos de cada registro
char *defineCampo(char *linha,int *posicao);

#endif