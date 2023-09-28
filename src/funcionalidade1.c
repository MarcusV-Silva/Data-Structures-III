#include "registro.h"

void funcionalidade1(char *dataCSV, char *dataBIN){
    registroCab *rC = (registroCab *) malloc(sizeof(registroCab));
    
    FILE *csvFile = fopen(dataCSV, "r");
    checkFile(csvFile);

    FILE *binFile = fopen(dataBIN, "wb");
    checkFile(binFile);

    *rC = createCabecalho();
    writeCabecalho(binFile, rC);
    
    char tecnologiasUnicas[700][40];
    int numTecnologiasUnicas = 0;

    char paresUnicos[700][2][40];
    int numParesUnicos = 0;

    char linha[100];
    fgets(linha, sizeof(linha), csvFile);
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

        armTec(r1, paresUnicos, tecnologiasUnicas, &numTecnologiasUnicas, &numParesUnicos);
        
        setCabecalho(rC, numParesUnicos, numTecnologiasUnicas);
        free(r1->nmTecnologiaOrigem);
        free(r1->nmTecnologiaDestino);
        free(r1);
    }

    rC->status = '1';
    writeCabecalho(binFile, rC);
    free(rC);
    fclose(csvFile);
    fclose(binFile);
}

void armTec(registro *r1, char paresUnicos[][2][40], char tecnologiasUnicas[][40], int *numTecnologiasUnicas, int *numParesUnicos) {

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
    
char *armCampo(char *linha, int *posicao) {
    char *campo = malloc(256); 
    int i = 0;
    while (linha[*posicao] != ',' && linha[*posicao] != '\0') {
        campo[i++] = linha[(*posicao)++];
    }
    (*posicao)++; 
    return campo;
}