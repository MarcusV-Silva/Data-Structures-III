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

    fread(&r->removido, 1, 1, dataBinFile);
    fread(&r->grupo, sizeof(int), 1, dataBinFile);
    fread(&r->popularidade, sizeof(int), 1, dataBinFile);
    fread(&r->peso, sizeof(int), 1, dataBinFile);

    fread(&r->tamTecnologiaOrigem, sizeof(int), 1, dataBinFile);
    r->nmTecnologiaOrigem = malloc(r->tamTecnologiaOrigem+1);
    fread(r->nmTecnologiaOrigem, 1, r->tamTecnologiaOrigem, dataBinFile);
    r->nmTecnologiaOrigem[r->tamTecnologiaOrigem] = '\0';

    fread(&r->tamTecnologiaDestino, sizeof(int), 1, dataBinFile);
    r->nmTecnologiaDestino = malloc(r->tamTecnologiaDestino+1);
    fread(r->nmTecnologiaDestino, 1, r->tamTecnologiaDestino, dataBinFile);
    r->nmTecnologiaDestino[r->tamTecnologiaDestino] = '\0';

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
void addTecnologiaUnica(char tecUnic[][MAXSTRING], char *tecnologia, int tamanho, int *numTec) {
    if(tamanho == 0){
        return;
    }
    for (int i = 0; i < *numTec; i++) {
        if (strcmp(tecnologia, tecUnic[i]) == 0) {
            return; 
        }
    }
    strcpy(tecUnic[*numTec], tecnologia);
    (*numTec)++;
}

void addParUnico(char parUnic[][2][MAXSTRING], registro r1, int *numPares) {
    if(r1.tamTecnologiaDestino == 0){
        return;
    }

    for (int i = 0; i < *numPares; i++) {
        if (strcmp(r1.nmTecnologiaOrigem, parUnic[i][0]) == 0 && strcmp(r1.nmTecnologiaDestino, parUnic[i][1]) == 0) {
            return; 
        }
    }
    strcpy(parUnic[*numPares][0], r1.nmTecnologiaOrigem);
    strcpy(parUnic[*numPares][1], r1.nmTecnologiaDestino);
    (*numPares)++;
}

//Função que armazena os campos dos registros
char *defineCampo(char *linha, int *posicao) {
    int i = 0;
    char *campo = (char *)malloc(MAXSTRING * sizeof(char));
    
    while (linha[*posicao] != ',' && linha[*posicao] != '\0') {
        campo[i++] = linha[(*posicao)++];
        if (i > MAXSTRING) {
            printf("Falha no processamento do arquivo.");
            exit(0);
        }
    }
    
    campo[i] = '\0'; 

    (*posicao)++;
    return campo;
}

int freeRegistro(registro *r){
    if (r != NULL) {
        free(r->nmTecnologiaDestino);
        free(r->nmTecnologiaOrigem);
        free(r);
        return 0;
    }
    return -1;
}

void createRegistro(registro *r){
    r->removido = NAOREMOVIDO;
    r->grupo = 0;
    r->popularidade = 0;
    r->peso = 0;
    r->tamTecnologiaOrigem = 0;
    r->nmTecnologiaOrigem = NULL;
    r->tamTecnologiaDestino = 0;
    r->nmTecnologiaDestino = NULL;
}
