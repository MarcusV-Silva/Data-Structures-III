#include "registro.h"

/*
*       Rodrigo Rodrigues de Castro 13695362
*
*/ 

int main(){
    char *dataBin = "saida1.bin";
    char *dataCSV = "../data/dados1.csv";
    char *dataCerto = "../data/binario5.bin";
    
    funcionalidade1(dataCSV, dataBin);
    binarioNaTela(dataBin);
    binarioNaTela(dataCerto);
    //funcionalidade2(dataCerto);
    //funcionalidade3();
    //funcionalidade4();

    return 0;
}




