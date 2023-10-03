#include "funcionalidades.h"
#include "funcoesFornecidas.h"
#include "arquivos.h"
#include "cabecalho.h"
#include "registro.h"

void funcionalidade1(){

    //Inicializa e abre os arquivos csv e binário
    char *dataBIN = malloc(sizeof(char)*40);
    char *dataCSV = malloc(sizeof(char)*40);
    scanf("%s %s", dataCSV, dataBIN);

    FILE *csvFile = fopen(dataCSV, "r");
    checkFile(csvFile);

    FILE *binFile = fopen(dataBIN, "wb");
    checkFile(binFile);

    registroCab rC; 
    createCabecalho(&rC);
    writeCabecalho(binFile, &rC);
    
    char tecUnic[MAX_TECNOLOGIAS][MAX_STRING];
    int numTecnologias = 0;
    char parUnic[MAX_TECNOLOGIAS][2][MAX_STRING];
    int numPares = 0;

    char linha[100];
    fgets(linha,sizeof(linha) , csvFile);//Pula a primeira linha do arquivo

    while (fgets(linha, sizeof(linha), csvFile)) {
        int posicao = 0;
        registro *r1 = malloc(sizeof(registro));
        createRegistro(r1);
    
        r1->nmTecnologiaOrigem = defineCampo(linha, &posicao);
        char *grupoStr = defineCampo(linha, &posicao);
        char *popularidadeStr = defineCampo(linha, &posicao);
        r1->nmTecnologiaDestino = defineCampo(linha, &posicao);
        char *pesoStr = defineCampo(linha, &posicao);
        
        r1->grupo = atoi(grupoStr);
        r1->popularidade = atoi(popularidadeStr);
        r1->peso = atoi(pesoStr);
        r1->tamTecnologiaOrigem = strlen(r1->nmTecnologiaOrigem);
        r1->tamTecnologiaDestino = strlen(r1->nmTecnologiaDestino);

        //Função que armazena os dados no arquivo binário
        writeRegistro(r1, binFile);
        
        //Função que armazena uma tecnologia recém adicionada 
        addTecnologiaUnica(tecUnic, r1->nmTecnologiaOrigem, r1->tamTecnologiaOrigem, &numTecnologias);
        addTecnologiaUnica(tecUnic, r1->nmTecnologiaDestino, r1->tamTecnologiaDestino, &numTecnologias);
        addParUnico(parUnic, *r1, &numPares);

        rC.proxRRN = rC.proxRRN + 1;

        free(grupoStr);
        free(popularidadeStr);
        free(pesoStr);

        freeRegistro(r1);
    }

    setCabecalho(&rC, numPares, numTecnologias);

    //Atualiza o status, o número de tecnologias e o cabeçalho do arquivo
    writeCabecalho(binFile, &rC);

    fclose(csvFile);
    fclose(binFile);

    binarioNaTela(dataBIN);

    free(dataBIN);
    free(dataCSV);
}

void funcionalidade2() {
    //Inicializa o arquivo binário  e verifica se ele existe
    char *dataBin = malloc(sizeof(char)*40);
    scanf("%s", dataBin);

    FILE *binFile = fopen(dataBin, "rb");
    checkFile(binFile);
    
    //Aloca memória e lê o cabeçalho do arquivo
    registroCab rC; 
    readCabecalho(&rC, binFile);
    verifyStatus(rC);

    int flag = 0;
    //Percorre o arquivo e imprime-o
    for (int i = 0; i < MAX_TECNOLOGIAS; i++){
        registro *r = malloc(sizeof(registro));
        createRegistro(r);

        //Função que lê um registro do arquivo
        if(readRegistro(r, binFile) == 0 && flag == 0){
            freeRegistro(r);
            printf("Registro inexistente.\n");
            break;
        }

        if(readRegistro(r, binFile) == 0 ){
            freeRegistro(r);
            break;
        }
        printRegistro(*r);//Função que impŕime um registro do arquivo
        freeRegistro(r);
        flag++;   
    }

    closeFile(binFile, dataBin);
}

