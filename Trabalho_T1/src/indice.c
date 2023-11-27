#include "indice.h"
#include "registro.h"
#include "cabecalho.h"
#include "arvore.h"
#include "funcionalidades.h"
#include "complemento.h"

// Funcao que cria a chave, concatenando os campos de tecnologias do registro
char *createChave(registro *r){

    char *concatenada = (char *)malloc(r->tamTecnologiaDestino + r->tamTecnologiaOrigem + 1); 
    concatenada[0] = '\0';
    
    strncpy(concatenada, r->nmTecnologiaOrigem, r->tamTecnologiaOrigem);
    strncat(concatenada, r->nmTecnologiaDestino, r->tamTecnologiaDestino);

    freeRegistro(r);
   
    return concatenada;
}


// Funcao para a leitura do arquivo de indice
int readPagina(FILE *indexFile, No *no){

    // Verifica se chegou no fim arquivo
    if(fread(&no->nroChavesNo, sizeof(int), 1, indexFile) == 0){
        return 0; 
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

// Funcao que escreve uma pagina no arquivo de indice
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
        } 
        for(int j = 0; j< TAM_CHAVE - num; j++){
            // Insere $ no restante da chave
            fwrite(LIXO, sizeof(char), 1, arquivo);
        }

        fwrite(&pagina->vetChaves[i].referencia, sizeof(int), 1, arquivo);
    }

    fwrite(&pagina->subArvores[ORDEM-1], sizeof(int), 1, arquivo);
}

// Funcao que retorna a posicao correta das chaves em uma pagina
int posicaoChave(No *PAGE, Chave KEY) {
    int pos = 0;

    while (pos < PAGE->nroChavesNo && strcmp(KEY.chave, PAGE->vetChaves[pos].chave) > 0) {
        if(strcmp(KEY.chave, PAGE->vetChaves[pos].chave) == 0)
            return -1; // retorna -1 caso a chave ja exista

        pos++;
    }

    return pos;
}