#include <stdio.h>
#include <stdlib.h>
#include "file.h"
#include "atualizacao.h"
#include "listaAdjacencia.h"
#include "PQ.h"
#include "dijkstra.h"

int main(int argc, char *argv[]) {

    // Verifica se os argumentos estao corretos
    verificaArgumentos(argc, argv);

    // Abre o arquivo de entrada
    FILE* arquivoEntrada = abreArquivoEntrada(argv[1]);

    int nVertices,mArestas;
    int vOrigem, vDestino;

    Atualizacoes* atualizacoes = initAtualizacoes();

    // Inicializa um grafo usando lista de adjacencia
    Grafo* grafo = initGrafo(arquivoEntrada, &nVertices, &mArestas, &vOrigem, &vDestino, atualizacoes);

    Item* pq;
    int* map;
    PQ_init(&pq,&map,nVertices);

    float distanciaPercorrida = 0;
    float tempoPercorrido = 0;
    Node** edgeTo = dijkstra(&grafo, vOrigem, vDestino, &atualizacoes, pq, map, &tempoPercorrido, &distanciaPercorrida);

    printf("\nDistancia percorrida: %.2f\n", distanciaPercorrida);
    printf("Tempo decorrido: %.2f\n", tempoPercorrido);
    
    free(edgeTo);
    // funcao para imprimir o grafo (deve ser removida)
    //imprimeGrafo(grafo);

    PQ_finish(pq,map);
    fechaArquivo(arquivoEntrada);
    liberaGrafo(grafo);
    liberaAtualizacoes(atualizacoes);
    return 0;
}
