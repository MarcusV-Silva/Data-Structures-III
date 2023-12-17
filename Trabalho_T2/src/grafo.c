#include "registro.h"
#include "cabecalho.h"
#include "funcionalidades.h"
#include "complemento.h"
#include "grafo.h"

// Inicialização dos campos de um grafo
grafo *criarGrafo(int numVertices){
    grafo *novoGrafo = (grafo *) malloc((numVertices+1)*sizeof(grafo));

    if (novoGrafo == NULL) 
        exit(0);
    
    // Definição dos campos vazios
    for (int i = 0; i < numVertices; i++) {
        novoGrafo[i].iAdjacente = NULL;  
        novoGrafo[i].grauEntrada = 0;
        novoGrafo[i].grauGeral = 0;
        novoGrafo[i].grauSaida = 0;
        novoGrafo[i].iGrupo = -1;
        novoGrafo[i].nomeOrigem = NULL;
    }

    return novoGrafo;
}

// Inicialização das listas de ajacencias com base no registro do arquivo binario
lista *criarNo(registro r){
    lista *novoNo = (lista *)malloc(sizeof(lista));

    if (novoNo == NULL) 
        exit(0);

    // Atribuição dos valores dos campos
    novoNo->nomeDestino = malloc(sizeof(char)*(r.tamTecnologiaDestino));
    strcpy(novoNo->nomeDestino, r.nmTecnologiaDestino);
    novoNo->pesoAresta = r.peso;
    novoNo->prox = NULL;

    return novoNo;
}

// Função que definem o vetor de elementos de um grafo com base nos registro de um arquivo .bin
void criarVetElementos(grafo *g, int numVertice, FILE *arquivo){
    int flag = 0;
    while(flag != -1){

        // Inicialização dos indices das tecnologias
        int iOrigem = -1;
        int iDestino = -1;

        // Leitura do arquivo de dados
        registro *r = malloc(sizeof(registro));
        int aux = readRegistro(r, arquivo);

        // Verificação do resultado da leitura

        // Caso em que chegou no fim do arquivo
        if(aux == 0){
            flag = -1;
            freeRegistro(r);
            break;
        }

        // Caso em que o registro esta removido
        if(aux == -1){
            freeRegistro(r);
            continue;
        }
        
        if(r->grupo == -1){
            freeRegistro(r);
            continue;
        }

        // Definição dos indices das tecnologias no vetor de elementos do grafo
        for(int i = 0; i< numVertice; i++){
            if(g[i].nomeOrigem != NULL && strcmp(g[i].nomeOrigem, r->nmTecnologiaOrigem) == 0)
                iOrigem = i;

            if(g[i].nomeOrigem != NULL && strcmp(g[i].nomeOrigem, r->nmTecnologiaDestino) == 0 && r->tamTecnologiaDestino != 0)
                iDestino = i;
        }

        // Caso o indice seja -1 significa que a tecnologia ainda não esta no vetor, com isso ela é inserida
        if(iOrigem == -1)
            inserirVertice(g, r->nmTecnologiaOrigem, r->grupo, numVertice);
        
        // Inserção da tecnologia de destino com o grupo vazio (flag = -2)
        if(iDestino == -1 && r->tamTecnologiaDestino != 0)
            inserirVertice(g, r->nmTecnologiaDestino, -2, numVertice);

        // Atribuição do grupo correto à tecnologia caso esteja vazio
        if(iOrigem != -1 && g[iOrigem].iGrupo == -2)
            g[iOrigem].iGrupo = r->grupo;

        freeRegistro(r);
    }

    // Ordenação do vetor de elementos
    quickSort(g, 0, numVertice-1);

    // Retorna ao fim do arquivo
    fseek(arquivo, TAM_CAB, SEEK_SET);
}

// Função que insere uma tecnologia no fim do vetor de elementos 
void inserirVertice(grafo *grafo, char *tecnologia, int grupo, int numVertice){
    int index = -1;

    // Encontra a ultima posição do vetor
    for(int i = 0; i<numVertice; i++){
        if(grafo[i].nomeOrigem == NULL){
            index = i;
            break;
        }
    }

    // Definição dos campos da ultima posicao
    grafo[index].nomeOrigem = malloc(sizeof(char)*strlen(tecnologia));
    strcpy(grafo[index].nomeOrigem, tecnologia);
    grafo[index].iGrupo = grupo;
}

