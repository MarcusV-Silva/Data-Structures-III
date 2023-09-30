#include "registro.h"

//Função que inicializa as variáveis do cabeçalho
registroCab createCabecalho(){
    registroCab rC;
    rC.status = '0';
    rC.proxRRN = 0;
    rC.nroTecnologias = 0;
    rC.nroParesTecnologias = 0;
    return rC;
}

//Função que atualiza o número de pares assim como o número de tecnologias do arquivo
void setCabecalho(registroCab *rC, int numParesUnicos, int numTecnologiasUnicas){
    rC->nroParesTecnologias = numParesUnicos;
    rC->nroTecnologias = numTecnologiasUnicas;
}

//Função que acessa e armazena os dados do cabeçalho no arquivo binário
void writeCabecalho(FILE *binFile, registroCab *rC){
    fseek(binFile, 0, SEEK_SET);
    fwrite(&rC->status, sizeof(char), 1, binFile);
    fwrite(&rC->proxRRN, sizeof(int), 1, binFile);
    fwrite(&rC->nroTecnologias, sizeof(int), 1, binFile);
    fwrite(&rC->nroParesTecnologias, sizeof(int), 1, binFile);
}

//Função que lê os campos do cabeçalho
void readCabecalho(registroCab *r, FILE *dataBinFile){
    fread(&r->status, sizeof(char), 1, dataBinFile);
    fread(&r->proxRRN, sizeof(int), 1, dataBinFile);
    fread(&r->nroTecnologias, sizeof(int), 1, dataBinFile);
    fread(&r->nroParesTecnologias, sizeof(int), 1, dataBinFile);
}

//Função que armazena os dados dos registros no arquivo binário
void writeRegistro(registro *r1, FILE *binFile, int posicao){
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
        posicao++;
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
void addTecnologiaUnica(char tecnologiasUnicas[][40], char *tecnologia, int *numTecnologiasUnicas) {
    for (int i = 0; i < *numTecnologiasUnicas; i++) {
        if (strcmp(tecnologia, tecnologiasUnicas[i]) == 0) {
            return; 
        }
    }
    strcpy(tecnologiasUnicas[*numTecnologiasUnicas], tecnologia);
    (*numTecnologiasUnicas)++;
}

//Função que armazena os campos dos registros
char *defineCampo(char *linha, int *posicao) {
    int i = 0;
    int tamanhoMaximo = 40;
    char *campo = (char *)malloc(tamanhoMaximo * sizeof(char));
    
    while (linha[*posicao] != ',' && linha[*posicao] != '\0') {
        campo[i++] = linha[(*posicao)++];

        if (i >= tamanhoMaximo - 1) {
            tamanhoMaximo *= 2; 
            campo = (char *)realloc(campo, tamanhoMaximo * sizeof(char));

            if (campo == NULL) {
                exit(1);
            }
        }
    }
    campo[i] = '\0'; 

    (*posicao)++;

    return campo;
}