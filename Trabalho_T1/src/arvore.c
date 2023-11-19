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

    for (int i = 0; i < ORDEM+1; i++){
        no->subArvores[i] = -1;
    }

    for(int i = 0; i< QNT_MAX_CHAVE+1; i++){
        no->vetChaves[i].chave = malloc(sizeof(char)* TAM_CHAVE + 1);
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
        size_t tamanho = strlen(no->vetChaves[i].chave);
        no->vetChaves[i].chave[tamanho] = '\0';
        fread(&no->vetChaves[i].referencia, sizeof(int), 1, indexFile);
    }

    fread(&no->subArvores[ORDEM-1], sizeof(int), 1, indexFile);
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

        int posicaoF = posicaoChave(no, busca);
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

int posicaoChave(No *PAGE, Chave KEY) {
    int pos = 0;

    // Encontra a posição onde a chave deve ser inserida ou onde ela está localizada
    while (pos < PAGE->nroChavesNo && strcmp(KEY.chave, PAGE->vetChaves[pos].chave) > 0) {
        if(strcmp(KEY.chave, PAGE->vetChaves[pos].chave) == 0)
            return -1;

        pos++;
    }

    return pos;
}
    
// Construção bottom-up
int inserirArvore(FILE *arquivo, int rrnAtual, Chave chave, int *promoRFilho, Chave *promoChave){

    if(rrnAtual == -1){
        *promoChave = chave;
        *promoRFilho = -1;
        return PROMOTION;
    }else{
        No *pagina = criarNo();
        int numPagina = (rrnAtual + 1) * TAM_PAG_INDEX;

        fseek(arquivo, numPagina, SEEK_SET);
        readPagina(arquivo, pagina);

        //verificar se essa posicao ta certa (dica: criar uma funcao pra ver ser ta cheio mudar posicaoF)
        int posicaoC = posicaoChave(pagina, chave);

        if(posicaoC == -1){
            free(pagina);
            return ERRO;
        }

        Chave promoBKey;
        int rrnBPromo;
        int valorRetorno = inserirArvore(arquivo, pagina->subArvores[posicaoC], chave, &rrnBPromo, &promoBKey);

        if(valorRetorno == NO_PROMOTION || valorRetorno == ERRO){
            free(pagina);
            return valorRetorno;
        }else if(pagina->nroChavesNo < QNT_MAX_CHAVE){
                
                //Inserção se o no tem Espaço
                inserirChave(pagina, posicaoC, promoBKey, rrnBPromo);
                *promoRFilho = -1; // nao ha uma subarvore a direita para ser promovida
                writePagina(arquivo, pagina, rrnAtual);
                free(pagina);
                return NO_PROMOTION;
            }else{
                //Ta cheio o no
                No *newPage = criarNo();
                splitArvore(arquivo, promoBKey, rrnBPromo, pagina, promoChave, promoRFilho, newPage);

                writePagina(arquivo, pagina, rrnAtual);
                writePagina(arquivo, newPage, *promoRFilho);

                free(pagina);
                free(newPage);
                return PROMOTION;
            }

        } 
}

void inserirChave(No *PAGE, int pos, Chave KEY, int RRN) {
    // Deslocar as chaves e subárvores para abrir espaço para a nova chave
    int i;
    for (i = PAGE->nroChavesNo; i > pos; i--) {
        PAGE->vetChaves[i] = PAGE->vetChaves[i - 1];
        PAGE->subArvores[i + 1] = PAGE->subArvores[i];
    }

    // Inserir a nova chave e RRN na posição correta
    PAGE->vetChaves[pos] = KEY;
    PAGE->subArvores[pos + 1] = RRN;

    // Atualizar o número de chaves no nó
    PAGE->nroChavesNo++;
}
 
