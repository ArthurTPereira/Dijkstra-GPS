#include <stdio.h>
#include <stdlib.h>

#include "listaAdjacencia.h"
#include "atualizacao.h"

// Struct com um no da lista de adjacencia
struct node {
    int origem;
    int destino;
    double distancia;
    double tempo;
    Node* prox;
};

// Struct com a lista de adjacencia
struct listaAdjacencia {
    Node* inicio;
};

// Struct com o vetor de listas de adjacencia
struct grafo {
    int vertices;
    ListaAdjacencia** vetor;
};

// Funcao que cria um no da lista de adjacencia
// Entrada: vertice destino, distancia e velocidade
// Saida: no da lista de adjacencia
Node* criaNode(int origem, int destino, double distancia, double velocidade) {
    // Aloca um no
    Node* node = (Node*) malloc(sizeof(Node));
    
    // Atribui os valores
    node->origem = origem;
    node->destino = destino;
    node->distancia = distancia;

    // Converte para m/s e calcula o tempo em segundos
    node->tempo = distancia / (velocidade / 3.6);
    node->prox = NULL;
    return node;
}

// Funcao que aloca o grafo
// Entrada: numero de vertices
// Saida: grafo
Grafo* criaGrafo(int vertices) {
    // Aloca o grafo
    Grafo* grafo = (Grafo*) malloc(sizeof(Grafo));
    grafo->vertices = vertices + 1; // +1 para o vertice 0
    
    // Aloca o vetor de listas de adjacencia
    grafo->vetor = (ListaAdjacencia**) malloc(grafo->vertices * sizeof(ListaAdjacencia*));
    
    // Aloca cada lista de adjacencia
    for (int i = 0; i < grafo->vertices; i++) {
        grafo->vetor[i] = (ListaAdjacencia*) malloc(sizeof(ListaAdjacencia));
        grafo->vetor[i]->inicio = NULL;
    }
    
    return grafo;
}

// Funcao que insere uma aresta no inicio da lista de adjacencia
// Entrada: grafo, vertice origem, vertice destino, distancia e velocidade
// Saida: void
void insereAresta(Grafo* grafo, int origem, int destino, double distancia, double velocidade) {
    // Cria um no para o vertice destino
    Node* node = criaNode(origem, destino, distancia, velocidade);
    
    // Atribui o proximo no como o inicio da lista de adjacencia
    node->prox = grafo->vetor[origem]->inicio;

    // Atribui o inicio da lista de adjacencia como o novo no
    grafo->vetor[origem]->inicio = node;
}

// Funcao que libera o grafo
// Entrada: grafo
// Saida: void
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

// Funcao que inicializa o grafo com as informacoes do arquivo de entrada
// Entrada: arquivo de entrada, numero de arestas, numero de arestas, vertice origem, vertice destino, lista de atualizacoes
// Saida: grafo
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
    double velocidadeMedia;
    sscanf(buffer, "%lf", &velocidadeMedia);

    // Preenche o grafo
    int i = 0;
    int origem, destino;
    double distancia;

    // Enquanto houver arestas, insere no grafo
    while (i < (*mArestas)) {
        getline(&buffer, &bufferSize, arquivoEntrada);
        sscanf(buffer, "%d;%d;%lf", &origem, &destino, &distancia);
        insereAresta(grafo, origem, destino, distancia, velocidadeMedia);
        i++;
    }

    int instante;
    // Preenche as atualizacoes
    // Enquanto houver atualizacoes ate o fim do arquivo, insere no vetor de atualizacoes
    while (getline(&buffer, &bufferSize, arquivoEntrada) != -1) {
        sscanf(buffer, "%d;%d;%d;%lf", &instante, &origem, &destino, &velocidadeMedia);
        insereAtualizacao(atualizacoes, origem, destino, instante, velocidadeMedia);
    }

    // Libera o buffer usado para leitura
    free(buffer);
    return grafo;
}

// Funcao que insere uma atualizacao no grafo
// Entrada: grafo, vertice origem, vertice destino e nova velocidade da aresta
// Saida: void
void atualizaGrafo(Grafo** grafo, int origem, int destino, double novaVelocidade) {
    // Obtem o inicio da lista para o vertice origem
    Node* p = (*grafo)->vetor[origem]->inicio;

    // Enquanto nao chegar no fim da lista, busca o vertice destino
    while (p != NULL) {
        if (p->destino == destino) {

            // Atrubui nova velocidade e calcula o novo tempo
            p->tempo = p->distancia / (novaVelocidade / 3.6);
        }
        p = p->prox;
    }
}

// Funcao que retorna os vertices do grafo
// Entrada: grafo
// Saida: numero de vertices
int getVertices(Grafo* grafo) {
    return grafo->vertices;
}

// Funcao que retorna a lista de adjacencia de um vertice
// Entrada: grafo, vertice
// Saida: lista de adjacencia
Node* getListaAdjacencia(Grafo* grafo, int vertice) {
    return grafo->vetor[vertice]->inicio;
}

// Funcao que retorna o proximo no da lista de adjacencia
// Entrada: no
// Saida: proximo no
Node* getProx(Node* node) {
    return node->prox;
}
// Funcao que retorna o vertice destino
// Entrada: no
// Saida: vertice destino
int getDestino(Node* node) {
    return node->destino;
}

// Funcao que retorna a distancia
// Entrada: no
// Saida: distancia
double getDistancia(Node* node) {
    return node->distancia;
}

// Funcao que retorna o tempo de percurso
// Entrada: no
// Saida: tempo de percurso
double getTempo(Node* node) {
    return node->tempo;
}

// Funcao que retorna a origem
// Entrada: no
// Saida: origem
int getOrigem(Node* node) {
    return node->origem;
}

double getTempoEntreVertices(Grafo* grafo, int origem, int destino) {
    Node* p = grafo->vetor[origem]->inicio;
    while (p != NULL) {
        if (p->destino == destino) {
            return p->tempo;
        }
        p = p->prox;
    }
    return -1;
}

double getDistanciaEntreVertices(Grafo* grafo, int origem, int destino) {
    Node* p = grafo->vetor[origem]->inicio;
    while (p != NULL) {
        if (p->destino == destino) {
            return p->distancia;
        }
        p = p->prox;
    }
    return -1;
}