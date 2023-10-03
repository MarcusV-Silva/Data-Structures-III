#ifndef ARQUIVOS_H
#define ARQUIVOS_H

// Função que verifica se o arquivo existe
void checkFile(FILE *arquivo);

// Função que libera o ponteiro do arquivo, como também fecha o arquivo
int closeFile(FILE *arquivoPonteiro, char *nomeArquivo);

// Funções fornecidas para o desenvolvimento do trabalho
void binarioNaTela(char *nomeArquivoBinario);
void scan_quote_string(char *str);

#endif