void funcionalidade3(){
    //Inicializa o arquivo binário  e verifica se ele existe
    int n;
    char *dataBin = malloc(sizeof(char)*40);
    scanf("%s %d", dataBin, &n);

    FILE *binFile = fopen(dataBin, "rb");
    checkFile(binFile);

    //Lê o cabeçalho do arquivo
    registroCab rC;
    readCabecalho(&rC, binFile);
    verifyStatus(rC);

    int contador = 0;
    listBuscas dadosBuscas[MAX_STRING];
    char tmp1[MAX_STRING];
    char tmp2[MAX_STRING];

    while(scanf("%s", tmp1) != EOF){
        scan_quote_string(tmp2);
        strcpy(dadosBuscas[contador].nomeCampo,tmp1);
        strcpy(dadosBuscas[contador].valorCampo,tmp2);
        contador++;
    }

    if(contador>n){
        printf("Falha no processamento do arquivo.");
        exit(-1);
    }

    //For para fazer as buscas solicitadas
    for(int i = 0; i<n; i++){
        int flag = 0;
        //For que percorre o arquivo para encontrar os registros
        for(int j = 0; j < MAX_TECNOLOGIAS; j++) {
            int registroEncontrado = 0;
            registro *r1 = malloc(sizeof(registro)+1);
            createRegistro(r1);
            if(readRegistro(r1, binFile) == 0){
                freeRegistro(r1);
                break;
            }
            //Lê um registro do arquivo binário
            //Cadeia de if e else para verificar a existência dos campos do registro
            if (strcmp(dadosBuscas[i].nomeCampo, "nomeTecnologiaOrigem") == 0 && strcmp(r1->nmTecnologiaOrigem, dadosBuscas[i].valorCampo) == 0) {
                registroEncontrado = 1;
            } else if (strcmp(dadosBuscas[i].nomeCampo, "nomeTecnologiaDestino") == 0 && strcmp(r1->nmTecnologiaDestino, dadosBuscas[i].valorCampo) == 0) {
                registroEncontrado = 1;
            } else if (strcmp(dadosBuscas[i].nomeCampo, "grupo") == 0 && r1->grupo == atoi(dadosBuscas[i].valorCampo)){
                registroEncontrado = 1;
            } else if (strcmp(dadosBuscas[i].nomeCampo, "popularidade") == 0 && r1->popularidade == atoi(dadosBuscas[i].valorCampo)){
                registroEncontrado = 1;
            } else if (strcmp(dadosBuscas[i].nomeCampo, "peso") == 0 && r1->peso == atoi(dadosBuscas[i].valorCampo)){
                registroEncontrado = 1;
            }
            if(registroEncontrado){
                printRegistro(*r1);
                flag = 1;
            }
            freeRegistro(r1);
        }
        if(!flag)
            printf("Registro inexistente.\n");

        fseek(binFile, 13, SEEK_SET);
    }

    closeFile(binFile, dataBin);
}

void funcionalidade4(){
    //Inicializa o arquivo binário  e verifica se ele existe
    char *dataBin = malloc(sizeof(char)*40);
    int RRN;
    scanf("%s %d", dataBin, &RRN);

    FILE *binFile = fopen(dataBin, "rb");
    checkFile(binFile);
    
    //Lê o cabeçalho do arquivo
    registroCab rC;
    readCabecalho(&rC, binFile);
    verifyStatus(rC);

    //Define como será feito o cáculo para ir para o próximo RRN
    int rrnDestino = (RRN*TAMREGISTRO)+13;
    registro *r1 = malloc(sizeof(registro));

    //Busca o registro solicitado no arquivo binário
    if(fseek(binFile, rrnDestino, SEEK_SET) == 0){
        createRegistro(r1);
        readRegistro(r1, binFile);
        int byteLido = fgetc(binFile);
        if (byteLido == EOF){
            printf("Registro inexistente.");
        }else
            printRegistro(*r1);
    }else{
        printf("Registro inexistente.");
    }
 

    freeRegistro(r1);
    closeFile(binFile, dataBin);
}