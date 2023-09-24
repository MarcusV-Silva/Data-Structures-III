#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
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

    //escreve os dados da struct de cabeçalho no .bin 
    //(ISSUE: esta escrevendo em 3 bytes a mais)
    fwrite(rC, sizeof(registroCab), 1, binFile);
    
char linha[256];
    while (fgets(linha, sizeof(linha), csvFile) != NULL) {
        registro r1;
        memset(&r1, 0, sizeof(registro)); // Inicialize a estrutura

        char *token = strtok(linha, ",");
        if (token == NULL) {
            continue; // Linha vazia
        }

        r1.removido = '1';
        r1.grupo = atoi(token);

        token = strtok(NULL, ",");
        if (token != NULL) {
            r1.popularidade = atoi(token);
        }

        token = strtok(NULL, ",");
        if (token != NULL) {
            r1.peso = atoi(token);
        }

        token = strtok(NULL, ",");
        if (token != NULL) {
            r1.tamTecnologiaOrigem = strlen(token);
            r1.nmTecnologiaOrigem = strdup(token);
        }

        token = strtok(NULL, ",");
        if (token != NULL) {
            r1.tamTecnologiaDestino = strlen(token);
            r1.nmTecnologiaDestino = strdup(token);
        }

        // Crie uma representação de registro com 76 bytes
        char registro76Bytes[76];
        criarRegistro76Bytes(&r1, registro76Bytes);

        // Escreva a representação de registro no arquivo binário

        // Escreva a representação de registro no arquivo binário
        fwrite(registro76Bytes, sizeof(char), 76, binFile);

        // Libere a memória alocada para as strings
        free(r1.nmTecnologiaOrigem);
        free(r1.nmTecnologiaDestino);
    }

    fclose(csvFile);
    fclose(binFile);

    fclose(csvFile);
    fclose(binFile);

}
void criarRegistro76Bytes(registro *r, char *registro76Bytes) {
    int offset = 0;

    // Copiar o campo 'removido'
    registro76Bytes[offset++] = r->removido;

    // Copiar o campo 'grupo', 'popularidade' e 'peso' como bytes de alta ordem
    registro76Bytes[offset++] = (r->grupo >> 24) & 0xFF;
    registro76Bytes[offset++] = (r->grupo >> 16) & 0xFF;
    registro76Bytes[offset++] = (r->grupo >> 8) & 0xFF;
    registro76Bytes[offset++] = r->grupo & 0xFF;

    registro76Bytes[offset++] = (r->popularidade >> 24) & 0xFF;
    registro76Bytes[offset++] = (r->popularidade >> 16) & 0xFF;
    registro76Bytes[offset++] = (r->popularidade >> 8) & 0xFF;
    registro76Bytes[offset++] = r->popularidade & 0xFF;

    registro76Bytes[offset++] = (r->peso >> 24) & 0xFF;
    registro76Bytes[offset++] = (r->peso >> 16) & 0xFF;
    registro76Bytes[offset++] = (r->peso >> 8) & 0xFF;
    registro76Bytes[offset++] = r->peso & 0xFF;

    // Copiar o campo 'tamTecnologiaOrigem' como bytes de alta ordem
    registro76Bytes[offset++] = (r->tamTecnologiaOrigem >> 8) & 0xFF;
    registro76Bytes[offset++] = r->tamTecnologiaOrigem & 0xFF;

    // Copiar o campo 'nmTecnologiaOrigem'
    memcpy(&registro76Bytes[offset], r->nmTecnologiaOrigem, r->tamTecnologiaOrigem);
    offset += r->tamTecnologiaOrigem;

    // Copiar o campo 'tamTecnologiaDestino' como bytes de alta ordem
    registro76Bytes[offset++] = (r->tamTecnologiaDestino >> 8) & 0xFF;
    registro76Bytes[offset++] = r->tamTecnologiaDestino & 0xFF;

    // Copiar o campo 'nmTecnologiaDestino'
    memcpy(&registro76Bytes[offset], r->nmTecnologiaDestino, r->tamTecnologiaDestino);
    offset += r->tamTecnologiaDestino;

    // Preencher o restante do registro com "$" se necessário
    while (offset < 76) {
        registro76Bytes[offset++] = '$';
    }
}
