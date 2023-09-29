#include "registro.h"

void funcionalidade1(){
    char *dataBIN = malloc(sizeof(char)*40);
    char *dataCSV = malloc(sizeof(char)*40);
    scanf("%s %s", dataCSV, dataBIN);

    registroCab *rC = (registroCab *) malloc(sizeof(registroCab));

    FILE *csvFile = fopen(dataCSV, "r");
    checkFile(csvFile);

    FILE *binFile = fopen(dataBIN, "wb");
    checkFile(binFile);

    *rC = createCabecalho();
    writeCabecalho(binFile, rC);
    
    char tecnologiasUnicas[700][40];
    int numTecnologiasUnicas = 0;
    //char paresUnicos[700][2][40];
    //int numParesUnicos = 0;

    char linha[100];
    fgets(linha,sizeof(linha) , csvFile);
    while (fgets(linha, sizeof(linha), csvFile)) {
        int posicao = 0;
        registro *r1 = malloc(sizeof(registro));

        r1->nmTecnologiaOrigem = armCampo(linha, &posicao);
        r1->grupo = atoi(armCampo(linha, &posicao));
        r1->popularidade = atoi(armCampo(linha, &posicao));
        r1->nmTecnologiaDestino = armCampo(linha, &posicao);
        r1->peso = atoi(armCampo(linha, &posicao));
        r1->removido = NAOREMOVIDO;
        r1->tamTecnologiaOrigem = strlen(r1->nmTecnologiaOrigem);
        r1->tamTecnologiaDestino = strlen(r1->nmTecnologiaDestino);

        writeRegistro(r1, binFile, posicao);

        adicionarTecnologiaUnica(tecnologiasUnicas, r1->nmTecnologiaOrigem, &numTecnologiasUnicas);
        //adicionarParUnico(paresUnicos, r1->nmTecnologiaOrigem, r1->nmTecnologiaDestino, &numParesUnicos);

        rC->proxRRN = rC->proxRRN + 1;
        rC->nroParesTecnologias = rC->nroParesTecnologias + 1;

        free(r1->nmTecnologiaOrigem);
        free(r1->nmTecnologiaDestino);
        free(r1);
    }


    //setCabecalho(rC, numParesUnicos, numTecnologiasUnicas);
    rC->nroTecnologias = numTecnologiasUnicas;
    rC->status = '1';
    writeCabecalho(binFile, rC);
    
    free(rC);

    fclose(csvFile);
    fclose(binFile);

    binarioNaTela(dataBIN);

    free(dataBIN);
    free(dataCSV);
}

void adicionarTecnologiaUnica(char tecnologiasUnicas[][40], char *tecnologia, int *numTecnologiasUnicas) {
    for (int i = 0; i < *numTecnologiasUnicas; i++) {
        if (strcmp(tecnologia, tecnologiasUnicas[i]) == 0) {
            return; 
        }
    }
    strcpy(tecnologiasUnicas[*numTecnologiasUnicas], tecnologia);
    (*numTecnologiasUnicas)++;
}

/*
void adicionarParUnico(char paresUnicos[][2][40], char *origem, char *destino, int *numParesUnicos) {
    for (int i = 0; i < *numParesUnicos; i++) {
        if (strcmp(origem, paresUnicos[i][0]) == 0 && strcmp(destino, paresUnicos[i][1]) == 0) {
            return; 
        }
    }
    strcpy(paresUnicos[*numParesUnicos][0], origem);
    strcpy(paresUnicos[*numParesUnicos][1], destino);
    (*numParesUnicos)++;
}*/
    
char *armCampo(char *linha, int *posicao) {
    int i = 0;
    int tamanhoMaximo = 40;
    char *campo = (char *)malloc(tamanhoMaximo * sizeof(char));

    if (campo == NULL) {
        fprintf(stderr, "Erro: Falha na alocação de memória para campo.\n");
        exit(1);
    }

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