#include "registro.h"

/*
*    Analises:
*    - as tecOrigem possuem diferentes pesos para diferentes tecDestino
*
*/ 

int main(){
    char *dataBin = "saida1.bin";
    char *dataCSV = "../data/dados1.csv";
    char *dataCerto = "../data/binario4.bin";
    
    funcionalidade1(dataCSV, dataBin);
    funcionalidade2(dataCerto);
    
    printf("\nNossos dados:");
    binarioNaTela(dataBin);

    printf("\nDados do arquivo pronto:");
    binarioNaTela(dataCerto);
    return 0;
}




