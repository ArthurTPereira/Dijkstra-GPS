#include <stdio.h>
#include "file.h"
#include "grafo.h"
#include "atualizacao.h"

int main(int argc, char *argv[]) {

    // Verifica se os argumentos estao corretos
    verificaArgumentos(argc, argv);

    // Abre o arquivo de entrada
    FILE* arquivoEntrada = abreArquivoEntrada(argv[1]);

    int m, n;
    int vOrigem, vDestino;

    Atualizacoes* atualizacoes = initAtualizacoes();

    // Inicializa um vetor de arestas para representar o grafo
    Aresta** grafo = initGrafo(arquivoEntrada, &n, &m, &vOrigem, &vDestino, atualizacoes);

    // Imprimindo o grafo para teste (deve ser removido)
    for (int i = 0; i < m; i++) {
        printf("%d %d %d %f\n", getOrigem(grafo[i]), getDestino(grafo[i]), getDistancia(grafo[i]), getTempo(grafo[i]));
    }

    // Imprimindo as atualizacoes para teste (deve ser removido)
    for (int i = 0; i < getNAtual(atualizacoes); i++) {
        printf("%d\n",getInstanteAtualizacao(atualizacoes, i));
    }

    fechaArquivo(arquivoEntrada);
    liberaGrafo(grafo, m);
    liberaAtualizacoes(atualizacoes);

    return 0;
}