#ifndef GRAFO_H
#define GRAFO_H

#include "atualizacao.h"

typedef struct aresta Aresta;

void liberaGrafo(Aresta** grafo, int m);

Aresta** initGrafo(FILE* arquivoEntrada, int* n, int* m, int* vOrigem, int* vDestino, Atualizacoes* atualizacoes);

int getOrigem(Aresta* aresta);

int getDestino(Aresta* aresta);

int getDistancia(Aresta* aresta);

float getTempo(Aresta* aresta);

void atualizaTempo(Aresta* aresta, float tempo);

#endif