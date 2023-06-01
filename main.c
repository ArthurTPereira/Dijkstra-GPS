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

    double distanciaPercorrida = 0;
    double tempoPercorrido = 0;
    int* edgeTo = dijkstra(&grafo, vOrigem, vDestino, &atualizacoes, pq, map, &tempoPercorrido, &distanciaPercorrida);

    
    FILE* arquivoSaida = abreArquivoSaida(argv[2]);
    
    imprimeArquivo(arquivoSaida, edgeTo, vOrigem, vDestino, tempoPercorrido, distanciaPercorrida);
        
    free(edgeTo);
    PQ_finish(pq,map);
    fechaArquivo(arquivoEntrada);
    fechaArquivo(arquivoSaida);
    liberaGrafo(grafo);
    liberaAtualizacoes(atualizacoes);
    return 0;
}
