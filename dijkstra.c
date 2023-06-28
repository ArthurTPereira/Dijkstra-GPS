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

int* dijkstra(Grafo** grafo, int vOrigem, int vDestino) {
    
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

// Funcao que executa o algoritmo de Dijkstra em loop
// Entrada: grafo - Grafo
//          vOrigem - Vertice de origem
//          vDestino - Vertice de destino
//          atualizacoes - Lista de atualizacoes
//          tempoDecorrido - Tempo decorrido
//          distanciaPercorrida - Distancia percorrida
// Saida:   int* - Vetor com o menor caminho final
int* DijkstraLoop(Grafo** grafo,int vOrigem, int vDestino, Atualizacoes** atualizacoes, double* tempoDecorrido, double* distanciaPercorrida) {

    // Variaveis temporarias
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

    // Enquanto o vertice de origem nao for o vertice de destino
    while(origemTemp != vDestino) {

        // Enquanto houver atualizacoes e o tempo total for maior ou igual ao instante da atualizacao
        while (getUltimaAtualizacao(*atualizacoes) < getNAtual(*atualizacoes) && (tempoTotal) >= getInstanteAtualizacao(*atualizacoes,getUltimaAtualizacao(*atualizacoes))) {
        // Obtem a atualizacao atual e o instante que ela ocorre
        atualizacaoAtual = getUltimaAtualizacao(*atualizacoes);
        instanteAtualizacao = getInstanteAtualizacao(*atualizacoes,atualizacaoAtual);
        // Atualiza o grafo com as novas atualizacoes
        atualizaGrafo(grafo,getOrigemAtualizacao(*atualizacoes,atualizacaoAtual),getDestinoAtualizacao(*atualizacoes,atualizacaoAtual),getVelocidadeAtualizacao(*atualizacoes,atualizacaoAtual));
        // Atualiza para a proxima atualizacao
        setUltimaAtualizacao(atualizacoes,atualizacaoAtual+1);
        }

        // Se o caminho nao for nulo libera a memoria temporaria
        if (caminho != NULL) {
            free(caminho);
        }

        // Obtem o menor caminho atual
        caminho = dijkstra(grafo,origemTemp,vDestino);
        
        // Obtem o proximo vertice do caminho
        proxVertice = buscaProxVertice(caminho, origemTemp, vDestino);

        // Incrementa o tempo total e a distancia total
        tempoTotal += getTempoEntreVertices(*grafo,origemTemp,proxVertice);
        distanciaTotal += getDistanciaEntreVertices(*grafo,origemTemp,proxVertice);

        // Adiciona o vertice atual ao vetor de menor caminho final
        edgeTo[i+1] = proxVertice;

        // Avanca para o proximo vertice
        origemTemp = proxVertice;
        i++;
    }

    // Atualiza o tempo decorrido e a distancia percorrida
    *tempoDecorrido = tempoTotal;
    *distanciaPercorrida = distanciaTotal;

    // Libera a memoria temporaria
    free(caminho);

    return edgeTo;
    
}

// Funcao que retorna o caminho entre dois vertices
// Entrada: vetor - vetor com os vertices
//          vOrigem - vertice de origem
//          vDestino - vertice de destino
// Saida:   int* - vetor com o caminho
int* retornaCaminho(int* vetor, int vOrigem, int vDestino) {
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

// Funcao que busca o proximo vertice do caminho
// Entrada: v - vetor com o caminho
//          origem - vertice de origem
//          destino - vertice de destino
// Saida:   int - proximo vertice do caminho
int buscaProxVertice(int* v, int origem, int destino) {
    int* caminho = retornaCaminho(v, origem, destino);
    int vertice = caminho[1];
    free(caminho);
    return vertice;
}