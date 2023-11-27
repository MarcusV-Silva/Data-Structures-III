#ifndef COMPLEMENTO_H
#define COMPLEMENTO_H

#include "funcionalidades.h"

// Função que verifica se o arquivo existe
void checkFile(FILE *arquivo);

// Função que libera o ponteiro do arquivo, como também fecha o arquivo
int closeFile(FILE *arquivoPonteiro, char *nomeArquivo);

// Funções fornecidas para o desenvolvimento do trabalho
void binarioNaTela(char *nomeArquivoBinario);
int scan_quote_string(char *str);

// Função de atualização das tecnologias do arquivo de dados, com base em um registro 
void verificarTecnologias(FILE *arquivo, registro r);

// Funções utilizadas para captação das entradas na funcionalidade 7
void scanfEntrada(registro *r);
void retiraVirgula(char *str);

#endif