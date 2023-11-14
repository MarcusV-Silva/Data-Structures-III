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

    for (int i = 0; i < ORDEM; i++){
        no->subArvores[i] == -1;
    }

    for(int i = 0; i< QNT_MAX_CHAVE; i++){
        no->vetChaves[i].chave == NULL;
        no->vetChaves[i].referencia == -1;
    }

    return no;
}

void readPagina(No *no, FILE *indexFile){

    fread(&no->nroChavesNo, sizeof(int), 1, indexFile);
    fread(&no->alturaNo, sizeof(int), 1, indexFile);
    fread(&no->RRNdoNo, sizeof(int), 1, indexFile);
    
    for(int i = 0; i < ORDEM; i++){
        fread(&no->subArvores[i], sizeof(int), 1, indexFile);
        fread(&no->vetChaves[i].chave, sizeof(char), 55, indexFile);
        fread(&no->vetChaves[i].referencia, sizeof(int), 1, indexFile);
    }

    fread(&no->subArvores[ORDEM], sizeof(int), 1, indexFile);
}

int posicaoChave(No no, Chave chaveTmp){
    int posicao = 0;
    for(int i = 0; i < ORDEM; i++){
        if(strcmp(no.vetChaves[i].chave, chaveTmp.chave) == 0)
            return -1;
        if(strcmp(no.vetChaves[i].chave, chaveTmp.chave) == -1)
            posicao++;
        if(strcmp(no.vetChaves[i].chave, chaveTmp.chave) == 1)    
            return posicao;
    }
    return posicao;
}

int posicaoFilho(No no , Chave chaveTmp){
    int posicao = 0;
    for(int i = 0; i < QNT_MAX_CHAVE; i++){
        if(strcmp(no.vetChaves[i].chave, chaveTmp.chave) == 0)
            return -1;
        if(strcmp(no.vetChaves[i].chave, chaveTmp.chave) == -1)
            posicao++;
        if(strcmp(no.vetChaves[i].chave, chaveTmp.chave) == 1)    
            return posicao;
    }
    return posicao;
}

int buscaArvore(FILE *arquivo, int RRN, Chave busca){
    if(RRN == -1)
        return NOT_FOUND;
    else{
        No *no = criarNo();
        int pagina = (RRN+1) * TAM_PAG_INDEX;
        readPagina(arquivo, no);
        int posicao = posicaoChave(*no, busca);

        if(posicao == -1)
            return FOUND;
        if(no->vetChaves[posicao].chave == busca.chave){
            return FOUND;
        }else{
            int posicaoFilho = posicaoFilho(*no, busca);
            return buscaArvore(no->subArvores[posicaoFilho], busca);
        }
    }
}


// Construção bottom-up
int inserirArvore(FILE *arquivo, int rrnAtual, Chave chave, Chave chavePromo, int filhoPromo){

    if(rrnAtual == -1){
        chavePromo = chave;
        filhoPromo = NULL;
        return PROMOTION;
    }else{
        No *no = criarNo();
        int pagina = (rrnAtual+1) * TAM_PAG_INDEX;

        fseek(arquivo, pagina, SEEK_SET);
        readPagina(arquivo, no);

        //verificar se essa posicao ta certa
        int pos = posicaoChave(*no, chave);

        if(pos == -1){
            return ERRO;
        }

        Chave promoBKey;
        int rrnBPromo;
        int valorRetorno = inserirArvore(arquivo, no->subArvores[pos], chave, promoBKey, rrnBPromo);

        if(valorRetorno == NO_PROMOTION || valorRetorno == ERRO){
            return valorRetorno;
        }else if(no->nroChavesNo < QNT_MAX_CHAVE){

                no->vetChaves[pos].chave = promoBKey.chave;
                no->subArvores[pos+1] = rrnBPromo;

                no->nroChavesNo++;
                inserirNo(arquivo, no);
                return NO_PROMOTION;
            }else{

                splitArvore(arquivo, promoBKey, rrnBPromo, pagina, chavePromo, filhoPromo);




                return PROMOTION;
            }

        }
    
 }

 void splitArvores(FILE *arquivo, Chave iChave, int iRRN, Chave chavePromo, int filhoPromo,  No *newPage){


 }


