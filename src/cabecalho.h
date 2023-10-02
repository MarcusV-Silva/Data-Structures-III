#ifndef CABECALHO_H
#define CABECALHO_H

typedef struct registroCabecalho{
    char status;
    int proxRRN;
    int nroTecnologias;
    int nroParesTecnologias;
}registroCab;

registroCab createCabecalho();
void readCabecalho(registroCab *rC, FILE *dataBinFile);
void setCabecalho(registroCab *rC, int numParesUnicos, int numTecnologiasUnicas);
void writeCabecalho(FILE *binFile, registroCab *rC);

#endif