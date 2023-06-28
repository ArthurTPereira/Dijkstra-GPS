#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "item.h"

int* dijkstra(Grafo** grafo, int vOrigem, int vDestino, Atualizacoes** atualizacoes, Item* pq, int* map, double* tempoDecorrido, double* distanciaPercorrida);
int* dijkstra2(Grafo** grafo, int vOrigem, int vDestino);
int buscaProxVertice(int* v, int origem,int destino, int size);
int* DijkstraLoop(Grafo** grafo,int vOrigem, int vDestino, Atualizacoes** atualizacoes, double* tempoDecorrido, double* distanciaPercorrida);
#endif
