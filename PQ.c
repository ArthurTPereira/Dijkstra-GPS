#include <stdio.h>
#include <stdlib.h>
#include "PQ.h"

static void swap(Item* pq, int* map, int i, int j) {
    exch(pq[i], pq[j]);
    map[id(pq[i])] = i;
    map[id(pq[j])] = j;
}

void fix_up(Item* pq, int* map, Item *a, int k) {
    while (k > 1 && more(a[k/2], a[k])) {
        swap(pq, map, k, k/2);
        k = k/2;
    }
}

void fix_down(Item* pq, int* map, Item *a, int sz, int k){
  while (2*k <= sz) {
    int j = 2*k;
    if (j < sz && more(a[j], a[j+1])){
      j++;
    }
    if (!more(a[k], a[j])) {
      break;
    }
    swap(pq,map, k, j);
    k = j;
  }
}

void PQ_init(Item** pq, int** map, int maxN) {
    (*pq) = (Item *) malloc((maxN+1) * sizeof (Item));
    (*map) = (int *) malloc((maxN+1) * sizeof (int));
    (*pq)->N = 0;
}

void PQ_insert(Item* pq, int* map, Item v) {
    pq->N++;
    pq[pq->N] = v;
    map[id(v)] = pq->N;
    fix_up(pq, map, pq, pq->N);
}

Item PQ_delmin(Item* pq, int* map) {
    Item min = pq[1];
    swap(pq, map, 1, pq->N);
    pq->N--;
    fix_down(pq, map, pq, pq->N, 1);
    return min;
}

Item PQ_min(Item* pq) {
    return pq[1];
}

void PQ_decrease_key(Item* pq, int* map, int id, double value) {
    int i = map[id];
    value(pq[i]) = value;
    fix_up(pq, map, pq, i);
}

bool PQ_empty(Item* pq) {
    return pq->N == 0;
}

int  PQ_size(Item* pq) {
    return pq->N;
}

void PQ_finish(Item* pq, int* map) {
    free(pq);
    free(map);
}

bool PQ_contains(Item* pq, int vertice) {
    for (int i = 1; i <= pq->N; i++) {
        if (id(pq[i]) == vertice) {
            return true;
        }
    }
    return false;
}


