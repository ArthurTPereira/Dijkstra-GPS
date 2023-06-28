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

    // Inicializa as variaveis
    int nVertices,mArestas;
    int vOrigem, vDestino;

    // Inicializa o vetor de atualizacoes
    Atualizacoes* atualizacoes = initAtualizacoes();

    // Inicializa um grafo usando lista de adjacencia
    Grafo* grafo = initGrafo(arquivoEntrada, &nVertices, &mArestas, &vOrigem, &vDestino, atualizacoes);

    // Fecha o arquivo de entrada
    fechaArquivo(arquivoEntrada);

    // Variaveis de distancia e tempo
    double distanciaPercorrida = 0;
    double tempoPercorrido = 0;

    // Executa o algoritmo de Dijkstra
    //int* edgeTo = dijkstra(&grafo, vOrigem, vDestino, &atualizacoes, pq, map, &tempoPercorrido, &distanciaPercorrida);
    int* edgeTo = DijkstraLoop(&grafo,vOrigem,vDestino, &atualizacoes, &tempoPercorrido, &distanciaPercorrida);
    // Abre o arquivo de saida
    FILE* arquivoSaida = abreArquivoSaida(argv[2]);

    // Imprime o menor caminho, o tempo decorrido e a distancia percorrida
    imprimeArquivo(arquivoSaida, edgeTo, vOrigem, vDestino, tempoPercorrido, distanciaPercorrida);
    
    // Libera o vetor de vertices
    free(edgeTo);

    // Libera a priority queue e o vetor de mapeamento
    

    // Fecha o arquivo de saida
    fechaArquivo(arquivoSaida);

    // Libera o grafo e as atualizacoes
    liberaGrafo(grafo);
    liberaAtualizacoes(atualizacoes);

    return 0;
}
