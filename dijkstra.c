#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "listaAdjacencia.h"
#include "atualizacao.h"
#include "dijkstra.h"
#include "PQ.h"

Item make_item(int id, double value) {
    Item t;
    id(t) = id;
    value(t) = value;
    return t;
}

int* dijkstra(Grafo** grafo, int vOrigem, int vDestino, Atualizacoes** atualizacoes, Item* pq, int* map, double* tempoDecorrido, double* distanciaPercorrida) {
    
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

        for (Node* adj = getListaAdjacencia((*grafo),vertice); adj != NULL; adj = getProx(adj)) {
            int v = getOrigem(adj);
            int w = getDestino(adj);
            double tempo = getTempo(adj);
            double distancia = getDistancia(adj);
            

            if (timeTo[w] > timeTo[v] + tempo) {
                timeTo[w] = timeTo[v] + tempo;
                distTo[w] = distTo[v] + distancia;
                edgeTo[w] = v;
                
                if (PQ_contains(pq,w)) {
                    PQ_decrease_key(pq,map,w,timeTo[w]);
                } else {
                    PQ_insert(pq,map,make_item(w,timeTo[w]));
                }
            }
        }
    }
    *tempoDecorrido = timeTo[vDestino];
    *distanciaPercorrida = distTo[vDestino];
    free(timeTo);
    free(distTo);
    imprimeCaminho(edgeTo, vOrigem, vDestino);
    return edgeTo;
}
