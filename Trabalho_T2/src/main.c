#include "indice.h"
#include "registro.h"
#include "cabecalho.h"
#include "arvore.h"
#include "funcionalidades.h"
#include "complemento.h"

/*
*                    TRABALHO 2 
*           Estrutura de Dados III (SCC0607)
*                   
*                       G-16
*       Rodrigo Rodrigues de Castro - 13695362
*         Marcus Vinicius da Silva - 13833150
*/ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(){
    int command;
    scanf("%d", &command);

    switch (command){
        case 8:
            funcionalidade8();
            break;
        case 9:
            funcionalidade9();
            break;
        case 10:
            funcionalidade10();
            break;
        case 11:
            funcionalidade11();
            break;
        case 12:
            funcionalidade12();
            break;
        default:
            printf("Falha no processamento do arquivo.\n");
            break;
    }
    return 0;
}