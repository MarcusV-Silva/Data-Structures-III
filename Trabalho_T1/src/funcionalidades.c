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
    

    int rrnDados = 0;
    int rrnIndice = 0;
    //Criando e adicionando a primeira pagina no arquivo de indice
    registroCab rC;
    readCabecalho(&rC, dataFile);
    verifyStatus(rC);

    printf("debug 0\n");

    //Criacao e definição do Primeiro no
    No *no = criarNo();

    registro *r0 = malloc(sizeof(registro));
    createRegistro(r0);
    readRegistro(r0, dataFile); //Arrumar dps

    no->vetChaves[0].chave = createChave(r0);
    no->vetChaves[0].referencia = rrnDados;
    no->nroChavesNo = 1;
    rrnDados++;
    writePagina(indexFile, no, rrnIndice);

    indexCab->noRaiz = rrnIndice;
    indexCab->RRNproxNo= -1;
    writeCabecalhoIndice(indexFile, indexCab);
    
    int totalNos = 1;  
    Chave promoChave;
    int promoRFilho;
    int flag = 0;
    while(flag < 3){    
        //testar fira do while
        
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
        chaveI.referencia = rrnDados;
        rrnDados++;

        int rrnRaiz = indexCab->noRaiz;
        printf("debug 4 (antes insercao) ");
        int promo = inserirArvore(indexFile, rrnRaiz, chaveI, &promoRFilho, &promoChave);
        printf("%d\n", promo);

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
            indexCab->noRaiz = 8;
            indexCab->RRNproxNo= ++totalNos;
            writeCabecalhoIndice(indexFile, indexCab);
            
        }
        flag++;
    }
    
    fclose(indexFile);
    fclose(dataFile);
}

void funcionalidade6(){

}

void funcionalidade7(){
    
}