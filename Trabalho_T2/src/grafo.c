#include "registro.h"
#include "cabecalho.h"
#include "funcionalidades.h"
#include "complemento.h"
#include "grafo.h"

// Direcionado 
// Ponderado

grafo *criarGrafo(int numVertices){
    grafo *novoGrafo = (grafo *) malloc(numVertices*sizeof(grafo));

    if (novoGrafo == NULL) 
        exit(0);
    
    for (int i = 0; i < numVertices; i++) {
        novoGrafo[i].iVertice = -1;
        novoGrafo[i].iAdjacente = NULL;  
        novoGrafo[i].grauEntrada = 0;
        novoGrafo[i].grauGeral = 0;
        novoGrafo[i].grauSaida = 0;
        novoGrafo[i].iGrupo = -1;
        novoGrafo[i].nomeOrigem = NULL;
    }

    return novoGrafo;
}

lista *criarNo(registro r){
    lista *novoNo = (lista *)malloc(sizeof(lista));

    if (novoNo == NULL) 
        exit(0);

    novoNo->nomeDestino = malloc(sizeof(char)*(r.tamTecnologiaDestino));
    strcpy(novoNo->nomeDestino, r.nmTecnologiaDestino);
    novoNo->pesoAresta = r.peso;
    novoNo->prox = NULL;

    return novoNo;
}

void criarListaAdjacencia(grafo *g, int numVertice, FILE *arquivo){
    int flag = 0;
    while(flag != -1){
        registro *r = malloc(sizeof(registro));
        int aux = readRegistro(r, arquivo);

        if(aux == 0){
            flag = -1;
            break;
        }

        if(aux == -1)
            continue;
        
        if(r->grupo == -1)
            continue;
        
        if(r->peso== -1)
            continue;

        adicionarAresta(g, *r, numVertice);
    }

    fseek(arquivo, TAM_CAB, SEEK_SET);
}
void criarVetElementos(grafo *g, int numVertice, FILE *arquivo){
    int flag = 0;
    while(flag != -1){
        int iOrigem = -1;
        int iDestino = -1;

        registro *r = malloc(sizeof(registro));
        int aux = readRegistro(r, arquivo);

        if(aux == 0){
            flag = -1;
            break;
        }

        if(aux == -1)
            continue;
        
        if(r->grupo == -1)
            continue;

        if(r->peso== -1)
            continue;

        for(int i = 0; i< numVertice; i++){
            if(g[i].nomeOrigem != NULL && strcmp(g[i].nomeOrigem, r->nmTecnologiaOrigem) == 0)
                iOrigem = i;

            if(g[i].nomeOrigem != NULL && strcmp(g[i].nomeOrigem, r->nmTecnologiaDestino) == 0 && r->nmTecnologiaDestino != NULL )
                iDestino = i;
        }

        if(iOrigem != -1 && g[iOrigem].iGrupo == -2)
            g[iOrigem].iGrupo = r->grupo;

        if(iOrigem == -1)
            inserirVertice(g, r->nmTecnologiaOrigem, r->grupo, numVertice);
        
        if(iDestino == -1)
            inserirVertice(g, r->nmTecnologiaDestino, -2, numVertice);
    }

    quickSort(g, 0, numVertice-1);
    fseek(arquivo, TAM_CAB, SEEK_SET);
}

void adicionarAresta(grafo *grafo, registro r, int numVertice){
    int iOrigem = -1;
    int iDestino = -1;

    for(int i = 0; i< numVertice; i++){
        if(grafo[i].nomeOrigem != NULL && strcmp(grafo[i].nomeOrigem, r.nmTecnologiaOrigem) == 0)
            iOrigem = i;

        if(grafo[i].nomeOrigem != NULL && strcmp(grafo[i].nomeOrigem, r.nmTecnologiaDestino) == 0)
            iDestino = i;
    }

    lista *novaAresta = criarNo(r);
    int aux = inserirLista(&grafo[iOrigem].iAdjacente, &novaAresta);

    if(aux){
        grafo[iOrigem].grauSaida++;
        grafo[iDestino].grauEntrada++;
    }
}

void criaGrafoTransposto(grafo *grafoI, grafo *grafoT, int numVertice){
    //imprimirGrafo(grafoI, numVertice);
    
    for(int u = 0; u < numVertice; u++){
        lista *tmp = grafoI[u].iAdjacente;
        
        while(tmp != NULL){
            int v = indiceTecnologia(tmp->nomeDestino, grafoI, numVertice);

            lista *aux = malloc(sizeof(lista));
            aux->nomeDestino = malloc(sizeof(char)*MAX_STRING);
            strcpy(aux->nomeDestino, grafoI[u].nomeOrigem);

            aux->pesoAresta = tmp->pesoAresta;

            int aux2 = inserirLista(&(grafoT[v].iAdjacente), &aux);

            if(aux2){
                grafoT[v].grauSaida++;
                grafoT[u].grauEntrada++;
            }

            tmp = tmp->prox;
        }
    }
}


