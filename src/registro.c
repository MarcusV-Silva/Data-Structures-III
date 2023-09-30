#include "funcionalidades.h"
#include "funcoesFornecidas.h"
#include "arquivos.h"
#include "cabecalho.h"
#include "registro.h"

//Função que armazena os dados dos registros no arquivo binário
void writeRegistro(registro *r1, FILE *binFile){
    if(r1->grupo == 0){r1->grupo = -1;}
    if(r1->popularidade == 0){r1->popularidade = -1;}
    if(r1->peso == 0){r1->peso = -1;}

    fwrite(&r1->removido, sizeof(char), 1, binFile);
    fwrite(&r1->grupo, sizeof(int), 1, binFile);
    fwrite(&r1->popularidade, sizeof(int), 1, binFile);
    fwrite(&r1->peso, sizeof(int), 1, binFile);
    fwrite(&r1->tamTecnologiaOrigem, sizeof(int), 1, binFile);
    fwrite(r1->nmTecnologiaOrigem, sizeof(char), r1->tamTecnologiaOrigem, binFile);
    fwrite(&r1->tamTecnologiaDestino, sizeof(int), 1, binFile);
    fwrite(r1->nmTecnologiaDestino, sizeof(char), r1->tamTecnologiaDestino, binFile);

    //For para preencher os espaços vazios dos campos variáveis com '$'
    //com o objetivo de deixar todos os registros com o mesmo tamanho
    for(int l = TAMREGISTROFIXO + r1->tamTecnologiaDestino + r1->tamTecnologiaOrigem; l < TAMREGISTRO; l++){
        fwrite(LIXO, sizeof(char), 1, binFile);
    }
}

//Função que lê os registros do arquivo binário 
void readRegistro(registro *r, FILE *dataBinFile){
    r->nmTecnologiaDestino = malloc(r->tamTecnologiaDestino);
    r->nmTecnologiaOrigem = malloc(r->tamTecnologiaOrigem);

    fread(&r->removido, 1, 1, dataBinFile);
    fread(&r->grupo, sizeof(int), 1, dataBinFile);
    fread(&r->popularidade, sizeof(int), 1, dataBinFile);
    fread(&r->peso, sizeof(int), 1, dataBinFile);
    fread(&r->tamTecnologiaOrigem, sizeof(int), 1, dataBinFile);
    fread(r->nmTecnologiaOrigem, 1, r->tamTecnologiaOrigem, dataBinFile);
    fread(&r->tamTecnologiaDestino, sizeof(int), 1, dataBinFile);
    fread(r->nmTecnologiaDestino, 1, r->tamTecnologiaDestino, dataBinFile);

    //Ignora os espaços dos campos que estão preenchidos com '$'
    int qntLida = TAMREGISTROFIXO + r->tamTecnologiaDestino + r->tamTecnologiaOrigem;
    int i;
    while(qntLida < TAMREGISTRO){
        fread(&i, 1, 1, dataBinFile);
        qntLida++;
    }
}

//Função que imprime os registros campo a campo
//São feitas as devidas alterações dos campos nulos pela string 'NULO'
void printRegistro(registro r1){
    printf("%s, ", r1.nmTecnologiaOrigem);

    if (r1.grupo != -1) 
        printf("%d, ", r1.grupo);
    else 
        printf("NULO, ");
    
    if (r1.popularidade != -1) 
        printf("%d, ", r1.popularidade);
    else 
        printf("NULO, ");
    
    if (r1.tamTecnologiaDestino != 0)
        printf("%s, ", r1.nmTecnologiaDestino);
    else
        printf("NULO, ");

    if (r1.peso != -1) 
        printf("%d\n", r1.peso);
    else 
        printf("NULO\n");
}

//Função que adiciona e armazena uma nova tecnologia
void addTecnologiaUnica(char tecnologiasUnicas[][MAXSTRING], char *tecnologia, int tamanho, int *numTecnologiasUnicas) {
    if(tamanho == 0){
        return;
    }
    for (int i = 0; i < *numTecnologiasUnicas; i++) {
        if (strcmp(tecnologia, tecnologiasUnicas[i]) == 0) {
            return; 
        }
    }
    strcpy(tecnologiasUnicas[*numTecnologiasUnicas], tecnologia);
    (*numTecnologiasUnicas)++;
}

void addParUnico(char paresUnicos[][2][MAXSTRING], registro r1, int *numParesUnicos) {
    if(r1.tamTecnologiaDestino == 0){
        return;
    }

    for (int i = 0; i < *numParesUnicos; i++) {
        if (strcmp(r1.nmTecnologiaOrigem, paresUnicos[i][0]) == 0 && strcmp(r1.nmTecnologiaDestino, paresUnicos[i][1]) == 0) {
            return; 
        }
    }
    strcpy(paresUnicos[*numParesUnicos][0], r1.nmTecnologiaOrigem);
    strcpy(paresUnicos[*numParesUnicos][1], r1.nmTecnologiaDestino);
    (*numParesUnicos)++;
}

//Função que armazena os campos dos registros
char *defineCampo(char *linha, int *posicao) {
    int i = 0;
    int tamanhoMaximo = 40;
    char *campo = (char *)malloc(MAXSTRING * sizeof(char));
    
    while (linha[*posicao] != ',' && linha[*posicao] != '\0') {
        campo[i++] = linha[(*posicao)++];

        if (i >= tamanhoMaximo - 1) {
            tamanhoMaximo *= 2; 
            campo = (char *)realloc(campo, tamanhoMaximo * sizeof(char));

            if (campo == NULL) {
                exit(0);
            }
        }
    }
    campo[i] = '\0'; 

    (*posicao)++;

    return campo;
}