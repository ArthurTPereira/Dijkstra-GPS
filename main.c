#include <stdio.h>
#include "file.h"
#include "atualizacao.h"
#include "listaAdjacencia.h"
#include "PQ.h"
#include "djikstra.h"
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

    djikstra(&grafo, vOrigem, vDestino, &atualizacoes, pq, map);

    // funcao para imprimir o grafo (deve ser removida)
    //imprimeGrafo(grafo);

    PQ_finish(pq,map);
    fechaArquivo(arquivoEntrada);
    liberaGrafo(grafo);
    liberaAtualizacoes(atualizacoes);

    return 0;
}