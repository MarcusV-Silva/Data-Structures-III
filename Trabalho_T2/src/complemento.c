#include "registro.h"
#include "cabecalho.h"
#include "grafo.h"
#include "funcionalidades.h"
#include "complemento.h"

//Função que verifica se o arquivo existe
void checkFile(FILE *arquivo){
    if (arquivo == NULL) {
        printf("Falha no processamento do arquivo.\n");
        exit(0);
    }
}

// Função que libera o ponteiro do arquivo, como também fecha o arquivo
int closeFile(FILE *arquivoPonteiro, char *nomeArquivo){
    free(nomeArquivo);
    fclose(arquivoPonteiro);
    return 0;
}

// Função criada para retirar o ultimo espaço das entradas que no caso é a virgula
void retiraVirgula(char *str){
	size_t length = strlen(str);

    if (length > 0) {
        for (size_t i = 0; i < length - 1; ++i) {
            str[i] = str[i];
        }
        str[length - 1] = '\0'; 
    }
}

// Função que atualiza o numero de tecnologias e seus pares no arquivo de dados
void verificarTecnologias(FILE *arquivo, registro r){
	fseek(arquivo,  0, SEEK_SET);
	registroCab *rC = malloc(sizeof(registroCab));
    createCabecalho(rC);
    readCabecalho(rC,arquivo);

	registro *aux = malloc(sizeof(registro));
	createRegistro(aux);

	//flags de controle
	int flag0 = 0;
	int flag1 = 0;
	int flag2 = 0;
	
	// Loop que percorre o arquivo de dados e verifica se a tecnologia ja existe
	while(readRegistro(aux, arquivo) != 0){
		if(aux->removido == '0'){
			if(strcmp(r.nmTecnologiaOrigem,aux->nmTecnologiaOrigem) == 0 || strcmp(r.nmTecnologiaOrigem,aux->nmTecnologiaDestino) == 0)
				flag0 = 1;
			if(strcmp(r.nmTecnologiaDestino,aux->nmTecnologiaOrigem) == 0 || strcmp(r.nmTecnologiaDestino,aux->nmTecnologiaDestino) == 0)
				flag1 = 1;
			if(strcmp(r.nmTecnologiaOrigem,aux->nmTecnologiaOrigem) == 0 && strcmp(r.nmTecnologiaDestino,aux->nmTecnologiaDestino) == 0)
				flag2 = 1;
		}
	}

	// Caso as flags permanecam em 0 e o campo não seja nulo, o numero de tecnologias aumenta
	if(!flag0 && r.tamTecnologiaOrigem != 0)
		rC->nroTecnologias++;

	if(!flag1 && r.tamTecnologiaDestino != 0)
		rC->nroTecnologias++;
		
	if(!flag2 && r.tamTecnologiaDestino != 0 && r.tamTecnologiaOrigem != 0)
		rC->nroParesTecnologias++;
	
	rC->proxRRN++;

	// Escreve no cabeçalho do arquivo de dados
	writeCabecalho(arquivo, rC);
}

// Função criada para a leitura das entradas da funcionalidade 7
void scanfEntrada(registro *r){

	//String  auxiliar para o escaneamento
	char *aux = malloc(sizeof(char)*MAX_STRING);

	// Rotina de entradas, verificando se o campo em questão é NULO
	scanf("%s", aux);
	retiraVirgula(aux);
	r->nmTecnologiaOrigem = (strcmp(aux, "NULO") == 0) ? strdup("") : strdup(aux);
	r->tamTecnologiaOrigem = strlen(r->nmTecnologiaOrigem);

	scanf("%s", aux);
	retiraVirgula(aux);
	(strcmp(aux,"NULO") == 0) ? (r->grupo = -1) : (r->grupo = atoi(aux));

	scanf("%s", aux);
	retiraVirgula(aux);
	(strcmp(aux,"NULO") == 0) ? (r->popularidade = -1) : (r->popularidade = atoi(aux));

	scanf("%s", aux);
	retiraVirgula(aux);
	r->nmTecnologiaDestino = (strcmp(aux, "NULO") == 0) ? strdup("") : strdup(aux);
	r->tamTecnologiaDestino = strlen(r->nmTecnologiaDestino);

	scanf("%s", aux);
	(strcmp(aux,"NULO") == 0) ? (r->peso = -1) : (r->peso = atoi(aux));

	free(aux);
}