void splitArvore(FILE *arquivo, Chave iChave, int iRRN, No *page, Chave *promoChave, int *promoRFilho,  No *newPage){

    No workingPage = *criarNo();
    workingPage.nroChavesNo = page->nroChavesNo;
    workingPage.alturaNo = page->alturaNo;
    workingPage.RRNdoNo = -1;  // O RRN do novo nó será definido após a alocação

    // Copiar todas as chaves e subárvores da página original para a página temporária
    int i;
    for (i = 0; i < QNT_MAX_CHAVE; i++) {
        workingPage.vetChaves[i] = page->vetChaves[i];
        workingPage.subArvores[i] = page->subArvores[i];
    }
    workingPage.subArvores[i] = page->subArvores[i]; // Copiar o último subárvore

    //printPagina(workingPage);

    int pos = posicaoChave(&workingPage, iChave);
    inserirChave(&workingPage, pos, iChave, iRRN);


    newPage->nroChavesNo = newPage->nroChavesNo / 2; 
    newPage->alturaNo = newPage->alturaNo;
    newPage->RRNdoNo = -1;

    // Definir PROMO_KEY como a chave no meio da página temporária
    *promoChave = workingPage.vetChaves[page->nroChavesNo / 2];

    // Definir PROMO_R_CHILD como o RRN da nova página
    *promoRFilho = page->RRNdoNo;

    // Copiar as chaves e subárvores antes e depois de PROMO_KEY para as páginas PAGE e NEWPAGE
    for (i = 0; i < page->nroChavesNo / 2; i++) {
        page->vetChaves[i] = workingPage.vetChaves[i];
        page->subArvores[i] = workingPage.subArvores[i];
    }
    page->subArvores[i] = workingPage.subArvores[i]; // Copiar o último subárvore

    int j = 0;
    for (i = page->nroChavesNo / 2 + 1; i < workingPage.nroChavesNo; i++) {
        newPage->vetChaves[j] = workingPage.vetChaves[i];
        newPage->subArvores[j] = workingPage.subArvores[i];
        j++;
    }
    newPage->subArvores[j] = workingPage.subArvores[i]; // Copiar o último subárvore

    // Atualizar o número de chaves na página original (PAGE)
    page->nroChavesNo = page->nroChavesNo / 2;
}

void writePagina(FILE *arquivo, No *pagina, int rrn) {
    int posicao = (rrn+1) * TAM_PAG_INDEX;
    int num = 0;
    fseek(arquivo, posicao, SEEK_SET);

    fwrite(&pagina->nroChavesNo, sizeof(int), 1, arquivo);
    fwrite(&pagina->alturaNo, sizeof(int), 1, arquivo);
    fwrite(&pagina->RRNdoNo, sizeof(int), 1, arquivo);

    for (int i = 0; i < QNT_MAX_CHAVE; i++) {
        fwrite(&pagina->subArvores[i], sizeof(int), 1, arquivo);
        if (pagina->vetChaves[i].chave != NULL) {
            fwrite(pagina->vetChaves[i].chave, sizeof(char), strlen(pagina->vetChaves[i].chave), arquivo);
            num = strlen(pagina->vetChaves[i].chave);
        } else {
            printf("deu erro");
        }

        for(int j = 0; j< TAM_CHAVE - num; j++){
            fwrite(LIXO, sizeof(char), 1, arquivo);
        }
        fwrite(&pagina->vetChaves[i].referencia, sizeof(int), 1, arquivo);
    }

    fwrite(&pagina->subArvores[ORDEM-1], sizeof(int), 1, arquivo);
}

// Funcao usada para debug
void printPagina(No no){
    printf("\n\nNro Chaves %d ", no.nroChavesNo);
    printf("\nAltura %d ", no.alturaNo) ;
    printf("\nRRN no %d ", no.RRNdoNo);

    for (int i = 0; i < ORDEM; i++){
        printf("\nSubArvore %d = %d ",i, no.subArvores[i]);
    }

    for(int i = 0; i< QNT_MAX_CHAVE; i++){
        printf("\nChave %d = %s ",i, no.vetChaves[i].chave);
        printf("\nChave %d = %d ",i, no.vetChaves[i].referencia);

    }
}


