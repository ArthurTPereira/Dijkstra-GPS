#ifndef DJIKSTRA_H
#define DJIKSTRA_H

#include "item.h"

int* djikstra(Grafo** grafo, int vOrigem, int vDestino, Atualizacoes** atualizacoes, Item* pq, int* map);

#endif