int indiceTecnologia(char *nome, grafo *g, int numVertice){
    int inicio = 0;
    int fim = numVertice -1;

    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;

        int comparacao = strcmp(nome, g[meio].nomeOrigem);

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

int inserirLista(lista **listaAdj, lista **novaAresta){

    if(*listaAdj == NULL || strcmp((*novaAresta)->nomeDestino, (*listaAdj)->nomeDestino) < 0) {
        (*novaAresta)->prox = *listaAdj;
        *listaAdj = *novaAresta;   
    }else{
        lista *tmp = *listaAdj;

        if(strcmp((*novaAresta)->nomeDestino, (*listaAdj)->nomeDestino) == 0)
            return 0;

        while(tmp->prox != NULL && strcmp((*novaAresta)->nomeDestino, (*listaAdj)->nomeDestino) > 0)
            tmp = tmp->prox;
        
        (*novaAresta)->prox = tmp->prox;
        tmp->prox = *novaAresta;
    }
    return 1;
}

void inserirVertice(grafo *grafo, char*nome, int grupo, int numVertice){
    int index = -1;
    for(int i = 0; i<numVertice; i++){
        if(grafo[i].nomeOrigem == NULL){
            index = i;
            break;
        }
    }
    grafo[index].nomeOrigem = malloc(sizeof(char)*strlen(nome));
    strcpy(grafo[index].nomeOrigem, nome);
    grafo[index].iGrupo = grupo;

}


void calculaGrau(grafo *g, int numVertices){
    for(int i = 0; i<numVertices; i++){
        g[i].grauGeral = g[i].grauEntrada + g[i].grauSaida;
    }
}

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

int encontrarTecnologiasOrigem(grafo *grafo, int numVertices, char *tecnologiaDestino) {
    int i;
    for (i = 0; i < numVertices; i++) {
        if (strcmp(grafo[i].nomeOrigem, tecnologiaDestino) == 0) {
            lista *adjacente = grafo[i].iAdjacente;
            while (adjacente != NULL) {
                printf("%s, ", adjacente->nomeDestino);
                adjacente = adjacente->prox;
            }
            printf("\n");
            return 1;
        }
    }

    // Se chegou aqui, a tecnologia destino não foi encontrada no grafo
  return 0;
}

/*//Função que realiza a busca em profundidade
void buscaEmProfundidade(grafo *g, int numVertices, int* ehFortementeConexo, int* numComponentes){
    int* cor = (int*)malloc(numVertices * sizeof(int));
    int* pre = (int*)malloc(numVertices * sizeof(int));
    int* low = (int*)malloc(numVertices * sizeof(int));

    //Atribui a cor branca a todos os vétices
    for(int i=0; i<numVertices; i++){
        cor[i] = BRANCO;
    }
    //Inicia a visita nos vértices
    for(int i=0; i<numVertices; i++){
        if(cor[i] == BRANCO){
            visitaVertice(g, i, numVertices,cor, pre, low, ehFortementeConexo, numComponentes);
        }
    }

    free(pre);
    free(low);
}

//Função que faz a visita nos vértices
void visitaVertice(grafo* g, int i, int numVertices, int* cor, int* pre, int* low, int* ehFortementeConexo, int* numComponentes) {
    int tempo = 0;
    
    cor[i] = CINZA;
    pre[i] = low[i] = ++tempo;

    lista* adjacente = g[i].iAdjacente;
    int v = indiceTecnologia(adjacente->nomeDestino, g, numVertices);
    lista* tmp = g[v].iAdjacente;
    
    //Percorre o grafo analisando e pintando os vértices
    while (tmp != NULL) {
        char* nomeAdjacente = tmp->nomeDestino;
        int adj = -1; // Inicializa como -1, indicando que não encontrou o vértice
        //int v = indiceTecnologia(adjacente->nomeDestino, g, numVertices);

        // Procura o vértice no grafo
        for (int j = 0; j < numVertices; j++) {
            if (strcmp(g[j].nomeOrigem, nomeAdjacente) == 0) {
                adj = j;
                break;
            }
        }

        if (adj != -1) {
            if (cor[adj] == BRANCO) {
                visitaVertice(g, adj, numVertices,cor, pre, low, ehFortementeConexo, numComponentes);
                low[i] = (low[i] < low[adj]) ? low[i] : low[adj];
            } else if (cor[adj] == CINZA) {
                low[i] = (low[i] < pre[adj]) ? low[i] : pre[adj];
            }
        }

        tmp = tmp->prox;
    }

    cor[i] = PRETO;

    if (pre[i] == low[i]) {
        (*numComponentes)++;
    }

    // Se o número de componentes for igual ao número de vértices, o grafo é fortemente conexo
    if (*numComponentes == numVertices) {
        *ehFortementeConexo = 1;
    }
}

//Algoritmo de Tarjan para verificar se o grafo é ou não fortemente conexo
void algoritmoDeTarjan(grafo* g, int numVertices) {
    int numComponentes = 0;
    int* ehFortementeConexo = (int*)malloc(sizeof(int));
    *ehFortementeConexo = 1;

    buscaEmProfundidade(g, numVertices, ehFortementeConexo, &numComponentes);

    if(*ehFortementeConexo){
        printf("O grafo é fortemente conexo e tem %d componentes\n", numComponentes);
    }else{
        printf("O grafo não é fortemente conexo e tem %d componentes\n", numComponentes);
    }
}*/

void push(int x, int numVertices){
    int stack[numVertices];
    int top;
    if (top >= numVertices - 1){
        printf("A pilha está cheia");
    }else{
        top++;
        stack[top] = x;
    }
}

void pop(){
    int top;
    if (top <= - 1){
        printf("A pilha está vazia");
    }else{
        top --;
    }
}


// Implementação da função para realizar a DFS no grafo reverso
void dfsR(grafo *grafoT, int v, int numVertices) {
    int pre[numVertices];
    //int cntt; //post[numVertices];
    //int vv[numVertices];

    //pre[v] = cnt++;
    lista *tmp = grafoT[v].iAdjacente;

    while (tmp != NULL) {
        int w = indiceTecnologia(tmp->nomeDestino, grafoT, numVertices);
        if (pre[w] == -1){
            dfsR(grafoT, w, numVertices);

        tmp = tmp->prox;
        }
    }

    //post[v] = cntt++;
}

// Implementação da função para realizar a DFS na etapa de atribuir rótulos
void dfsRStrongCompsK(grafo *grafoI, int v, int *sc, int k, int numVertices) {
    sc[v] = k;

    lista *tmp = grafoI[v].iAdjacente;
    while (tmp != NULL) {
        int w = indiceTecnologia(tmp->nomeDestino, grafoI, numVertices);
        if (sc[w] == -1)
            dfsRStrongCompsK(grafoI, w, sc, k, numVertices);

        tmp = tmp->prox;
    }
}


// Implementação da função para calcular as componentes fortes
int calcularComponentesFortes(int numVertices) {
    int *sc = malloc(sizeof(int*));
    int pre[numVertices];
    int post[numVertices];
    int vv[numVertices];

    // Fase 1
    grafo *grafoR = criarGrafo(numVertices);
    grafo *grafoT = criarGrafo(numVertices);
    criaGrafoTransposto(grafoR, grafoT, numVertices);

    //cnt = cntt = 0;
    for (int v = 0; v < numVertices; ++v){
        pre[v] = -1;
    }
    printf("\n 1\n");

    for (int v = 0; v < numVertices; ++v){
        if (pre[v] == -1)
            dfsR(grafoT, v, numVertices);
    }
    printf("\n 2\n");

    for (int v = 0; v < numVertices; ++v){
        vv[post[v]] = v;
        printf("\n %d\n", vv[post[v]]);
    }
    printf("\n 3\n");

    // Fase 2
    for (int v = 0; v < numVertices; ++v){
        sc[v] = -1;
    }
    printf("\n 4 \n");

    int k = 0;
    for (int i = numVertices - 1; i >= 0; --i) {
        printf("\n 5 \n");
        int v = vv[i];
        if (sc[v] == -1) {
            printf("entrou if");
            dfsRStrongCompsK(grafoR, v, sc, k, numVertices);
            k++;
        }
    }
    printf("\n %d!! \n", k);
    printf("\n 5 \n");

    //free(grafoR);
    //free(grafoT);

    return k;
}

/*void algoritmoDeDijkstra(int numVertices, char *nomeOrigem, char *nomeDestino){
    int u, v, count = 0;
    int *ant, *tmp;
    int *z;

    ant = malloc(sizeof(int*));
    tmp = malloc(sizeof(int*));

    if(ant == NULL){
        printf("Erro!");
    }

    z = malloc(sizeof(int*));
    if(z == NULL){
        printf("erro!");
    }
    
}*/