#include "registro.h"

void funcionalidade1(){

    //Inicializa e abre os arquivos csv e binário
    //char *nome = malloc(sizeof(char)*20);
    char *dataBIN = malloc(sizeof(char)*40);
    char *dataCSV = malloc(sizeof(char)*40);
    scanf("%s %s", dataCSV, dataBIN);

    registroCab *rC = (registroCab *) malloc(sizeof(registroCab));

    FILE *csvFile = fopen(dataCSV, "r");
    checkFile(csvFile);//Função que verifica se o arquivo existe

    FILE *binFile = fopen(dataBIN, "wb");
    checkFile(binFile);

    //Funções as quais criam e armazenam o cabeçalho do arquivo
    *rC = createCabecalho();
    writeCabecalho(binFile, rC);
    
    char tecnologiasUnicas[700][40];
    int numTecnologiasUnicas = 0;
    //char paresUnicos[700][2][40];
    //int numParesUnicos = 0;

    char linha[100];
    fgets(linha,sizeof(linha) , csvFile);//Pula a primeira linha do arquivo

    while (fgets(linha, sizeof(linha), csvFile)) {
        int posicao = 0;
        registro *r1 = malloc(sizeof(registro));

        //Os campos são armazenados por meio da função armCampo
        r1->nmTecnologiaOrigem = armCampo(linha, &posicao);
        r1->grupo = atoi(armCampo(linha, &posicao));
        r1->popularidade = atoi(armCampo(linha, &posicao));
        r1->nmTecnologiaDestino = armCampo(linha, &posicao);
        r1->peso = atoi(armCampo(linha, &posicao));
        r1->removido = NAOREMOVIDO;
        r1->tamTecnologiaOrigem = strlen(r1->nmTecnologiaOrigem);
        r1->tamTecnologiaDestino = strlen(r1->nmTecnologiaDestino);

        //Função que armazena os dados no arquivo binário
        writeRegistro(r1, binFile, posicao);
        
        //Função que armazena uma tecnologia recém adicionada 
        adicionarTecnologiaUnica(tecnologiasUnicas, r1->nmTecnologiaOrigem, &numTecnologiasUnicas);
        //adicionarParUnico(paresUnicos, r1->nmTecnologiaOrigem, r1->nmTecnologiaDestino, &numParesUnicos);

        rC->proxRRN = rC->proxRRN + 1;
        rC->nroParesTecnologias = rC->nroParesTecnologias + 1;

        free(r1->nmTecnologiaOrigem);
        free(r1->nmTecnologiaDestino);
        free(r1);
    }


    //setCabecalho(rC, numParesUnicos, numTecnologiasUnicas);
    //Atualiza o status, o número de tecnologias e o cabeçalho do arquivo
    rC->nroTecnologias = numTecnologiasUnicas;
    rC->status = '1';
    writeCabecalho(binFile, rC);
    
    free(rC);

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
    FILE *dataBinFile = fopen(dataBin, "rb");
    checkFile(dataBinFile);
    
    //Aloca memória e lê o cabeçalho do arquivo
    registroCab *rC = malloc(sizeof(registroCab));
    readCabecalho(rC, dataBinFile);

    //Percorre o arquivo e imprime-o
    for (int i = 0; i < 490; i++){
        registro *r = malloc(sizeof(registro));
        readRegistro(r, dataBinFile);//Função que lê um registro do arquivo
        printRegistro(*r);//Função que impŕime um registro do arquivo

        free(r);
    }
    free(dataBin);
    fclose(dataBinFile);
}

void funcionalidade3(){
    //Inicializa o arquivo binário  e verifica se ele existe
    char *dataBin = malloc(sizeof(char)*40);
    int n;
    scanf("%s %d", dataBin, &n);
    FILE *binFile = fopen(dataBin, "rb");
    checkFile(binFile);

    //Lê o cabeçalho do arquivo
    registroCab rC;
    readCabecalho(&rC, binFile);

    //For para fazer as buscas solicitadas
    for(int numBuscas = 0; numBuscas<n; numBuscas++){
        char tmp1[40];
        char tmp2[40];

        scanf("%s", tmp1);
        scan_quote_string(tmp2);
        
        
        int flag = 0;
        //For que percorre o arquivo para encontrar os registros
        for(int j = 0; j < 490; j++) {
            int registroEncontrado = 0;
            registro *r1 = malloc(sizeof(registro));
            
            readRegistro(r1, binFile);//Lê um registro do arquivo binário

            //Cadeia de if e else para verificar a existência dos campos do registro
            if (strcmp(tmp1, "nomeTecnologiaOrigem") == 0 && strcmp(r1->nmTecnologiaOrigem, tmp2) == 0) {
                registroEncontrado = 1;
            } else if (strcmp(tmp1, "nomeTecnologiaDestino") == 0 && strcmp(r1->nmTecnologiaDestino, tmp2) == 0) {
                registroEncontrado = 1;
            } else if (strcmp(tmp1, "grupo") == 0 && r1->grupo == atoi(tmp2)){
                registroEncontrado = 1;
            } else if (strcmp(tmp1, "popularidade") == 0 && r1->popularidade == atoi(tmp2)){
                registroEncontrado = 1;
            } else if (strcmp(tmp1, "peso") == 0 && r1->peso == atoi(tmp2)){
                registroEncontrado = 1;
            }
            if(registroEncontrado){
                printRegistro(*r1);
                flag =1;
            }
            free(r1);
        }
        if(!flag)
            printf("Registro inexistente.\n");

        fseek(binFile, 13, SEEK_SET);

    }
    
    free(dataBin);
    fclose(binFile);
}

void funcionalidade4(){
    //Inicializa o arquivo binário  e verifica se ele existe
    char *dataBin = malloc(sizeof(char)*40);
    int RRN;
    scanf("%s %d", dataBin, &RRN);

    FILE *binFile = fopen(dataBin, "rb");
    checkFile(binFile);
    
    //Define como será feito o cáculo para ir para o próximo RRN
    int rrnDestino = (RRN*TAMREGISTRO) + 13;
    registro *r1 = malloc(sizeof(registro));

    //Busca o registro solicitado no arquivo binário
    if(fseek(binFile, rrnDestino, SEEK_SET) == 0){
        readRegistro(r1, binFile);
        int byteLido = fgetc(binFile);
        if (byteLido == EOF){
            printf("Registro inexistente.");
        }else
            printRegistro(*r1);
    }else{
        printf("Registro inexistente.");
    }

    free(r1);
    fclose(binFile);
}