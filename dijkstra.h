#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "item.h"

int* dijkstra(Grafo** grafo, int vOrigem, int vDestino, Atualizacoes** atualizacoes, Item* pq, int* map);

#endif
