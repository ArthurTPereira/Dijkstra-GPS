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
    int* edgeTo;

    // Insere o vertice de origem na priority queue
    PQ_insert(pq,map,make_item(vOrigem, 0));
    
    // Insere os demais vertices na priority queue
    for (int i = 1; i < getVertices(*(grafo)); i++) {
        if (i != vOrigem) {
            PQ_insert(pq,map,make_item(i, INT_MAX)); // INT_MAX representa infinito
        }
    }

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
        // continuar o algoritmo
    
    }

    return edgeTo;
}

