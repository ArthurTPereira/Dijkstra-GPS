#include <stdio.h>
#include <stdlib.h>

#include "listaAdjacencia.h"
#include "atualizacao.h"
struct node {
    int destino;
    int distancia;
    float velocidade;
    float tempo;
    int visitado;
    Node* prox;
};

struct listaAdjacencia {
    Node* inicio;
};

struct grafo {
    int vertices;
    ListaAdjacencia** vetor;
};

Node* criaNode(int destino, int distancia, float velocidade) {
    Node* node = (Node*) malloc(sizeof(Node));
    node->destino = destino;
    node->distancia = distancia;
    node->velocidade = velocidade;
    node->tempo = (float) distancia / (velocidade / 3.6); // converte para m/s e calcula o tempo em segundos
    node->visitado = 0; // util depois para a fila de prioridade
    node->prox = NULL;
    return node;
}

Grafo* criaGrafo(int vertices) {
    Grafo* grafo = (Grafo*) malloc(sizeof(Grafo));
    grafo->vertices = vertices;
    grafo->vetor = (ListaAdjacencia**) malloc(vertices * sizeof(ListaAdjacencia*));
    for (int i = 0; i < vertices; i++) {
        grafo->vetor[i] = (ListaAdjacencia*) malloc(sizeof(ListaAdjacencia));
        grafo->vetor[i]->inicio = NULL;
    }
    
    return grafo;
}

void insereAresta(Grafo* grafo, int origem, int destino, int distancia, float velocidade) {
    Node* node = criaNode(destino, distancia, velocidade);
    node->prox = grafo->vetor[origem]->inicio;
    grafo->vetor[origem]->inicio = node;
}

void imprimeGrafo(Grafo* grafo) {
    int v;
    for (v = 0; v < grafo->vertices; v++) {
        Node* p = grafo->vetor[v]->inicio;
        printf("\n Lista de adjacências do vértice %d\n head ", v);
        while (p) {
            printf("-> %d (Peso: %d) (Tempo: %f)", p->destino, p->distancia, p->tempo);
            p = p->prox;
        }
        printf("\n");
    }   
}

void liberaGrafo(Grafo* grafo) {
    for (int i = 0; i < grafo->vertices; i++) {
        Node* p = grafo->vetor[i]->inicio;
        while (p) {
            Node* t = p->prox;
            free(p);
            p = t;
        }
        free(grafo->vetor[i]);
    }
    free(grafo->vetor);
    free(grafo);
}

Grafo* initGrafo(FILE* arquivoEntrada, int* nArestas, int* mArestas, int* vOrigem, int* vDestino, Atualizacoes* atualizacoes) {

    // Alocacao do buffer de leitura
    size_t bufferSize = 64;
    char * buffer = (char*) malloc(bufferSize * sizeof(char));

    // Obtem a primeira linha do CSV
    getline(&buffer, &bufferSize, arquivoEntrada);

    // Obter N e M
    sscanf(buffer, "%d;%d", nArestas, mArestas);

    // Alocacao do grafo
    Grafo* grafo = criaGrafo((*nArestas));

    // Obtem a segunda linha do CSV 
    getline(&buffer, &bufferSize, arquivoEntrada);

    // Obter vOrigem e vDestino
    sscanf(buffer, "%d;%d", vOrigem, vDestino);

    // Obtem a terceira linha do CSV 
    getline(&buffer, &bufferSize, arquivoEntrada);

    // Obtem a velocidade media
    float velocidadeMedia;
    sscanf(buffer, "%f", &velocidadeMedia);

    // Preenche o grafo
    int i = 0;
    int origem, destino, distancia;
    while (i < (*mArestas)) {
        getline(&buffer, &bufferSize, arquivoEntrada);
        sscanf(buffer, "%d;%d;%d", &origem, &destino, &distancia);
        insereAresta(grafo, origem, destino, distancia, velocidadeMedia);
        i++;
    }

    // Preenche as atualizacoes
    int instante;
    while (getline(&buffer, &bufferSize, arquivoEntrada) != -1) {
        sscanf(buffer, "%d;%d;%d;%f", &instante, &origem, &destino, &velocidadeMedia);
        insereAtualizacao(atualizacoes, origem, destino, instante, velocidadeMedia);
    }

    free(buffer);
    return grafo;
}

void atualizaGrafo(Grafo* grafo, int origem, int destino, float novaVelocidade) {
    Node* p = grafo->vetor[origem]->inicio;
    while (p != NULL) {
        if (p->destino == destino) {
            p->velocidade = novaVelocidade;
            p->tempo = (float) p->distancia / (novaVelocidade / 3.6);
        }
        p = p->prox;
    }
}