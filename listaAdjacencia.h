#ifndef LISTAADJACENCIA_H
#define LISTAADJACENCIA_H

#include "atualizacao.h"

typedef struct node Node;

typedef struct listaAdjacencia ListaAdjacencia;

typedef struct grafo Grafo;

Node* criaNode(int destino, int distancia, float velocidade);

Grafo* criaGrafo(int vertices);

void insereAresta(Grafo* grafo, int origem, int destino, int distancia, float velocidade);

void imprimeGrafo(Grafo* grafo);

Grafo* initGrafo(FILE* arquivoEntrada, int* nVertices, int* mArestas, int* vOrigem, int* vDestino, Atualizacoes* atualizacoes);

void liberaGrafo(Grafo* grafo);

void atualizaGrafo(Grafo* grafo, int origem, int destino, float novaVelocidade);

#endif