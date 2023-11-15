#include "indice.h"
#include "registro.h"
#include "cabecalho.h"
#include "arvore.h"
#include "funcionalidades.h"
#include "complemento.h"

void funcionalidade5(){
    char *dataBIN = malloc(sizeof(char)*40);
    char *dataINDEX = malloc(sizeof(char)*40);
    scanf("%s %s", dataBIN, dataINDEX);

    // VERIFICAR SE A ABERTURA ESTA CORRETA
    FILE *binFile = fopen(dataBIN, "rb");
    checkFile(binFile);

    FILE *indexFile = fopen(dataINDEX, "wb");
    checkFile(binFile);

    int RRN = 19;
    int rrnDestino = (RRN * TAMREGISTRO)+13;

    //testando chave
    char con[55];
    strcpy(con, createChave(binFile, rrnDestino));
    
    printf("%s", con);

    cabIndice *indexCab = createCabecalhoIndice();
    writeCabecalhoIndice(indexFile, indexCab);

}

void funcionalidade6(){

}

void funcionalidade7(){
    
}