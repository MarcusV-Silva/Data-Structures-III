#include "funcionalidades.h"
#include "complemento.h"
#include "cabecalho.h"
#include "registro.h"

void funcionalidade1(){

    // Inicializa e abre os arquivos csv e binário
    char *dataBIN = malloc(sizeof(char)*40);
    char *dataCSV = malloc(sizeof(char)*40);
    scanf("%s %s", dataCSV, dataBIN);

    FILE *csvFile = fopen(dataCSV, "r");
    checkFile(csvFile);

    FILE *binFile = fopen(dataBIN, "wb");
    checkFile(binFile);

    // Cria o cabeçalho do arquivo
    registroCab rC;
    createCabecalho(&rC);
    writeCabecalho(binFile, &rC);
    
    // Declaração da variaveis responsaveis pelo armazenamento em memoria primaria
    char tecUnic[MAX_TECNOLOGIAS][MAX_STRING];
    int numTecnologias = 0;
    char parUnic[MAX_TECNOLOGIAS][2][MAX_STRING];
    int numPares = 0;

    // Pula a primeira linha do arquivo
    char linha[100];
    fgets(linha,sizeof(linha) , csvFile);

    // Loop para ler o arquivo .csv e escrever no arquivo .bin
    while (fgets(linha, sizeof(linha), csvFile)) {
        int posicao = 0;
        registro *r1 = malloc(sizeof(registro));
        createRegistro(r1);

        // Definição dos registro e escrita no arquivo binario
        setRegistro(r1, linha, &posicao);
        writeRegistro(r1, binFile);
        
        // Funções que armazenam dados de tecnologia recém adicionados 
        addTecnologiaUnica(tecUnic, r1->nmTecnologiaOrigem, r1->tamTecnologiaOrigem, &numTecnologias);
        addTecnologiaUnica(tecUnic, r1->nmTecnologiaDestino, r1->tamTecnologiaDestino, &numTecnologias);
        addParUnico(parUnic, *r1, &numPares);

        rC.proxRRN = rC.proxRRN + 1;

        freeRegistro(r1);
    }

    // Atualizando o cabeçalho com novos valores
    setCabecalho(&rC, numPares, numTecnologias);
    writeCabecalho(binFile, &rC);

    // Fecha os arquivos
    fclose(csvFile);
    fclose(binFile);

    binarioNaTela(dataBIN);

    // Libera memoria referentes aos nomes dos arquivos
    free(dataBIN);
    free(dataCSV);
}

void funcionalidade2() {
    // Inicializa o arquivo binário  e verifica se ele existe
    char *dataBin = malloc(sizeof(char)*40);
    scanf("%s", dataBin);

    FILE *binFile = fopen(dataBin, "rb");
    checkFile(binFile);
    

    // Lê o cabeçalho do arquivo e verifica o status
    registroCab rC;
    readCabecalho(&rC, binFile);
    verifyStatus(rC);

    int flag = 0;
    // Percorre o arquivo e imprime-o
    while(flag != -1){
        // Criação do registro
        registro *r = malloc(sizeof(registro));
        createRegistro(r);

        // Função que lê um registro do arquivo e para quando chagar ao fim
        if(readRegistro(r, binFile) == 0){
            if(flag == 0){
                printf("Registro inexistente.\n");
            }
            flag = -1;
            freeRegistro(r);
            break;
        }

        // Função que imprime um registro do arquivo
        printRegistro(*r);
        freeRegistro(r);
        flag = 1;   
    }

    // Fecha o arquivo
    closeFile(binFile, dataBin);
}

void funcionalidade3(){
    // Inicializa o arquivo binário  e verifica se ele existe
    int n;
    char *dataBin = malloc(sizeof(char)*40);
    scanf("%s %d", dataBin, &n);

    FILE *binFile = fopen(dataBin, "rb");
    checkFile(binFile);

    // Lê o cabeçalho do arquivo e verifica o status
    registroCab rC;
    readCabecalho(&rC, binFile);
    verifyStatus(rC);

    // Dados de entrada
    int contador = 0;
    listBuscas dadosBuscas[MAX_TECNOLOGIAS];
    char tmp1[MAX_STRING];
    char tmp2[MAX_STRING];

    // Armazena todas os dados referentes as buscas dos campos de entrada
    while(scanf("%s", tmp1) != EOF){
        scan_quote_string(tmp2);
        strcpy(dadosBuscas[contador].nomeCampo,tmp1);
        strcpy(dadosBuscas[contador].valorCampo,tmp2);
        contador++;
    }

    // Caso o numero de buscas seja maior do que o valor "n" fornecido
    if(contador>n){
        printf("Falha no processamento do arquivo.");
        exit(0);
    }

    // For para fazer as buscas solicitadas
    for(int i = 0; i<n; i++){
        int flag = 0;
        // For que percorre o arquivo para encontrar os registros
        for(int j = 0; j<MAX_TECNOLOGIAS; j++){
            int registroEncontrado = 0;

            // Criação dos registros
            registro *r1 = malloc(sizeof(registro)+1);
            createRegistro(r1);

            // Lê um registro do arquivo binário e encerra o loop no fim do arquivo
            if(readRegistro(r1, binFile) == 0){
                freeRegistro(r1);
                break;
            }

            // Cadeia de if e else para verificar a existência dos campos do registro
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
        if(!(flag))
            printf("Registro inexistente.\n");

        //Retorna ao começo do arquivo
        fseek(binFile, 13, SEEK_SET);
    }

    //Fecha o Arquivo
    closeFile(binFile, dataBin);
}

void funcionalidade4(){
    // Inicializa o arquivo binário  e verifica se ele existe
    char *dataBin = malloc(sizeof(char)*40);
    int RRN;
    scanf("%s %d", dataBin, &RRN);

    FILE *binFile = fopen(dataBin, "rb");
    checkFile(binFile);
    
    // Lê o cabeçalho do arquivo e verifica o status
    registroCab rC;
    readCabecalho(&rC, binFile);
    verifyStatus(rC);

    // Define como será feito o cáculo para ir para o próximo RRN
    int rrnDestino = (RRN*TAMREGISTRO)+13;
    registro *r1 = malloc(sizeof(registro));

    // Busca o registro solicitado no arquivo binário
    if(fseek(binFile, rrnDestino, SEEK_SET) == 0){
        createRegistro(r1);
        if (readRegistro(r1, binFile) == 0){
            printf("Registro inexistente.");
        }else
            printRegistro(*r1);
    }else{
        printf("Registro inexistente.");
    }
 
    // Libera memoria do registro e fecha o arquivo
    freeRegistro(r1);
    closeFile(binFile, dataBin);
}