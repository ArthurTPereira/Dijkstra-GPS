#ifndef LISTAADJACENCIA_H
#define LISTAADJACENCIA_H

#include "atualizacao.h"

typedef struct node Node;

typedef struct listaAdjacencia ListaAdjacencia;

typedef struct grafo Grafo;

Node* criaNode(int origem, int destino, float distancia, float velocidade);

Grafo* criaGrafo(int vertices);

void insereAresta(Grafo* grafo, int origem, int destino, float distancia, float velocidade);

void imprimeGrafo(Grafo* grafo);

Grafo* initGrafo(FILE* arquivoEntrada, int* nVertices, int* mArestas, int* vOrigem, int* vDestino, Atualizacoes* atualizacoes);

void liberaGrafo(Grafo* grafo);

void atualizaGrafo(Grafo** grafo, int origem, int destino, float novaVelocidade);

int getVertices(Grafo* grafo);

Node* getListaAdjacencia(Grafo* grafo, int vertice);

Node* getProx(Node* node);

int getDestino(Node* node);

float getDistancia(Node* node);

float getTempo(Node* node);

int getOrigem(Node* node);

#endif