#include <stdio.h>
#include <stdlib.h>

#include "grafo.h"

#define ERROR -1

struct aresta {
    int origem;
    int destino;
    int distancia; // metros
    float tempo; // segundos
};

Aresta** alocaGrafo(int m) {
    Aresta** grafo = (Aresta**) malloc(m * sizeof(Aresta*));
    if (grafo == NULL) {
        printf("Erro ao alocar o grafo!\n");
        exit(ERROR);
    }
    for (int i = 0; i < m; i++) {
        grafo[i] = (Aresta*) malloc(m * sizeof(Aresta));
        if (grafo[i] == NULL) {
            printf("Erro ao alocar o grafo!\n");
            exit(ERROR);
        }
    }
    return grafo;
}

void liberaGrafo(Aresta** grafo, int m) {
    for (int i = 0; i < m; i++) {
        free(grafo[i]);
    }
    free(grafo);
}

Aresta** initGrafo(FILE* arquivoEntrada, int* n, int* m, int* vOrigem, int* vDestino) {

    // Alocacao do buffer de leitura
    size_t bufferSize = 64;
    char * buffer = (char*) malloc(bufferSize * sizeof(char));

    // Obtem a primeira linha do CSV
    getline(&buffer, &bufferSize, arquivoEntrada);

    // Obter N e M
    sscanf(buffer, "%d;%d", n, m);

    // Alocacao do grafo
    Aresta** grafo = alocaGrafo((*m));

    // Obtem a segunda linha do CSV 
    getline(&buffer, &bufferSize, arquivoEntrada);

    // Obter vOrigem e vDestino
    sscanf(buffer, "%d;%d", vOrigem, vDestino);

    // Obtem a terceira linha do CSV 
    getline(&buffer, &bufferSize, arquivoEntrada);

    // Obtem a velocidade media
    float velocidadeMedia;
    sscanf(buffer, "%f", &velocidadeMedia);

    // Preenche o grafo
    int i = 0;
    int origem, destino, distancia;
    while (i < (*m)) {
        getline(&buffer, &bufferSize, arquivoEntrada);
        sscanf(buffer, "%d;%d;%d", &origem, &destino, &distancia);
        grafo[i]->origem = origem;
        grafo[i]->destino = destino;
        grafo[i]->distancia = distancia;
        grafo[i]->tempo = 3600 * (distancia / (velocidadeMedia * 1000)); // Tempo em segundos
        i++;
    }

    // ! TODO: Armazenar as alteracoes de velocidade das vias

    free(buffer);
    return grafo;
}

int getOrigem(Aresta* aresta) {
    return aresta->origem;
}

int getDestino(Aresta* aresta) {
    return aresta->destino;
}

int getDistancia(Aresta* aresta) {
    return aresta->distancia;
}

float getTempo(Aresta* aresta) {
    return aresta->tempo;
}

void atualizaTempo(Aresta* aresta, float tempo) {
    aresta->tempo = tempo;
}