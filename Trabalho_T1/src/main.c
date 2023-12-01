#include "indice.h"
#include "registro.h"
#include "cabecalho.h"
#include "arvore.h"
#include "funcionalidades.h"
#include "complemento.h"

/*
*                    TRABALHO 1 
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
        case 5:
            funcionalidade5();
            break;
        case 6:
            funcionalidade6();
            break;
        case 7:
            funcionalidade7();
            break;
        default:
            printf("Falha no processamento do arquivo.\n");
            break;
    }
    return 0;
}