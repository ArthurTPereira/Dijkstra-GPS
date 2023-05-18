#include <stdio.h>
#include "PQ.h"
#include "item.h"
#include <stdlib.h>

Item make_item(int id, double value) {
    Item t;
    id(t) = id;
    value(t) = value;
    return t;
}

int main2() {

    Item* pq;
    int* map;
    // inicializando a PQ
    PQ_init(&pq, &map, 10);

    // inserindo alguns elementos na PQ
    PQ_insert(pq,map,make_item(1, 10.0));
    PQ_insert(pq,map,make_item(6, 5.0));
    PQ_insert(pq,map,make_item(3, 3.0));
    PQ_insert(pq,map,make_item(4, 4.0));
    PQ_insert(pq,map,make_item(7, 7.0));
    PQ_insert(pq,map,make_item(2, 1.0));

    // alterando a prioridade de alguns elementos
    PQ_decrease_key(pq,map,4, 0.5); // agora o nó 4 tem valor 0.5, sua posição no heap deve mudar
    PQ_decrease_key(pq,map,6, 0.1); // agora o nó 6 tem valor 0.1, sua posição no heap deve mudar

    // removendo o menor elemento e imprimindo
    while (!PQ_empty(pq)) {
        Item p = PQ_delmin(pq,map);
        printf("Identificador %d, prioridade %lf\n", id(p), value(p));
    }

    PQ_finish(pq, map);

}
