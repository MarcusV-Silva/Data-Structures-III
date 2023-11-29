#include "indice.h"
#include "registro.h"
#include "cabecalho.h"
#include "complemento.h"
#include "arvore.h"
#include "funcionalidades.h"

// Função que cria os Nós utilizados na Arvore B
No *criarNo(){
    //Alocação do no
    No *no = malloc(sizeof(No));

    no->nroChavesNo = 0;
    no->alturaNo = 1;
    no->RRNdoNo = -1;

    // Um espaço vazio a mais foi criado para utilização no split
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

    
// Inserção na Arvore B por meio de um construção bottom-up
int inserirArvore(FILE *arquivo, int *rrnAtual, Chave *chave, int *promoRFilho, Chave *promoChave){

    // Verifica o RRN atual, para a construção a partir das folhas 
    if(*rrnAtual == -1){
        *promoChave = *chave;
        *promoRFilho = -1;
        return PROMOTION;
    }else{
        // Se a página não é um nó folha, a função é chamada recursivamente até que ela chegue no nó folha
        No *pagina = criarNo();
        int numPagina = (*rrnAtual + 1) * TAM_PAG_INDEX;

        // Armazenamento da pagina contida no rrn atual
        fseek(arquivo, numPagina, SEEK_SET);
        readPagina(arquivo, pagina);
       
        // Procura a posição na arvore
        int posicaoC = posicaoChave(pagina, *chave);

        if(strcmp(pagina->vetChaves[posicaoC].chave, chave->chave)==0){
            free(pagina); // A chave ja existe na pagina
            return ERRO;
        }

        // Inicio da rotina de recursão
        Chave *promoBKey = malloc(sizeof(Chave));
        int *rrnBPromo = malloc(sizeof(int));
        int valorRetorno = inserirArvore(arquivo, &pagina->subArvores[posicaoC], chave, rrnBPromo, promoBKey);
       
        // Se o valor de retorno não pedir promoção termina a rotina de recursão
        if(valorRetorno == NO_PROMOTION || valorRetorno == ERRO){
            free(pagina);
            return valorRetorno;
        }else if(pagina->nroChavesNo < QNT_MAX_CHAVE){
                // Caso haja espaço na pagina, ocorre a inserção sem Split
                inserirChave(pagina, posicaoC, *promoBKey, *rrnBPromo);
                writePagina(arquivo, pagina, *rrnAtual);
                free(pagina);
                return NO_PROMOTION;
            }else{
                // Caso em que não há espaço na pagina, necessitando que haja o Split

                // Cria uma nova Pagina
                No *novaPag = criarNo();

                // Inicia a função de Split
                splitArvore(arquivo, promoBKey, rrnBPromo, &pagina, promoChave, promoRFilho, &novaPag);

                // Inserção da pagina atual e da nova pagina, com base no valor do proximo RRN
                cabIndice *c1 = createCabecalhoIndice();
                readCabIndice(arquivo, c1);
                novaPag->RRNdoNo = c1->RRNproxNo;
                
                writePagina(arquivo, pagina, *rrnAtual);
                writePagina(arquivo, novaPag, novaPag->RRNdoNo);

                // Atualização de valores para o cabecalho e para a promoção da chave
                *promoRFilho = c1->RRNproxNo;
                c1->RRNproxNo++;
                writeCabecalhoIndice(arquivo,c1);
            
                // Liberação da memoria
                free(pagina);
                free(novaPag);
                return PROMOTION;
            }
    }   
}

// Insere a Chave na posição correta
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
 
// Função que raeliza o Split na arvore
void splitArvore(FILE *arquivo, Chave *iChave, int *iRRN, No **page, Chave *promoChave, int *promoRFilho,  No **newPage){
    // Cria uma pagina temporaria
    No workingPage;
    workingPage.nroChavesNo = (*page)->nroChavesNo;
    workingPage.alturaNo = (*page)->alturaNo;
    workingPage.RRNdoNo = -1;  

    // Copiar todas as chaves e subárvores da página original para a página temporária
    for (int i = 0; i < QNT_MAX_CHAVE; i++) {
        workingPage.vetChaves[i] = (*page)->vetChaves[i];
        workingPage.subArvores[i] = (*page)->subArvores[i];
    }
    workingPage.subArvores[QNT_MAX_CHAVE] = (*page)->subArvores[QNT_MAX_CHAVE];

    // Insere nova chave na posicao correta da pagina auxilar, utilizando o espaço auxiliar definido na struct de No
    int pos = posicaoChave(&workingPage, *iChave);
    inserirChave(&workingPage, pos, *iChave, *iRRN);

    // Coloca todos os elementos da pagina como nulos
    for(int i = 0; i<QNT_MAX_CHAVE; i++){
        (*page)->vetChaves[i].chave = "";
        (*page)->vetChaves[i].referencia = -1;
        (*page)->subArvores[i] = -1;
    }
    (*page)->subArvores[QNT_MAX_CHAVE] = -1;


    // Define os novos campos das paginas
    (*page)->nroChavesNo = 0;
    (*page)->alturaNo = workingPage.alturaNo;

    (*newPage)->alturaNo = workingPage.alturaNo;
    (*newPage)->nroChavesNo = 0;

    // Define as chaves que devem permanecer na pagina a esquerda
    for (int i = 0; i < ORDEM/2; i++) {
        (*page)->vetChaves[i] = workingPage.vetChaves[i];
        (*page)->subArvores[i] = workingPage.subArvores[i];
        (*page)->nroChavesNo++;
    }
    (*page)->subArvores[ORDEM/2] = workingPage.subArvores[ORDEM/2]; 

    // Definição da chave de promoção e do RRN de promoção
    *promoChave = workingPage.vetChaves[ORDEM/2]; 
    *promoRFilho = (*page)->subArvores[ORDEM/2];

    // Define as chaves que devem ir para nova pagina a direita
    int j = 0;
    for (int i =  ORDEM/2+ 1; i < QNT_MAX_CHAVE+1; i++ ,j++) {
        (*newPage)->vetChaves[j] = workingPage.vetChaves[i];
        (*newPage)->subArvores[j] = workingPage.subArvores[i];
        (*newPage)->nroChavesNo++;
    }
    (*newPage)->subArvores[j] = workingPage.subArvores[ORDEM]; 
}

void realizaPromocao(FILE *indexFile, cabIndice *indexCab, int *promoRFilho, Chave *promoChave){
    No *novoNo = criarNo();
    No *auxNo = criarNo();

    fseek(indexFile, TAM_PAG_INDEX*(indexCab->noRaiz+1), SEEK_SET);
    readPagina(indexFile, auxNo);

    novoNo->nroChavesNo = 1;
    novoNo->alturaNo = auxNo->alturaNo + 1;
    novoNo->vetChaves[0] = *promoChave;
    novoNo->subArvores[0] = indexCab->noRaiz;
    novoNo->subArvores[1] = *promoRFilho;

    readCabIndice(indexFile, indexCab);
    novoNo->RRNdoNo = indexCab->RRNproxNo;
    
    
    writePagina(indexFile, novoNo, novoNo->RRNdoNo);
    indexCab->noRaiz = novoNo->RRNdoNo;
    indexCab->RRNproxNo++;
    writeCabecalhoIndice(indexFile, indexCab);
}

void printPagina(No no){
    //printf("\n\nNro Chaves %d ", no.nroChavesNo);
   // printf("\nAltura %d ", no.alturaNo) ;
   printf("\nRRN no %d\n ", no.RRNdoNo);

    for (int i = 0; i < ORDEM+1; i++){
        printf("\nSubArvore %d = %d ",i, no.subArvores[i]);
    }

    for(int i = 0; i< QNT_MAX_CHAVE+1; i++){
        printf("\nChave %d = %s ",i, no.vetChaves[i].chave);
        printf(" Referencia %d = %d ",i, no.vetChaves[i].referencia);

    }

    printf("\n\n");
}