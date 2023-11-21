#include "indice.h"
#include "registro.h"
#include "cabecalho.h"
#include "arvore.h"
#include "funcionalidades.h"
#include "complemento.h"

void funcionalidade5(){
    
    char *dataBIN = malloc(sizeof(char) * 40);
    char *dataINDEX = malloc(sizeof(char) * 40);
    scanf("%s %s", dataBIN, dataINDEX);
    
    FILE *dataFile = fopen(dataBIN, "rb");
    checkFile(dataFile);

    FILE *indexFile = fopen(dataINDEX, "wb+");
    checkFile(indexFile);

    cabIndice *indexCab = createCabecalhoIndice();
    writeCabecalhoIndice(indexFile, indexCab);
    

    int rrnDados = 0;
    registroCab rC;
    readCabecalho(&rC, dataFile);
    verifyStatus(rC);

    //Criacao e definição do Primeiro no
    No *no = criarNo();

    registro *r0 = malloc(sizeof(registro));
    createRegistro(r0);
    readRegistro(r0, dataFile); //Arrumar dps
    no->RRNdoNo = 0;
    no->vetChaves[0].chave = createChave(r0);
    no->vetChaves[0].referencia = rrnDados;
    no->nroChavesNo = 1;

    rrnDados++;
    writePagina(indexFile, no, 0);

    indexCab->noRaiz = 0;
    indexCab->RRNproxNo = 0;
    writeCabecalhoIndice(indexFile, indexCab);
    Chave *promoChave = malloc(sizeof(Chave));
    int *promoRFilho = malloc(sizeof(int));

    //int totalNos = 1;  
    int flag = 0;
    while(flag != -1){    
    
        registro *r = malloc(sizeof(registro));

        int aux = readRegistro(r, dataFile);
        
        if(aux == 0){
            flag = -1;
            break;
        }

        if(aux == -1){
            rrnDados++;
            continue;
        }

        if(r->tamTecnologiaDestino == 0  || r->tamTecnologiaOrigem == 0){
            rrnDados++;
            continue;
        }

        Chave chaveI;
        chaveI.chave = createChave(r);
        chaveI.referencia = rrnDados;
        rrnDados++;

        int rrnRaiz = indexCab->noRaiz;
        int promo = inserirArvore(indexFile, &rrnRaiz, &chaveI, promoRFilho, promoChave);
       
        if (promo == PROMOTION) {
            readCabIndice(indexFile, indexCab);
            No *novoNo = criarNo();

            No *auxNo = criarNo();
            fseek(indexFile, TAM_PAG_INDEX*(indexCab->RRNproxNo+1), SEEK_SET);
            readPagina(indexFile, auxNo);

            novoNo->nroChavesNo = 1;
            novoNo->alturaNo = (rrnRaiz == -1) ? 1 : auxNo->alturaNo + 1;
            novoNo->vetChaves[0] = *promoChave;
            novoNo->subArvores[0] = rrnRaiz;
            novoNo->subArvores[1] = *promoRFilho;
            novoNo->RRNdoNo = ++indexCab->RRNproxNo;
            
            writePagina(indexFile, novoNo, novoNo->RRNdoNo);
            indexCab->noRaiz = novoNo->RRNdoNo;
            writeCabecalhoIndice(indexFile, indexCab);
        }

        flag++;
    }
    
    readCabIndice(indexFile, indexCab);
    indexCab->status = '1';
    indexCab->RRNproxNo++;
    writeCabecalhoIndice(indexFile, indexCab);

    fclose(indexFile);
    fclose(dataFile); 
    
    binarioNaTela(dataINDEX);
}

void funcionalidade6(){

}

void funcionalidade7(){
    char *dataBIN = malloc(sizeof(char) * 40);
    char *dataINDEX = malloc(sizeof(char) * 40);
    int n = 3;
    //scanf("%s %s %d", dataBIN, dataINDEX, &n);
    strcpy(dataBIN, "binario8.bin");
    strcpy(dataINDEX, "indice8.bin");

    FILE *dataFile = fopen(dataBIN, "ab");
    checkFile(dataFile);

    FILE *indexFile = fopen(dataINDEX, "rb+");
    checkFile(indexFile);

    cabIndice *indexCab = createCabecalhoIndice();
    readCabIndice(indexFile, indexCab);

    fseek(dataFile, 0, SEEK_END);
    int tamanho = ftell(dataFile);// num bytes
    tamanho = (tamanho - 12)/TAMREGISTRO;// rrn final

    for(int i = 0; i<n; i++){
        Chave *promoChave = malloc(sizeof(Chave));
        int *promoRFilho = malloc(sizeof(int));
        registro *registroInsercao = malloc(sizeof(registro));
        createRegistro(registroInsercao);
        scanfEntrada(registroInsercao);
        //printRegistro(*registroInsercao); //Debug
        
        writeRegistro(registroInsercao, dataFile);

        Chave chaveI;
        chaveI.chave = createChave(registroInsercao);
        chaveI.referencia = tamanho++;

        int rrnRaiz = indexCab->noRaiz;
        int promo = inserirArvore(indexFile, &rrnRaiz, &chaveI, promoRFilho, promoChave);
       
        if (promo == PROMOTION) {
            readCabIndice(indexFile, indexCab);
            No *novoNo = criarNo();

            No *auxNo = criarNo();
            fseek(indexFile, TAM_PAG_INDEX*(indexCab->RRNproxNo+1), SEEK_SET);
            readPagina(indexFile, auxNo);

            novoNo->nroChavesNo = 1;
            novoNo->alturaNo = (rrnRaiz == -1) ? 1 : auxNo->alturaNo + 1;
            novoNo->vetChaves[0] = *promoChave;
            novoNo->subArvores[0] = rrnRaiz;
            novoNo->subArvores[1] = *promoRFilho;
            novoNo->RRNdoNo = ++indexCab->RRNproxNo;
            
            writePagina(indexFile, novoNo, novoNo->RRNdoNo);
            indexCab->noRaiz = novoNo->RRNdoNo;
            writeCabecalhoIndice(indexFile, indexCab);
        }
    }
    readCabIndice(indexFile, indexCab);
    indexCab->RRNproxNo++;
    writeCabecalhoIndice(indexFile, indexCab);


    //SQL-SERVER, 2, 3, .NET, 33
    fclose(indexFile);
    fclose(dataFile);

    binarioNaTela(dataBIN);
    binarioNaTela(dataINDEX);
}



// ---------------------- TRABALHO 0 ---------------------------------
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
    while(scanf("%s ", tmp1) != EOF){
        strcpy(dadosBuscas[contador].nomeCampo,tmp1);
        if(strcmp(tmp1, "nomeTecnologiaOrigem") == 0 || strcmp(tmp1, "nomeTecnologiaDestino") == 0) {
            scan_quote_string(tmp2);
        }else{
            scanf("%s", tmp2);
        }
        strcpy(dadosBuscas[contador].valorCampo,tmp2);
        contador++;
    }

    // Caso o numero de buscas seja maior do que o valor "n" fornecido
    if(contador>n){
        printf("Falha no processamento do arquivo.");
        exit(0);
    }
    int flag;
    // For para fazer as buscas solicitadas
    for(int i = 0; i<n; i++){
        flag = 0;
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