// Função que definem a lista de adjacencias de um grafo com base nos registro de um arquivo .bin
void criarListaAdjacencia(grafo *g, int numVertice, FILE *arquivo){
    int flag = 0;
    while(flag != -1){
        // Leitura do arquivo de dados
        registro *r = malloc(sizeof(registro));
        int aux = readRegistro(r, arquivo);

        // Verificação do resultado da leitura

        // Caso em que chegou no fim do arquivo
        if(aux == 0){
            flag = -1;
            freeRegistro(r);
            break;
        }

        // Caso em que o registro esta removido
        if(aux == -1){
            freeRegistro(r);
            continue;
        }
        
        // Valores que nao podem entrar no grafo
        if(r->grupo == -1){
            freeRegistro(r);
            continue;
        }
        
        if(r->peso== -1){
            freeRegistro(r);
            continue;
        }

        // Adiciona a aresta na lista de adjacencia
        adicionarAresta(g, *r, numVertice);
        freeRegistro(r);
    }

    // Ordena cada lista de adjacencia
    for(int i = 0; i<numVertice; i++){
        quickSortLista(g[i].iAdjacente, ultimoNo(g[i].iAdjacente));
    }

    // Volta para o inicio do arquivo binario
    fseek(arquivo, TAM_CAB, SEEK_SET);
}

// Função que adiciona a aresta na lista de adjacencia
void adicionarAresta(grafo *grafo, registro r, int numVertice){
    int iOrigem = -1;
    int iDestino = -1;

    // Encontra a posicao no grafo
    for(int i = 0; i< numVertice; i++){
        if(grafo[i].nomeOrigem != NULL && strcmp(grafo[i].nomeOrigem, r.nmTecnologiaOrigem) == 0)
            iOrigem = i;

        if(grafo[i].nomeOrigem != NULL && strcmp(grafo[i].nomeOrigem, r.nmTecnologiaDestino) == 0 && r.tamTecnologiaDestino != 0)
            iDestino = i;
    }

    // Cria o campo da lista
    lista *novaAresta = criarNo(r);
    int aux;

    // Realiza a inserção da nova lista na lista que ja existia
    if(iDestino != -1)
        aux = inserirLista(&grafo[iOrigem].iAdjacente, novaAresta);

    // Define os novos graus
    if(aux){
        grafo[iOrigem].grauSaida++;
        grafo[iDestino].grauEntrada++;
    }
}

// Inserção de uma nova lista na lista atual do vetor de elementos
int inserirLista(lista **listaAdj, lista *novaAresta){

    if(*listaAdj == NULL || strcmp((novaAresta)->nomeDestino, (*listaAdj)->nomeDestino) < 0) {
        (novaAresta)->prox = *listaAdj;
        *listaAdj = novaAresta;   
    }else{
        lista *tmp = *listaAdj;

        if(strcmp((novaAresta)->nomeDestino, (*listaAdj)->nomeDestino) == 0)
            return 0;

        while(tmp->prox != NULL && strcmp(novaAresta->nomeDestino, (*listaAdj)->nomeDestino) > 0)
            tmp = tmp->prox;
        
        (novaAresta)->prox = tmp->prox;
        tmp->prox = novaAresta;
    }
    return 1;
}

