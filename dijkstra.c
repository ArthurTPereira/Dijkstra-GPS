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

int* dijkstra(Grafo** grafo, int vOrigem, int vDestino, Atualizacoes** atualizacoes, Item* pq, int* map) {
    
    // TODO: Vetor timeTo e vetor edgeTo
    // Retorno: vetor edgeTo -> Podemos obter o menor caminho
    // Temos que retornar o tempo e a distancia de alguma forma
    int* edgeTo = (int*) malloc(getVertices(*(grafo)) * sizeof(int));
    float* timeTo = (float*) malloc(getVertices(*(grafo)) * sizeof(float));

    // Insere o vertice de origem na priority queue
    PQ_insert(pq,map,make_item(vOrigem, 0));
    
    // Insere os demais vertices na priority queue
    for (int i = 1; i < getVertices(*(grafo)); i++) {
        timeTo[i] = INT_MAX;
    }

    timeTo[vOrigem] = 0;

    float tempoDecorrido = 0;
    int instanteAtualizacao = 0;
    int atualizacaoAtual = 0;

    // Enquanto a priority queue nao estiver vazia
    while (!PQ_empty(pq)) {        
        // Verifica se ha atualizacoes no vetor e varre as atualizacoes que ocorrem apos o tempo decorrido atual
        while (getUltimaAtualizacao(*atualizacoes) < getNAtual(*atualizacoes) && tempoDecorrido >= getInstanteAtualizacao(*atualizacoes,getUltimaAtualizacao(*atualizacoes))) {
            // Obtem a atualizacao atual e o instante que ela ocorre
            atualizacaoAtual = getUltimaAtualizacao(*atualizacoes);
            instanteAtualizacao = getInstanteAtualizacao(*atualizacoes,atualizacaoAtual);

            // Atualiza o grafo com as novas atualizacoes
            atualizaGrafo(grafo,getOrigemAtualizacao(*atualizacoes,atualizacaoAtual),getDestinoAtualizacao(*atualizacoes,atualizacaoAtual),getVelocidadeAtualizacao(*atualizacoes,atualizacaoAtual));
                
            // Atualiza para a proxima atualizacao
            setUltimaAtualizacao(atualizacoes,atualizacaoAtual+1);
        }

        
        // Remove o elemento com menor prioridade
        Item p = PQ_delmin(pq,map);
        
        
    
    }

    free(timeTo);

    return edgeTo;
}

