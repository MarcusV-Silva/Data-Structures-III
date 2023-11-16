#include "indice.h"
#include "registro.h"
#include "cabecalho.h"
#include "complemento.h"
#include "arvore.h"
#include "funcionalidades.h"


No *criarNo(){
    No *no = malloc(sizeof(No));

    no->nroChavesNo = 0;
    no->alturaNo = 1;
    no->RRNdoNo = -1;

    for (int i = 0; i < ORDEM; i++){
        no->subArvores[i] = -1;
    }

    for(int i = 0; i< QNT_MAX_CHAVE; i++){
        no->vetChaves[i].chave = NULL;
        no->vetChaves[i].referencia = -1;
    }

    return no;
}

void readPagina(FILE *indexFile, No *no){

    fread(&no->nroChavesNo, sizeof(int), 1, indexFile);
    fread(&no->alturaNo, sizeof(int), 1, indexFile);
    fread(&no->RRNdoNo, sizeof(int), 1, indexFile);
    
    for(int i = 0; i < QNT_MAX_CHAVE; i++){
        fread(&no->subArvores[i], sizeof(int), 1, indexFile);
        fread(no->vetChaves[i].chave, sizeof(char), 55, indexFile);
        fread(&no->vetChaves[i].referencia, sizeof(int), 1, indexFile);
    }

    fread(&no->subArvores[ORDEM-1], sizeof(int), 1, indexFile);
}

int posicaoChave(No *no, Chave *chaveTmp){
    int posicao = 0;
    for(int i = 0; i <QNT_MAX_CHAVE; i++){ 
        if(no->vetChaves[i].chave == NULL|| chaveTmp->chave == NULL) {
            return -1;
        }else{
            if(strcmp(no->vetChaves[i].chave, chaveTmp->chave) == 0)
                return -1;
            if(strcmp(no->vetChaves[i].chave, chaveTmp->chave) == -1)
                posicao++;
            if(strcmp(no->vetChaves[i].chave, chaveTmp->chave) == 1)    
                return posicao;
        }
    }
    return posicao;
}

int posicaoFilho(No *no , Chave *chaveTmp){
 int posicao = 0;
    for(int i = 0; i <ORDEM; i++){
         if(no->vetChaves[i].chave == NULL || chaveTmp->chave == NULL) {
            return -1;
        }else{
            if(strcmp(no->vetChaves[i].chave, chaveTmp->chave) == 0)
                return -1;
            if(strcmp(no->vetChaves[i].chave, chaveTmp->chave) == -1)
                posicao++;
            if(strcmp(no->vetChaves[i].chave, chaveTmp->chave) == 1)    
                return posicao;
        }
    }
    return posicao;
}

int buscaArvore(FILE *arquivo, int RRN, Chave busca){
    if(RRN == -1)
        return NOT_FOUND;
    else{
        No *no = criarNo();
        int numPagina = (RRN + 1) * TAM_PAG_INDEX;
        fseek(arquivo, numPagina, SEEK_SET);
        readPagina(arquivo, no);

        for(int i = 0; i < no->nroChavesNo; i++){
            if(strcmp(no->vetChaves[i].chave,busca.chave) == 0)
                return FOUND;
        }

        int posicaoF = posicaoFilho(no, &busca);
        if(posicaoF == -1)
            return ERRO;

        return buscaArvore(arquivo, no->subArvores[posicaoF], busca);
    }
}

int proximoRRNLivre(FILE *arquivo) {
    int rrn = 0;
    No *registro = criarNo();  // Assumindo que você tenha uma função criarNo que aloque memória para um nó

    // Percorre os registros até encontrar um registro livre ou chegar ao final do arquivo
    while (1) {
        fseek(arquivo, rrn * TAM_PAG_INDEX, SEEK_SET);
        fread(registro, sizeof(No), 1, arquivo);

        if (registro->nroChavesNo == -1) {  // Verifica se o registro está livre
            free(registro);
            return rrn;
        }

        rrn++;
    }

    free(registro);
    return rrn;  // Retorna o próximo RRN disponível caso não encontre um registro livre
}
// Construção bottom-up
int inserirArvore(FILE *arquivo, int rrnAtual, Chave chave, int *promoRFilho, Chave *promoChave){

    if(rrnAtual == -1){
        *promoChave = chave;
        *promoRFilho = -1;
        return PROMOTION;
    }else{
        No *pagina = criarNo();
        int numPagina = (rrnAtual+1) * TAM_PAG_INDEX;

        fseek(arquivo, numPagina, SEEK_SET);
        readPagina(arquivo, pagina);

        //verificar se essa posicao ta certa
        int posicaoF = posicaoFilho(pagina, &chave);
        int posicaoC = posicaoChave(pagina, &chave);

        if(posicaoF == -1){
            free(pagina);
            return ERRO;
        }

        Chave promoBKey;
        int rrnBPromo;
        int valorRetorno = inserirArvore(arquivo, pagina->subArvores[posicaoF], chave, &rrnBPromo, &promoBKey);

        if(valorRetorno == NO_PROMOTION || valorRetorno == ERRO){
            free(pagina);
            return valorRetorno;
        }else if(pagina->nroChavesNo < QNT_MAX_CHAVE){
                // Insira a chave na posição apropriada
                for (int i = pagina->nroChavesNo - 1; i >= posicaoC; i--) {
                    strcpy(pagina->vetChaves[i + 1].chave, pagina->vetChaves[i].chave);
                    pagina->subArvores[i + 2] = pagina->subArvores[i + 1];
                }
                strcpy(pagina->vetChaves[posicaoC].chave, promoBKey.chave);
                pagina->subArvores[posicaoF + 1] = rrnBPromo;
                pagina->nroChavesNo++;

                writePagina(arquivo, pagina, rrnAtual);
                free(pagina );
                return NO_PROMOTION;
            }else{
                No *newPage = criarNo();
                splitArvore(arquivo, promoBKey, rrnBPromo, pagina, promoChave, promoRFilho, &newPage);

                writePagina(arquivo, pagina, rrnAtual);
                writePagina(arquivo, newPage, *promoRFilho);

                free(pagina);
                free(newPage);
                return PROMOTION;
            }

        }
    
 }


