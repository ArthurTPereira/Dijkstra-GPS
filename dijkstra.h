#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "item.h"
#include "listaAdjacencia.h"
int* dijkstra(Grafo** grafo, int vOrigem, int vDestino);
int buscaProxVertice(int* v, int origem, int destino);
int* DijkstraLoop(Grafo** grafo,int vOrigem, int vDestino, Atualizacoes** atualizacoes, double* tempoDecorrido, double* distanciaPercorrida);
#endif
