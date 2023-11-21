#ifndef COMPLEMENTO_H
#define COMPLEMENTO_H

// Função que verifica se o arquivo existe
void checkFile(FILE *arquivo);

// Função que libera o ponteiro do arquivo, como também fecha o arquivo
int closeFile(FILE *arquivoPonteiro, char *nomeArquivo);

// Funções fornecidas para o desenvolvimento do trabalho
void binarioNaTela(char *nomeArquivoBinario);
int scan_quote_string(char *str);

void scanfEntrada(registro *r);
void retiraVirgula(char *str);

#endif