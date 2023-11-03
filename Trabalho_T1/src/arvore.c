#include "indice.h"
#include "registro.h"
#include "cabecalho.h"
#include "arvore.h"
#include "funcionalidades.h"

No *criarNo(){
    No *no = malloc(sizeof(No));

    no->nroChavesNo = 0;
    no->alturaNo = 1;
    no->RRNdoNo = -1;

    for(int i = 0; i< MAX_CHAVE; i++){
        no->vetChaves[i].chave == NULL;
        no->vetChaves[i].referencia == -1;
    }

    for (int i = 0; i < ORDEM; i++){
        no->vetSubArvores[i].subArvore == -1;
    }
    
    return no;
}



int inserirArvore(int rrnAtual, Chave chave, Chave chavePromo, SubArvore *filhoPromoD, FILE *arquivo){

    if(rrnAtual == -1){
        chavePromo = chave;
        filhoPromoD = NULL;
        return PROMOTION;
    }else{
        


    }



}

