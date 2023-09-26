#include "header.h"

void funcionalidade1(char *dataCSV, char *dataBIN){
    registroCab *rC = (registroCab *) malloc(sizeof(registroCab));
    
    FILE *csvFile = fopen(dataCSV, "r");
    if(!csvFile){
        printf("Erro ao abrir arquivo\n");
    }

    FILE *binFile = fopen(dataBIN, "wb");
    if(!binFile){
        printf("Erro ao abrir arquivo\n");
    }

    //ignora a primeira linha do .csv
    int c;
    while ((c = fgetc(csvFile)) != EOF && c != '\n') {
    }

    //inicializa registro de cabeçalho .bin
    rC->status = '1';
    rC->proxRRN = 0;
    rC->nroTecnologias = 0;
    rC->nroParesTecnologias = 0;

  
    fwrite(&rC->status, sizeof(char), 1, binFile);
    fwrite(&rC->proxRRN, sizeof(int), 1, binFile);
    fwrite(&rC->nroTecnologias, sizeof(int), 1, binFile);
    fwrite(&rC->nroParesTecnologias, sizeof(int), 1, binFile);
    

    char tecnologiasUnicas[700][40];
    int numTecnologiasUnicas = 0;

    char paresUnicos[700][2][40];
    int numParesUnicos = 0;


    char linha[100];
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

        fwrite(&r1->removido, sizeof(char), 1, binFile);

        if(r1->grupo == 0){r1->grupo = -1;}
        fwrite(&r1->grupo, sizeof(int), 1, binFile);

        if(r1->popularidade == 0){r1->popularidade = -1;}
        fwrite(&r1->popularidade, sizeof(int), 1, binFile);
        
        if(r1->peso == 0){r1->peso = -1;}
        fwrite(&r1->peso, sizeof(int), 1, binFile);

        fwrite(&r1->tamTecnologiaOrigem, sizeof(int), 1, binFile);
        fwrite(r1->nmTecnologiaOrigem, sizeof(char), r1->tamTecnologiaOrigem, binFile);
        fwrite(&r1->tamTecnologiaDestino, sizeof(int), 1, binFile);
        fwrite(r1->nmTecnologiaDestino, sizeof(char), r1->tamTecnologiaDestino, binFile);

        for(int l = 21+r1->tamTecnologiaDestino+r1->tamTecnologiaOrigem; l<76; l++){
            fwrite(LIXO, sizeof(char), 1, binFile);
            posicao++;
        }
        armTec(r1, paresUnicos, tecnologiasUnicas, &numTecnologiasUnicas, &numParesUnicos);
        rC->proxRRN = rC->proxRRN + 1;
        free(r1);
    }
    rC->nroParesTecnologias = numParesUnicos;
    rC->nroTecnologias = numTecnologiasUnicas;
    newRegCab(binFile,rC);

    fclose(csvFile);
    fclose(binFile);
}

void armTec(registro *r1, char paresUnicos[][2][40], char tecnologiasUnicas[][40], int *numTecnologiasUnicas, int *numParesUnicos) {
    // Verifica se a tecnologia de origem é única
    int tecnologiaOrigemUnica = 1;
    for (int i = 0; i < *numTecnologiasUnicas; i++) {
        if (strcmp(r1->nmTecnologiaOrigem, tecnologiasUnicas[i]) == 0) {
            tecnologiaOrigemUnica = 0;
            break;
        }
    }

    // Se for única, adiciona ao conjunto de tecnologias únicas
    if (tecnologiaOrigemUnica) {
        strcpy(tecnologiasUnicas[*numTecnologiasUnicas], r1->nmTecnologiaOrigem);
        (*numTecnologiasUnicas)++;
    }

    // Verifica se o par é único
    int parUnico = 1;
    for (int i = 0; i < *numParesUnicos; i++) {
        if (strcmp(r1->nmTecnologiaOrigem, paresUnicos[i][0]) == 0 &&
            strcmp(r1->nmTecnologiaDestino, paresUnicos[i][1]) == 0) {
            parUnico = 0;
            break;
        }
    }

    // Se for único, adiciona ao conjunto de pares únicos
    if (parUnico) {
        strcpy(paresUnicos[*numParesUnicos][0], r1->nmTecnologiaOrigem);
        strcpy(paresUnicos[*numParesUnicos][1], r1->nmTecnologiaDestino);
        (*numParesUnicos)++;
    }
}
    
char *armCampo(char *linha, int *posicao) {
    char *campo = malloc(256); 
    int i = 0;
    while (linha[*posicao] != ',' && linha[*posicao] != '\0') {
        campo[i++] = linha[(*posicao)++];
    }
    (*posicao)++; 
    return campo;
}

void newRegCab(FILE *binFile, registroCab *r1){
    fseek(binFile, 1, SEEK_SET);
    fwrite(&r1->proxRRN, sizeof(int), 1, binFile);
    fwrite(&r1->nroTecnologias, sizeof(int), 1, binFile);
    fwrite(&r1->nroParesTecnologias, sizeof(int), 1, binFile);
    
}
