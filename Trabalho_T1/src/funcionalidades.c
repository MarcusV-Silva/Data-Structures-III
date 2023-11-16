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

    FILE *dataFile = fopen(dataBIN, "rb");
    checkFile(dataFile);

    FILE *indexFile = fopen(dataINDEX, "rb");
    checkFile(indexFile);

    cabIndice *indexCab = createCabecalhoIndice();
    writeCabecalhoIndice(indexFile, indexCab);

    int flag = 0;
    while(flag != -1){
        registroCab rC;
        readCabecalho(&rC, dataFile);
        verifyStatus(rC);

        Chave chaveI;
        chaveI.chave = createChave(dataFile);
        printf("%s", chaveI.chave);
        chaveI.referencia = 1;

        int rrnRaiz = -1;
        int promoRFilho;
        Chave promoChave;
        int promo = inserirArvore(indexFile, rrnRaiz, chaveI, &promoRFilho, &promoChave );

        if (promo == 1) {
           
            // Atualiza o cabeçalho do arquivo de índice
            indexCab->noRaiz = promoRFilho;;
            writeCabecalhoIndice(indexFile, indexCab);

            // Cria nova raiz se necessário
            if (indexCab->noRaiz == -1) {
                No *novaRaiz = criarNo();
                novaRaiz->vetChaves[0] = promoChave;
                novaRaiz->subArvores[0] = rrnRaiz;
                novaRaiz->subArvores[1] = promoRFilho;
                novaRaiz->nroChavesNo = 1;

                int novaRaizRRN = proximoRRNLivre(indexFile);
                writePagina(indexFile, novaRaiz, novaRaizRRN);

                indexCab->noRaiz = novaRaizRRN;
                writeCabecalhoIndice(indexFile, indexCab);
            }
        }
    }
    
    fclose(indexFile);
    fclose(dataFile);
}

void funcionalidade6(){

}

void funcionalidade7(){
    
}