// Função para a criação de um grafo transposto
void criaGrafoTransposto(grafo *grafoI, grafo *grafoT, int numVertice){
    
    // Percorre todos os campos do vetor de elementos
    for(int u = 0; u < numVertice; u++){
        // Lista temporaria
        lista *tmp = grafoI[u].iAdjacente;
        
        // Percorre a lista temporaria
        while(tmp != NULL){
            //Encontra o indice da tecnologia no grafo geral
            int v = indiceTecnologia(tmp->nomeDestino, grafoI, numVertice);

            // Cria um novo campo da lista com base no elemento do vetor
            lista *aux = malloc(sizeof(lista));
            aux->nomeDestino = malloc(sizeof(char)*MAX_STRING);
            strcpy(aux->nomeDestino, grafoI[u].nomeOrigem);
            aux->pesoAresta = tmp->pesoAresta;

            // Insere esse novo campo no grafo transposto
            int aux2 = inserirLista(&(grafoT[v].iAdjacente), aux);

            // Atualiza o grau do elemento do novo grafo
            if(aux2){
                grafoT[v].grauSaida++;
                grafoT[u].grauEntrada++;
            }

            tmp = tmp->prox;
        }
    }
}

// Busca binaria para encontrar a posição de um tecnologia no vetor de elementos do grafo
int indiceTecnologia(char *tecnologia, grafo *g, int numVertice){
    int inicio = 0;
    int fim = numVertice -1;

    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;

        int comparacao = strcmp(tecnologia, g[meio].nomeOrigem);

        if (comparacao == 0) {
            return meio; 
        } else if (comparacao < 0) {
            fim = meio - 1; //  metade inferior
        } else {
            inicio = meio + 1; // metade superior
        }
    }
    return inicio; // Retorna a posição onde esta
}

// Define o grau geral de todos os elementos
void calculaGrau(grafo *g, int numVertices){
    for(int i = 0; i<numVertices; i++){
        g[i].grauGeral = g[i].grauEntrada + g[i].grauSaida;
    }
}


// Imprime todos os campos do grafo
void imprimirGrafo(grafo *g, int numVertices){
    lista *tmp;
    for(int i = 0; i<numVertices; i++){
        tmp = g[i].iAdjacente;
        while(tmp != NULL){
            printf("%s %d %d %d %d %s %d\n", g[i].nomeOrigem, g[i].iGrupo, g[i].grauEntrada, g[i].grauSaida, g[i].grauGeral, tmp->nomeDestino, tmp->pesoAresta);
            tmp = tmp->prox;
        }
    }
}

// Encontra as tecnologias que originaram o clique para uma determinada tecnologia destino
int encontrarTecnologiasOrigem(grafo *grafo, int numVertices, char *tecnologia) {
    // Encontra o indice de tecnologia no vetor de elementos
    int aux = indiceTecnologia(tecnologia, grafo, numVertices);

    // Cria um grafo temporario
    lista *adjacente = grafo[aux].iAdjacente;

    // Numero de saidas do grafo
    int lim = grafo[aux].grauSaida;
    if(lim == 0)
        return 0;

    // Impressão das tecnologias
    while (adjacente != NULL && lim>1) {
        lim--;
        printf("%s, ", adjacente->nomeDestino);
        adjacente = adjacente->prox;
    }
    printf("%s\n", adjacente->nomeDestino);

    return 1;
}

// Função para preencher a pilha que será usada no algoritmo de Kosaraju
void preencherPilhaFinalizacao(grafo *g, int v, int visitado[], pilhaTAD* pilha, int numVertice) {
    visitado[v] = 1;

    lista* temp = g[v].iAdjacente;
    // While para preencher a pilha recursicamente
    while (temp != NULL) {
        int adjVertex = indiceTecnologia(temp->nomeDestino, g, numVertice);
        if (!visitado[adjVertex]) {
            preencherPilhaFinalizacao(g, adjVertex, visitado, pilha, numVertice);
        }
        temp = temp->prox;
    }
    // Insere um item na pilha
    empilhar(pilha, v);
}

// Função para realizar a busca em profundidade no grafo
void buscaProfundidade(grafo *g, int v, int visitado[], int numVertice) {
    visitado[v] = 1;

    lista* temp = g[v].iAdjacente;
    // While para que a função possa ser realizada de forma recursiva
    while (temp != NULL) {
        int adjVertex = indiceTecnologia(temp->nomeDestino, g, numVertice);
        // Se  o vértice não foi visitado ainda,realiza a busca em profundidade
        if (!visitado[adjVertex]) {
            buscaProfundidade(g, adjVertex, visitado, numVertice);
        }
        temp = temp->prox;
    }
}

