#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "listaAdjacencia.h"
#include "atualizacao.h"
#include "djikstra.h"
#include "PQ.h"

Item make_item(int id, double value) {
    Item t;
    id(t) = id;
    value(t) = value;
    return t;
}

void djikstra(Grafo** grafo, int vOrigem, int vDestino, Atualizacoes** atualizacoes, Item* pq, int* map) {
    
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
        // Obtem qual a atualizacao que deve ser feita e o instante
        atualizacaoAtual = getUltimaAtualizacao(*atualizacoes);
        instanteAtualizacao = getInstanteAtualizacao(*atualizacoes,atualizacaoAtual);

        // Verifica se o tempo decorrido alcançou o instante de atualizacao
        if (tempoDecorrido > instanteAtualizacao) {
            // Atualiza o grafo com as novas atualizacoes
            atualizaGrafo(grafo,getOrigemAtualizacao(*atualizacoes,atualizacaoAtual),getDestinoAtualizacao(*atualizacoes,atualizacaoAtual),getVelocidadeAtualizacao(*atualizacoes,atualizacaoAtual));
            setUltimaAtualizacao(atualizacoes,atualizacaoAtual+1);
            tempoDecorrido += instanteAtualizacao;
        }
        
        // Remove o elemento com menor prioridade
        Item p = PQ_delmin(pq,map);
        printf("Identificador %d, prioridade %lf\n", id(p), value(p));
        // continuar o algoritmo

    }
}

