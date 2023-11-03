#include "cabecalho.h"

cabIndice *novoCabecalhoIndice(){
    cabIndice *cabecalho = malloc(sizeof(cabIndice));

    cabecalho->status = '0';
    cabecalho->noRaiz = -1;
    cabecalho->RRNproxNo = 0;

    return cabecalho;
}