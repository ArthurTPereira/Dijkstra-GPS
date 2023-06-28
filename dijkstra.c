#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "listaAdjacencia.h"
#include "atualizacao.h"
#include "dijkstra.h"
#include "PQ.h"

// Funcao para criar um Item
// Entrada:     id - Identificador do vertice
//              value - Peso do vertice (Tempo)
// Saida:       Item - Item criado
Item make_item(int id, double value) {
    Item t;
    id(t) = id;
    value(t) = value;
    return t;
}

// Algoritmo de Dijkstra
// Entrada:     Grafo - Grafo com as informacoes das arestas
//              vOrigem - Vertice de origem
//              vDestino - Vertice de destino
//              atualizacoes - Vetor com as atualizacoes
//              pq - Fila de prioridade
//              map - Vetor de mapeamento
//              tempoDecorrido - Tempo decorrido
//              distanciaPercorrida - Distancia percorrida
// Saida:       edgeTo - Vetor com os vertices antecessores
int* dijkstra(Grafo** grafo, int vOrigem, int vDestino, Atualizacoes** atualizacoes, Item* pq, int* map, double* tempoDecorrido, double* distanciaPercorrida) {
    
    // Inicializa os vetores de tempo, distancia e adjacentes
    int* edgeTo = (int*) calloc(getVertices(*(grafo)), sizeof(int));
    double* timeTo = (double*) malloc(getVertices(*(grafo)) * sizeof(double));
    double* distTo = (double*) malloc(getVertices(*(grafo)) * sizeof(double));

    // Insere o vertice de origem na priority queue
    PQ_insert(pq,map,make_item(vOrigem, 0));
    
    // Insere os demais vertices na priority queue
    for (int i = 1; i < getVertices(*(grafo)); i++) {
        timeTo[i] = __FLT_MAX__;
        distTo[i] = __FLT_MAX__;
    }

    // Inicializa o vertice de origem do vetor de tempo e distancia com 0
    timeTo[vOrigem] = 0;
    distTo[vOrigem] = 0;

    double tempoTotal = 0;
    int instanteAtualizacao = 0;
    int atualizacaoAtual = 0;

    // Enquanto a priority queue nao estiver vazia
    while (!PQ_empty(pq)) {
        // Remove o elemento com menor prioridade
        Item p = PQ_delmin(pq,map);
        int vertice = id(p);
        double value = value(p);

        // Coleta o tempo total decorrido
        tempoTotal = timeTo[vertice];

        // Verifica se ha atualizacoes no vetor e varre as atualizacoes que ocorrem apos o tempo decorrido atual
            while (getUltimaAtualizacao(*atualizacoes) < getNAtual(*atualizacoes) && (tempoTotal) >= getInstanteAtualizacao(*atualizacoes,getUltimaAtualizacao(*atualizacoes))) {
            // Obtem a atualizacao atual e o instante que ela ocorre
            atualizacaoAtual = getUltimaAtualizacao(*atualizacoes);
            instanteAtualizacao = getInstanteAtualizacao(*atualizacoes,atualizacaoAtual);

            // Atualiza o grafo com as novas atualizacoes
            atualizaGrafo(grafo,getOrigemAtualizacao(*atualizacoes,atualizacaoAtual),getDestinoAtualizacao(*atualizacoes,atualizacaoAtual),getVelocidadeAtualizacao(*atualizacoes,atualizacaoAtual));
                
            // Atualiza para a proxima atualizacao
            setUltimaAtualizacao(atualizacoes,atualizacaoAtual+1);
        }

        // Para cada vertice adjacente ao vertice removido
        for (Node* adj = getListaAdjacencia((*grafo),vertice); adj != NULL; adj = getProx(adj)) {
            // Obtem o vertice origem, destino, tempo e distancia
            int v = getOrigem(adj);
            int w = getDestino(adj);
            double tempo = getTempo(adj);
            double distancia = getDistancia(adj);
            
            // Atualiza a fila de prioridades caso o tempo para o vertice destino seja menor que o tempo atual
            if (timeTo[w] > timeTo[v] + tempo) {
                timeTo[w] = timeTo[v] + tempo;
                distTo[w] = distTo[v] + distancia;
                edgeTo[w] = v;
                
                // Verifica se o vertice destino ja esta na priority queue
                if (PQ_contains(pq,w)) {

                    // Atualiza a prioridade do item
                    PQ_decrease_key(pq,map,w,timeTo[w]);
                } else {

                    // Insere na priority queue
                    PQ_insert(pq,map,make_item(w,timeTo[w]));
                }
            }
        }
    }

    // Atribui o tempo decorrido final e a distancia as variaveis de saida
    *tempoDecorrido = timeTo[vDestino];
    *distanciaPercorrida = distTo[vDestino];

    // Libera os vetores auxiliares de tempo e distancia
    free(timeTo);
    free(distTo);

    // Retorna o vetor com o menor caminho
    return edgeTo;
}


