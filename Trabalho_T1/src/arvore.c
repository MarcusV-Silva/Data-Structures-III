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

int buscaArvore(FILE *arquivoI, FILE *arquivoD, int *RRN, int *RRNBusca, Chave* busca){

    if(*RRN == -1){
        return printf("Registro inexistente.\n");
    }else{
        No *no = criarNo();
        int numPagina = (*RRN + 1) * TAM_PAG_INDEX;
        fseek(arquivoI, numPagina, SEEK_SET);
        readPagina(arquivoI, no);

        int posicao = posicaoChave(no, *busca);

        if(strcmp(busca->chave,no->vetChaves[posicao].chave) == 0){
            *RRNBusca = no->vetChaves[posicao].referencia;
            funcionalidade4(arquivoD, RRNBusca);
            return 0;
        }else{
            return buscaArvore(arquivoI, arquivoD, &no->subArvores[posicao], RRNBusca, busca);
        }
    }
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
            printf("Erro"); //deixar como comentario
            return ERRO;
        }

        Chave *promoBKey = malloc(sizeof(Chave));
        int *rrnBPromo = malloc(sizeof(int));
        int valorRetorno = inserirArvore(arquivo, &pagina->subArvores[posicaoC], chave, rrnBPromo, promoBKey);
        //printPagina(*pagina);
       
        if(valorRetorno == NO_PROMOTION || valorRetorno == ERRO){
            free(pagina);
            return valorRetorno;
        }else if(pagina->nroChavesNo < QNT_MAX_CHAVE){
                //no tem Espaço
                inserirChave(pagina, posicaoC, *promoBKey, *rrnBPromo);
                writePagina(arquivo, pagina, *rrnAtual);
                //printPagina(*pagina);
                free(pagina);
                return NO_PROMOTION;
            }else{
                //no cheio 
                No *novaPag = criarNo();
                splitArvore(arquivo, promoBKey, rrnBPromo, &pagina, promoChave, promoRFilho, &novaPag);

                writePagina(arquivo, pagina, *rrnAtual);

                cabIndice *c1 = createCabecalhoIndice();
                readCabIndice(arquivo, c1);

                novaPag->RRNdoNo = c1->RRNproxNo;
                writePagina(arquivo, novaPag, novaPag->RRNdoNo);
                
                *promoRFilho = c1->RRNproxNo;
                c1->RRNproxNo++;
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