int particionarVertice(grafo *g, int baixo, int topo) {
    char *pivo = malloc(sizeof(char)*strlen(g[topo].nomeOrigem));
    strcpy(pivo, g[topo].nomeOrigem);

    int i = (baixo - 1);

    for (int j = baixo; j <= topo - 1; j++) {
        if (strcmp(g[j].nomeOrigem, pivo) < 0) {
            i++;
            // Trocar g[i] e g[j]
            grafo temp = g[i];
            g[i] = g[j];
            g[j] = temp;
        }
    }
    // Trocar g[i + 1] e g[topo]
    grafo temp = g[i + 1];
    g[i + 1] = g[topo];
    g[topo] = temp;

    return (i + 1);
}

// Função QuickSort para o vetor de vértices durante a criação do grafo
void quickSort(grafo *g, int baixo, int topo) {
    if (baixo < topo) {

        int pivo = particionarVertice(g, baixo, topo);

        quickSort(g, baixo, pivo - 1);
        quickSort(g, pivo + 1, topo);
    }
}

//---------------------(Funções fornecidas para o desenvolvimento do trabalho)---------------------

void readline(char* string){
    char c = 0;

    do{
        c = (char) getchar();

    } while(c == '\n' || c == '\r');

    int i = 0;

    do{
        string[i] = c;
        i++;
        c = getchar();
    } while(c != '\n' && c != '\r');

    string[i]  = '\0';
}

void binarioNaTela(char *nomeArquivoBinario) { /* Você não precisa entender o código dessa função. */

	/* Use essa função para comparação no run.codes. Lembre-se de ter fechado (fclose) o arquivo anteriormente.
	*  Ela vai abrir de novo para leitura e depois fechar (você não vai perder pontos por isso se usar ela). */

	unsigned long i, cs;
	unsigned char *mb;
	size_t fl;
	FILE *fs;
	if(nomeArquivoBinario == NULL || !(fs = fopen(nomeArquivoBinario, "rb"))) {
		fprintf(stderr, "ERRO AO ESCREVER O BINARIO NA TELA (função binarioNaTela): não foi possível abrir o arquivo que me passou para leitura. Ele existe e você tá passando o nome certo? Você lembrou de fechar ele com fclose depois de usar?\n");
		return;
	}
	fseek(fs, 0, SEEK_END);
	fl = ftell(fs);
	fseek(fs, 0, SEEK_SET);
	mb = (unsigned char *) malloc(fl);
	fread(mb, 1, fl, fs);

	cs = 0;
	for(i = 0; i < fl; i++) {
		cs += (unsigned long) mb[i];
	}
	printf("%lf\n", (cs / (double) 100));
	free(mb);
	fclose(fs);
}

int scan_quote_string(char *str) {

	/*
	*	Use essa função para ler um campo string delimitado entre aspas (").
	*	Chame ela na hora que for ler tal campo. Por exemplo:
	*
	*	A entrada está da seguinte forma:
	*		nomeDoCampo "MARIA DA SILVA"
	*
	*	Para ler isso para as strings já alocadas str1 e str2 do seu programa, você faz:
	*		scanf("%s", str1); // Vai salvar nomeDoCampo em str1
	*		scan_quote_string(str2); // Vai salvar MARIA DA SILVA em str2 (sem as aspas)
	*
	*/

	char R;

	while((R = getchar()) != EOF && isspace(R)); // ignorar espaços, \r, \n...

	if(R == 'N' || R == 'n') { // campo NULO
		getchar(); getchar(); getchar(); // ignorar o "ULO" de NULO.
		strcpy(str, ""); // copia string vazia
	} else if(R == '\"') {
		if(scanf("%[^\"]", str) != 1) { // ler até o fechamento das aspas
			strcpy(str, "");
		}
		getchar(); // ignorar aspas fechando
	} else if(R != EOF){ // vc tá tentando ler uma string que não tá entre aspas! Fazer leitura normal %s então, pois deve ser algum inteiro ou algo assim...
		str[0] = R;
		scanf("%s", &str[1]);
	} else { // EOF
		strcpy(str, "");
	}

	return 1;
}