int* dijkstra2(Grafo** grafo, int vOrigem, int vDestino) {
    
    // Inicializa os vetores de tempo, distancia e adjacentes
    int* edgeTo = (int*) calloc(getVertices(*(grafo)), sizeof(int));
    double* timeTo = (double*) malloc(getVertices(*(grafo)) * sizeof(double));
    Item* pq;
    int* map;
    PQ_init(&pq,&map,getVertices(*(grafo)));

    // Insere o vertice de origem na priority queue
    PQ_insert(pq,map,make_item(vOrigem, 0));
    
    // Insere os demais vertices na priority queue
    for (int i = 1; i < getVertices(*(grafo)); i++) {
        timeTo[i] = __DBL_MAX__;
    }

    edgeTo[vOrigem] = 0;
    timeTo[vOrigem] = 0;

    // Enquanto a priority queue nao estiver vazia
    while (!PQ_empty(pq)) {
        // Remove o elemento com menor prioridade
        Item p = PQ_delmin(pq,map);
        int vertice = id(p);
        double value = value(p);

        // Para cada vertice adjacente ao vertice removido
        for (Node* adj = getListaAdjacencia((*grafo),vertice); adj != NULL; adj = getProx(adj)) {
            // Obtem o vertice origem, destino, tempo e distancia
            int v = getOrigem(adj);
            int w = getDestino(adj);
            double tempo = getTempo(adj);
            double distancia = getDistancia(adj);
            
            // Atualiza a fila de prioridades caso o tempo para o vertice destino seja menor que o tempo atual
            if (timeTo[w] > timeTo[v] + tempo) {
                timeTo[w] = timeTo[v] + tempo;
                edgeTo[w] = v;
                
                // Verifica se o vertice destino ja esta na priority queue
                if (PQ_contains(pq,w)) {

                    // Atualiza a prioridade do item
                    PQ_decrease_key(pq,map,w,timeTo[w]);
                } else {

                    // Insere na priority queue
                    PQ_insert(pq,map,make_item(w,timeTo[w]));
                }
            }
        }
    }
    free(timeTo);
    PQ_finish(pq,map);
    // Retorna o vetor com o menor caminho
    return edgeTo;
}

int* DijkstraLoop(Grafo** grafo,int vOrigem, int vDestino, Atualizacoes** atualizacoes, double* tempoDecorrido, double* distanciaPercorrida) {

    int origemTemp = vOrigem;

    double tempoTotal = 0;
    double distanciaTotal = 0;
    int atualizacaoAtual = 0;
    int instanteAtualizacao = 0;
    int proxVertice;
    int* edgeTo = (int*) calloc(getVertices(*(grafo)), sizeof(int));
    int i = 0;
    edgeTo[i] = vOrigem;

    int* caminho = NULL;
    while(origemTemp != vDestino) {
        while (getUltimaAtualizacao(*atualizacoes) < getNAtual(*atualizacoes) && (tempoTotal) >= getInstanteAtualizacao(*atualizacoes,getUltimaAtualizacao(*atualizacoes))) {
        // Obtem a atualizacao atual e o instante que ela ocorre
        atualizacaoAtual = getUltimaAtualizacao(*atualizacoes);
        instanteAtualizacao = getInstanteAtualizacao(*atualizacoes,atualizacaoAtual);
        // Atualiza o grafo com as novas atualizacoes
        atualizaGrafo(grafo,getOrigemAtualizacao(*atualizacoes,atualizacaoAtual),getDestinoAtualizacao(*atualizacoes,atualizacaoAtual),getVelocidadeAtualizacao(*atualizacoes,atualizacaoAtual));
        // Atualiza para a proxima atualizacao
        setUltimaAtualizacao(atualizacoes,atualizacaoAtual+1);
        }
        if (caminho != NULL) {
            free(caminho);
        }
        caminho = dijkstra2(grafo,origemTemp,vDestino);
        proxVertice = buscaProxVertice(caminho, origemTemp, vDestino, getVertices(*grafo)); // varre o caminho e retorna o proximo vertice

        tempoTotal += getTempoEntreVertices(*grafo,origemTemp,proxVertice); // buscar tempo de origemTemp a proxVertice
        //printf("%d -> %d\n",origemTemp,proxVertice);
        //printf("Tempo total: %lf\n",tempoTotal);
        distanciaTotal += getDistanciaEntreVertices(*grafo,origemTemp,proxVertice); // buscar distancia de origemTemp a proxVertice
        //printf("Distancia total: %lf\n",distanciaTotal);
        edgeTo[i+1] = proxVertice;
        origemTemp = proxVertice;
        i++;
    }

    *tempoDecorrido = tempoTotal;
    *distanciaPercorrida = distanciaTotal;
    free(caminho);
    return edgeTo;
    
}

int* retornaCaminhoTerminal(int* vetor, int vOrigem, int vDestino) {
    int tamanho = 0;

    // Verifica o tamanho do caminho
    int vAtual = vDestino;
    while (vAtual != vOrigem) {
        tamanho++;
        vAtual = vetor[vAtual];
    }

    // Cria um vetor para armazenar o caminho
    int* caminho = (int*) malloc((tamanho + 1) * sizeof(int));
    vAtual = vDestino;
    int indice = tamanho;

    // Preenche o vetor com o caminho
    while (vAtual != vOrigem) {
        caminho[indice] = vAtual;
        indice--;
        vAtual = vetor[vAtual];
    }
    caminho[indice] = vOrigem;

    return caminho;
}

int buscaProxVertice(int* v, int origem, int destino, int size) {
    int* caminho = retornaCaminhoTerminal(v, origem, destino);
    int vertice = caminho[1];
    free(caminho);
    return vertice;
}