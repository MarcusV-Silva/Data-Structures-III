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

int readPagina(FILE *indexFile, No *no){

    if(fread(&no->nroChavesNo, sizeof(int), 1, indexFile) == 0){
        return 0; //fim arquivo
    }
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

    return 1;
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

        int posicao = posicaoChave(no, busca);
        if(posicao == -1)
            return FOUND;

        return buscaArvore(arquivo, no->subArvores[posicao], busca);
    }
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
int inserirArvore(FILE *arquivo, int *rrnAtual, Chave *chave, int *promoRFilho, Chave *promoChave){

    if(*rrnAtual == -1){
        *promoChave = *chave;
        *promoRFilho = -1;
        return PROMOTION;
    }else{
        No *pagina = criarNo();
        int numPagina = (*rrnAtual + 1) * TAM_PAG_INDEX;

        fseek(arquivo, numPagina, SEEK_SET);
        readPagina(arquivo, pagina);

        //verificar se essa posicao ta certa 
        int posicaoC = posicaoChave(pagina, *chave);

        if(posicaoC == -1){
            free(pagina);
            printf("Erro");
            return ERRO;
        }

        Chave *promoBKey = malloc(sizeof(Chave));
        int *rrnBPromo = malloc(sizeof(int));
        int valorRetorno = inserirArvore(arquivo, &pagina->subArvores[posicaoC], chave, rrnBPromo, promoBKey);

        if(valorRetorno == NO_PROMOTION || valorRetorno == ERRO){
            free(pagina);
            return valorRetorno;
        }else if(pagina->nroChavesNo < QNT_MAX_CHAVE){
                //no tem Espaço
                inserirChave(pagina, posicaoC, *promoBKey, *rrnBPromo);
                printPagina(*pagina);
                writePagina(arquivo, pagina, *rrnAtual+1);
                free(pagina);
                return NO_PROMOTION;
            }else{
                //no cheio 
                No *novaPag = criarNo();
                splitArvore(arquivo, promoBKey, rrnBPromo, &pagina, promoChave, promoRFilho, &novaPag);

                writePagina(arquivo, pagina, *rrnAtual);

                cabIndice *c1 = createCabecalhoIndice();
                readCabIndice(arquivo, c1);

                novaPag->RRNdoNo = ++c1->RRNproxNo;
                writePagina(arquivo, novaPag, novaPag->RRNdoNo);

                *promoRFilho = c1->RRNproxNo;
                writeCabecalhoIndice(arquivo,c1);
                        
                free(pagina);
                free(novaPag);
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
 
void splitArvore(FILE *arquivo, Chave *iChave, int *iRRN, No **page, Chave *promoChave, int *promoRFilho,  No **newPage){
    No workingPage;
    workingPage.nroChavesNo = (*page)->nroChavesNo;
    workingPage.alturaNo = (*page)->alturaNo;
    workingPage.RRNdoNo = -1;  // O RRN do novo nó será definido após a alocação

    // Copiar todas as chaves e subárvores da página original para a página temporária
    for (int i = 0; i < QNT_MAX_CHAVE; i++) {
        workingPage.vetChaves[i] = (*page)->vetChaves[i];
        workingPage.subArvores[i] = (*page)->subArvores[i];
    }
    workingPage.subArvores[QNT_MAX_CHAVE] = (*page)->subArvores[QNT_MAX_CHAVE];

    int pos = posicaoChave(&workingPage, *iChave);
    inserirChave(&workingPage, pos, *iChave, *iRRN);

    // Coloca todos os elementos da pagina como nulos
    for(int i = 0; i<QNT_MAX_CHAVE; i++){
        (*page)->vetChaves[i].chave = "";
        (*page)->vetChaves[i].referencia = -1;
        (*page)->subArvores[i] = -1;
    }
    (*page)->subArvores[QNT_MAX_CHAVE] = -1;

    (*page)->nroChavesNo = 0;
    (*page)->alturaNo = workingPage.alturaNo;

    (*newPage)->alturaNo = workingPage.alturaNo;
    (*newPage)->nroChavesNo = 0;

    for (int i = 0; i < ORDEM/2; i++) {
        (*page)->vetChaves[i] = workingPage.vetChaves[i];
        (*page)->subArvores[i] = workingPage.subArvores[i];
        (*page)->nroChavesNo++;
    }
    (*page)->subArvores[ORDEM/2] = workingPage.subArvores[ORDEM/2]; 

    *promoChave = workingPage.vetChaves[ORDEM/2]; 
    *promoRFilho = (*page)->subArvores[ORDEM/2];

    int j = 0;
    for (int i =  ORDEM/2+ 1; i < QNT_MAX_CHAVE+1; i++ ,j++) {
        (*newPage)->vetChaves[j] = workingPage.vetChaves[i];
        (*newPage)->subArvores[j] = workingPage.subArvores[i];
        (*newPage)->nroChavesNo++;
    }
    (*newPage)->subArvores[j] = workingPage.subArvores[ORDEM]; 
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
            printf("Falha no processamento do arquivo.\n");
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

    for (int i = 0; i < ORDEM+1; i++){
        printf("\nSubArvore %d = %d ",i, no.subArvores[i]);
    }

    for(int i = 0; i< QNT_MAX_CHAVE+1; i++){
        printf("\nChave %d = %s ",i, no.vetChaves[i].chave);
        printf("\nChave %d = %d ",i, no.vetChaves[i].referencia);

    }

    printf("\n\n");
}


