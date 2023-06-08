#ifndef LISTAADJACENCIA_H
#define LISTAADJACENCIA_H

#include "atualizacao.h"

typedef struct node Node;

typedef struct listaAdjacencia ListaAdjacencia;

typedef struct grafo Grafo;

Node* criaNode(int origem, int destino, double distancia, double velocidade);

Grafo* criaGrafo(int vertices);

void insereAresta(Grafo* grafo, int origem, int destino, double distancia, double velocidade);

Grafo* initGrafo(FILE* arquivoEntrada, int* nVertices, int* mArestas, int* vOrigem, int* vDestino, Atualizacoes* atualizacoes);

void liberaGrafo(Grafo* grafo);

void atualizaGrafo(Grafo** grafo, int origem, int destino, double novaVelocidade);

int getVertices(Grafo* grafo);

Node* getListaAdjacencia(Grafo* grafo, int vertice);

Node* getProx(Node* node);

int getDestino(Node* node);

double getDistancia(Node* node);

double getTempo(Node* node);

int getOrigem(Node* node);

#endif