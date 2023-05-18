#ifndef PQ_H
#define PQ_H

#include <stdbool.h>
#include "item.h"

void PQ_init(Item** pq, int** map, int maxN); // cria uma min PQ com capacidade maxN
void PQ_insert(Item* pq, int* map, Item v);  // Insere Item na PQ. A maior prioridade é a do Item com menor campo 'value'
Item PQ_delmin(Item* pq, int* map);       // Remove Item com menor campo 'value' da PQ
void PQ_decrease_key(Item* pq, int* map, int id, double value); // Muda a prioridade do nó com identificador 'id' para 'value'
Item PQ_min(Item* pq);          // Retorna Item com menor campo 'value' da PQ
bool PQ_empty(Item* pq);        // Retorna True se a PQ não tem elementos
int  PQ_size(Item* pq);         // Número de elementos na PQ
void PQ_finish(Item* pq, int* map);       // Libera memória

#endif
