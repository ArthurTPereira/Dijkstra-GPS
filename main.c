#include <stdio.h>
#include "file.h"
#include "atualizacao.h"
#include "listaAdjacencia.h"

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

    // TODO: 
    // - Utilizar a priority queue com a lista de adjacencia
    // - Implementar o algoritmo de Dijkstra
    // - Antes de cada iteracao do algoritmo, verificar se ha atualizacoes nas rotas
    // - Criar uma funcao para atualizar as rotas no grafo

    // funcao para imprimir o grafo (deve ser removida)
    imprimeGrafo(grafo);

    fechaArquivo(arquivoEntrada);
    liberaGrafo(grafo);
    liberaAtualizacoes(atualizacoes);

    return 0;
}