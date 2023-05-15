#include <stdio.h>
#include "file.h"
#include "grafo.h"

int main(int argc, char *argv[]) {

    // Verifica se os argumentos estao corretos
    verificaArgumentos(argc, argv);

    // Abre o arquivo de entrada
    FILE* arquivoEntrada = abreArquivoEntrada(argv[1]);

    int m, n;
    int vOrigem, vDestino;

    // Inicializa um vetor de arestas para representar o grafo
    Aresta** grafo = initGrafo(arquivoEntrada, &n, &m, &vOrigem, &vDestino);

    // Imprimindo o grafo para teste (deve ser removido)
    for (int i = 0; i < m; i++) {
        printf("%d %d %d %f\n", getOrigem(grafo[i]), getDestino(grafo[i]), getDistancia(grafo[i]), getTempo(grafo[i]));
    }


    fechaArquivo(arquivoEntrada);
    liberaGrafo(grafo, m);

    return 0;
}