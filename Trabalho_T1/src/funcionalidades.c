#include "indice.h"
#include "registro.h"
#include "cabecalho.h"
#include "arvore.h"
#include "funcionalidades.h"
#include "complemento.h"

void funcionalidade5(){
    
    char *dataBIN = malloc(sizeof(char) * 40);
    char *dataINDEX = malloc(sizeof(char) * 40);
    scanf("%s %s", dataBIN, dataINDEX);
   
    FILE *dataFile = fopen(dataBIN, "rb");
    checkFile(dataFile);

    FILE *indexFile = fopen(dataINDEX, "wb+");
    checkFile(indexFile);

    cabIndice *indexCab = createCabecalhoIndice();
    writeCabecalhoIndice(indexFile, indexCab);
    

    int rrn = 0;
    //Criando e adicionando a primeira pagina no arquivo de indice
    registroCab rC;
    readCabecalho(&rC, dataFile);
    verifyStatus(rC);

    printf("debug 0\n");

    No *no = criarNo();
    writePagina(indexFile, no, rrn);
    
    int promoRFilho;
    int totalNos = 0;  
    Chave promoChave;

    int flag = 0;// Insira a chave na posição apropriada
    while(flag != -1){
        printf("\ndebug 1 (inicio while)\n");
    
        registro *r = malloc(sizeof(registro));
        if(readRegistro(r, dataFile) == 0){
            flag = -1;
            break;
        }

        printf("debug 2 (ler registro)\n");

        Chave chaveI;
        chaveI.chave = createChave(r);
        printf("debug 3 %s \n", chaveI.chave);
        chaveI.referencia = rrn++;

        int rrnRaiz = indexCab->noRaiz;
        printf("debug 4 (antes insercao)\n");
        int promo = inserirArvore(indexFile, rrnRaiz, chaveI, &promoRFilho, &promoChave );
        printf("%d", promo);

        printf("debug 5 (pos insercao)\n");
        if (promo == PROMOTION) {
            No *novoNo = criarNo();

            novoNo->nroChavesNo = 1;
            novoNo->alturaNo = no->alturaNo + 1;
            novoNo->vetChaves[0] = chaveI;
            novoNo->subArvores[0] = rrnRaiz;
            novoNo->subArvores[1] = promoRFilho;
            printf("debug 6 (pre promocao)\n");
            fseek(indexFile, 0 , SEEK_END);
            writePagina(indexFile, novoNo, rrnRaiz);
            indexCab->noRaiz = t;
            indexCab->RRNproxNo= ++totalNos;
            writeCabecalhoIndice(indexFile, indexCab);
            
        }
    }
    
    fclose(indexFile);
    fclose(dataFile);
}

void funcionalidade6(){

}

void funcionalidade7(){
    
}