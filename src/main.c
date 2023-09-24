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
    char *dataCSV = "../data/tecnologia.csv";
    char *dadoCerto = "../data/binario9.bin";
    funcionalidade1(dataCSV, dataBin);
    binarioNaTela(dataBin);
    printf("\n");
    binarioNaTela(dadoCerto);
    
    return 0;
}



