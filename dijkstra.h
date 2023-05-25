#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "item.h"

Node** dijkstra(Grafo** grafo, int vOrigem, int vDestino, Atualizacoes** atualizacoes, Item* pq, int* map, float* tempoDecorrido, float* distanciaPercorrida);

#endif
