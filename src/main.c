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
    char *dataBin = "saidaBin.bin";
    char *dataCSV = "../data/tecnologia.csv";
 
    funcionalidade1(dataCSV, dataBin);
    binarioNaTela(dataBin);
    
    return 0;
}



