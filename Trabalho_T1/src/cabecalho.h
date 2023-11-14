#ifndef CABECALHO_H
#define CABECALHO_H


// Struct referente aos dados do cabeçalho do arquivo
typedef struct cabecalhoIndice{
    char status;
    int noRaiz;
    int RRNproxNo;
}cabIndice;

cabIndice *novoCabecalhoIndice();

#endif