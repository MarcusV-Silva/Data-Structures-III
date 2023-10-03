#include "funcionalidades.h"
#include "funcoesFornecidas.h"
#include "arquivos.h"
#include "cabecalho.h"
#include "registro.h"

//Função que verifica se o arquivo existe
void checkFile(FILE *arquivo){
    if (arquivo == NULL) {
        printf("Falha no processamento do arquivo.\n");
        exit(0);
    }
}

int closeFile(FILE *arquivoPonteiro, char *nomeArquivo){
    free(nomeArquivo);
    fclose(arquivoPonteiro);
    return 0;
}