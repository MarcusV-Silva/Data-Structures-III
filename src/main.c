#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "header.h"

/*
*    Analises:
*    - as tecOrigem possuem diferentes pesos para diferentes tecDestino
*
*/ 

int main(){
    char *dataBin = "saida1.bin";
    char *dataCSV = "../data/dados2.csv";
    char *dataCerto = "../data/binario5.bin";
    
    funcionalidade1(dataCSV, dataBin);
    
    printf("\nNossos dados:");
    binarioNaTela(dataBin);

    printf("\nDados do arquivo pronto:");
    binarioNaTela(dataCerto);
    return 0;
}




