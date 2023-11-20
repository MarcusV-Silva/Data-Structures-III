#include "indice.h"
#include "registro.h"
#include "cabecalho.h"
#include "arvore.h"
#include "funcionalidades.h"
#include "complemento.h"

void funcionalidade5(){
    
    char *dataBIN = malloc(sizeof(char) * 40);
    char *dataINDEX = malloc(sizeof(char) * 40);
    //scanf("%s %s", dataBIN, dataINDEX);
   
    strcpy(dataBIN, "binario1.bin");
    strcpy(dataINDEX, "a.bin");
    
    FILE *dataFile = fopen(dataBIN, "rb");
    checkFile(dataFile);

    FILE *indexFile = fopen(dataINDEX, "wb+");
    checkFile(indexFile);

    cabIndice *indexCab = createCabecalhoIndice();
    writeCabecalhoIndice(indexFile, indexCab);
    

    int rrnDados = 0;
    //Criando e adicionando a primeira pagina no arquivo de indice
    registroCab rC;
    readCabecalho(&rC, dataFile);
    verifyStatus(rC);

    //Criacao e definição do Primeiro no
    No *no = criarNo();

    registro *r0 = malloc(sizeof(registro));
    createRegistro(r0);
    readRegistro(r0, dataFile); //Arrumar dps
    no->RRNdoNo = 0;
    no->vetChaves[0].chave = createChave(r0);
    no->vetChaves[0].referencia = rrnDados;
    no->nroChavesNo = 1;

    rrnDados++;
    writePagina(indexFile, no, 0);

    indexCab->noRaiz = 0;
    indexCab->RRNproxNo = 0;
    writeCabecalhoIndice(indexFile, indexCab);
    Chave *promoChave = malloc(sizeof(Chave));
    int *promoRFilho = malloc(sizeof(int));

    //int totalNos = 1;  
    int flag = 0;
    while(flag != -1){    
    
        registro *r = malloc(sizeof(registro));
        if(readRegistro(r, dataFile) == 0){
            flag = -1;
            break;
        }

        Chave chaveI;
        chaveI.chave = createChave(r);
        chaveI.referencia = rrnDados;
        rrnDados++;

        int rrnRaiz = indexCab->noRaiz;
        int promo = inserirArvore(indexFile, &rrnRaiz, &chaveI, promoRFilho, promoChave);
       
        if (promo == PROMOTION) {
            readCabIndice(indexFile, indexCab);
            No *novoNo = criarNo();
            novoNo->nroChavesNo = 1;
            novoNo->alturaNo = no->alturaNo + 1;
            novoNo->vetChaves[0] = *promoChave;
            novoNo->subArvores[0] = rrnRaiz;
            novoNo->subArvores[1] = *promoRFilho;
            novoNo->RRNdoNo = ++indexCab->RRNproxNo;
            
            writePagina(indexFile, novoNo, novoNo->RRNdoNo);
            indexCab->noRaiz = novoNo->RRNdoNo;
            writeCabecalhoIndice(indexFile, indexCab);
        }

        flag++;
    }
    
    readCabIndice(indexFile, indexCab);
    indexCab->status = '1';
    indexCab->RRNproxNo++;
    writeCabecalhoIndice(indexFile, indexCab);

    fclose(indexFile);
    fclose(dataFile); 
    
    binarioNaTela(dataINDEX);
}

void funcionalidade6(){

}

void funcionalidade7(){
    
}