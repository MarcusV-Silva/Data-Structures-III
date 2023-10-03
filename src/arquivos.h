#ifndef ARQUIVOS_H
#define ARQUIVOS_H

void checkFile(FILE *arquivo);
int closeFile(FILE *arquivoPonteiro, char *nomeArquivo);

void binarioNaTela(char *nomeArquivoBinario);
void scan_quote_string(char *str);

#endif