// Função que verifica se o grafo é fortemente conexo
int verificarFortementeConexo(grafo *g, grafo *grafoTransposto, int numVertice) {
    int visitado[numVertice];
    // Criando o TAD de pilha
    pilhaTAD *pilha = criarPilha(numVertice);

    // Preenche o visitado como 0 para mostrar que o vértice não foi visitado
    for (int i = 0; i < numVertice; i++) {
        visitado[i] = 0;
    }

    // Preenche a pilha usando o grafo normal para usar na busca
    for (int i = 0; i < numVertice; i++) {
        if (!visitado[i]) {
            preencherPilhaFinalizacao(g, i, visitado, pilha, numVertice);
        }
    }

    // Zera os vértices para que possam ser reutilizados
    for (int i = 0; i < numVertice; i++){
        visitado[i] = 0;
    }

    int numComponentes = 0;

    // Realiza a busca em profundidade usando o grafo transposto e conta o número de componentes
    while (!pilhaVazia(pilha)) {
        int v = desempilhar(pilha);
        // Caso o vértice não tenha sido visitado, a busca é feita
        if (!visitado[v]) {
            numComponentes++;
            buscaProfundidade(grafoTransposto, v, visitado, numVertice);
        }
    }

    // Libera espaço e retorna o número de componentes
    liberarPilha(pilha);
    return numComponentes;
}

// Função que utiliza o algoritmo de Dijkstra para encontrar o menor caminho
int Dijkstra(grafo *g, char *nmOrigem, char *nmDestino, int numVertice){
    int menorCaminho[numVertice];
    int visitado[numVertice];

    // For para indicar que os vértices ainda não foram visitados
    // e que o menor caminho incialmente é máximo
    for(int i = 0; i< numVertice; i++){
        visitado[i] = 0;
        menorCaminho[i]= INT_MAX;
    }

    // Encontrando o índice das entradas
    int iOrigem = indiceTecnologia(nmOrigem, g, numVertice);
    int iDestino = indiceTecnologia(nmDestino, g, numVertice);

    menorCaminho[iOrigem] = 0;

    // For loop para encontrar o menor caminho executando o Dijkstra
    for(int i = 0; i< numVertice; i++){
        
        // Verifica se a origem não é inexistente
        if(iOrigem == -1)
            return -1;

        int w = indiceTecnologia(g[iOrigem].nomeOrigem, g, numVertice);
        lista *tmp = g[iOrigem].iAdjacente;

        // While para percorrer o grafo calculando o qual é o caminho de menor valor de forma gulosa
        while(tmp != NULL && !visitado[w]){
            int v = indiceTecnologia(tmp->nomeDestino, g, numVertice);
            menorCaminho[v] = menorValor(menorCaminho[v], menorCaminho[w] + tmp->pesoAresta);
            tmp = tmp->prox;
        }

        // Variável auxiliar que recebe menor valor do caminho
        int aux = menorValorCaminho(visitado, menorCaminho, numVertice);
        visitado[iOrigem] = 1;

        if(aux != INT_MAX)
            iOrigem = aux;
    }

    // Retorna o valor do menor caminho
    return menorCaminho[iDestino];
}

// Função que calcula qual é o caminho que tem menor valor
int menorValorCaminho(int visitado[], int caminho[], int numVertice){
    int aux = INT_MAX;
    int minIndex = -1;
    for(int i = 0; i< numVertice; i++){
        if(caminho[i]<aux && visitado[i] != 1){
            minIndex = i;
            aux = caminho[i];
        }
    }
    return minIndex;
}

// Função que dado dois valores, ela retorna o menor entre eles
int menorValor(int a, int b){
    return (a>b) ? b : a ;
}


void liberaGrafo(grafo *g, int numVertice){
    for(int i = 0; i < numVertice; i++){
        while(g[i].iAdjacente != NULL){
            free(g[i].iAdjacente->nomeDestino);
            free(g[i].iAdjacente);
            g[i].iAdjacente = g[i].iAdjacente->prox;
        }
        free(g[i].nomeOrigem);
    }
    free(g);
}