void splitArvore(FILE *arquivo, Chave iChave, int iRRN, No *page, Chave *promoChave, int *promoRFilho,  No **newPage){
    No *novoFilho = criarNo();

    //Copias das chaves e filhos da pagina atual
    Chave tempChave[ORDEM];
    int *tempFilho[ORDEM + 1];

    // Copia de todas as chaves e ponteiros da página para a página de trabalho
    for (int i = 0; i < page->nroChavesNo; i++) {
        tempChave[i] = page->vetChaves[i];
        *tempFilho[i] = page->subArvores[i];
    }
    *tempFilho[page->nroChavesNo] = page->subArvores[page->nroChavesNo];

    // Insere a nova chave e o filho à direita na posição correta
    int j;
    for (j = page->nroChavesNo - 1; j >= 0 && strcmp(iChave.chave,tempChave[j].chave) <0; j--) {
        tempChave[j + 1] = tempChave[j];
        *tempFilho[j + 2] = *tempFilho[j + 1];
    }
    tempChave[j + 1] = iChave;
    *tempFilho[j + 2] = iRRN;

    // Calcula a posição da chave promovida
    int mid = (ORDEM) / 2;
    *promoChave = tempChave[mid];
    *promoRFilho = *tempFilho[mid + 1];

    // Copia as chaves e ponteiros precedendo a chave promovida para a página original
    for (int i = 0; i < mid; i++) {
        page->vetChaves[i] = tempChave[i];
        page->subArvores[i] = *tempFilho[i];
    }
    page->subArvores[mid] = *tempFilho[mid];

    // Copia as chaves e ponteiros seguintes à chave promovida para a nova página
    (*newPage) = novoFilho;
    (*newPage)->nroChavesNo = ORDEM - mid - 1;
    for (int i = 0; i < (*newPage)->nroChavesNo; i++) {
        (*newPage)->vetChaves[i] = tempChave[mid + 1 + i];
        (*newPage)->subArvores[i] = *tempFilho[mid + 2 + i];
    }
    (*newPage)->subArvores[(*newPage)->nroChavesNo] = *tempFilho[ORDEM];

    for (int i = 0; i < ORDEM - 1; i++) {
        free(tempChave[i].chave);
    }
}


void writePagina(FILE *arquivo, No *pagina, int rrn) {
    int posicao = rrn * TAM_PAG_INDEX;

    fseek(arquivo, posicao, SEEK_SET);

    fwrite(&pagina->nroChavesNo, sizeof(int), 1, arquivo);
    fwrite(&pagina->alturaNo, sizeof(int), 1, arquivo);
    fwrite(&pagina->RRNdoNo, sizeof(int), 1, arquivo);

    for (int i = 0; i < QNT_MAX_CHAVE; i++) {
        fwrite(&pagina->subArvores[i], sizeof(int), 1, arquivo);
        fwrite(pagina->vetChaves[i].chave, sizeof(char), TAM_CHAVE, arquivo);
        fwrite(&pagina->vetChaves[i].referencia, sizeof(int), 1, arquivo);
    }

    fwrite(&pagina->subArvores[ORDEM-1], sizeof(int), 1, arquivo);
}



void copiarNo(No *n1, No *n2){
    n1->alturaNo = n2->alturaNo;
    n1->nroChavesNo = n2->nroChavesNo;
    n1->RRNdoNo = n2->RRNdoNo;

    for (int i = 0; i < ORDEM; i++){
        n1->subArvores[i] = n2->subArvores[i];
    }
    for(int i = 0; i< QNT_MAX_CHAVE; i++){
        n1->vetChaves[i].chave = n2->vetChaves[i].chave;
        n1->vetChaves[i].referencia = n2->vetChaves[i].referencia;
    }  
}

