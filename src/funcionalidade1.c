#include "registro.h"

void funcionalidade1(char *dataCSV, char *dataBIN){
    registroCab *registroC = createCabecalho();
    
    FILE *csvFile = fopen(dataCSV, "r");
    if(!csvFile){
        printf("Erro ao abrir arquivo\n");
    }

    FILE *binFile = fopen(dataBIN, "wb");
    if(!binFile){
        printf("Erro ao abrir arquivo\n");
    }

    char tecnologiasUnicas[700][40];
    int numTecnologiasUnicas = 0;

    char paresUnicos[700][2][40];
    int numParesUnicos = 0;

    char linha[100];
    fgets(linha, sizeof(linha), csvFile);
    while (fgets(linha, sizeof(linha), csvFile)) {
        int posicao = 0;
        registroDados *r1 = malloc(sizeof(registroDados));
        int var1;

        r1->nmTecnologiaOrigem = lenCampo(linha, &posicao);
        r1->grupo = atoi(lenCampo(linha, &posicao));
        r1->popularidade = atoi(lenCampo(linha, &posicao));
        r1->nmTecnologiaDestino = lenCampo(linha, &posicao);
        r1->peso = atoi(lenCampo(linha, &posicao));
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
        if(r1->nmTecnologiaDestino == 0){r1->nmTecnologiaDestino = NULL;}
        fwrite(r1->nmTecnologiaDestino, sizeof(char), r1->tamTecnologiaDestino, binFile);

        for(int l = 21+r1->tamTecnologiaDestino+r1->tamTecnologiaOrigem; l<76; l++){
            fwrite(LIXO, sizeof(char), 1, binFile);
            posicao++;
        }

        armTec(r1, paresUnicos, tecnologiasUnicas, &numTecnologiasUnicas, &numParesUnicos);

        setHeader(registroC,numParesUnicos, numTecnologiasUnicas);
        
        free(r1->nmTecnologiaOrigem);
        free(r1->nmTecnologiaDestino);
        
        free(r1);
    }
    writeHeaderBin(binFile, registroC);

    fclose(csvFile);
    fclose(binFile);
}

void armTec(registroDados *r1, char paresUnicos[][2][40], char tecnologiasUnicas[][40], int *numTecnologiasUnicas, int *numParesUnicos) {

    int tecnologiaOrigemUnica = 1;
    for (int i = 0; i < *numTecnologiasUnicas; i++) {
        if (strcmp(r1->nmTecnologiaOrigem, tecnologiasUnicas[i]) == 0) {
            tecnologiaOrigemUnica = 0;
            break;
        }
    }

    if (tecnologiaOrigemUnica) {
        strcpy(tecnologiasUnicas[*numTecnologiasUnicas], r1->nmTecnologiaOrigem);
        (*numTecnologiasUnicas)++;
    }

    int parUnico = 1;
    for (int i = 0; i < *numParesUnicos; i++) {
        if (strcmp(r1->nmTecnologiaOrigem, paresUnicos[i][0]) == 0 &&
            strcmp(r1->nmTecnologiaDestino, paresUnicos[i][1]) == 0) {
            parUnico = 0;
            break;
        }
    }

    if (parUnico) {
        strcpy(paresUnicos[*numParesUnicos][0], r1->nmTecnologiaOrigem);
        strcpy(paresUnicos[*numParesUnicos][1], r1->nmTecnologiaDestino);
        (*numParesUnicos)++;
    }
}
    
char *lenCampo(char *linha, int *posicao) {
    char *campo = malloc(sizeof(char)*256); 
    int i = 0;
    while (linha[*posicao] != ',' && linha[*posicao] != '\0') {
        campo[i++] = linha[(*posicao)++];
    }
    (*posicao)++; 
    return campo;
}

