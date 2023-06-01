#include <stdio.h>
#include <stdlib.h>

#include "atualizacao.h"

// Struct com uma atualizacao
struct atualizacao {
    int origem;
    int destino;
    int instante;
    double velocidade;
};

// Struct com o vetor de atualizacoes
struct atualizacoes {
    int ultimaAtualizacao;
    int nAtual;
    int nMax;
    Atualizacao** vetor;
};

// Funcao que aloca o vetor de atualizacoes
// Entrada: nenhuma
// Saida: vetor de atualizacoes
Atualizacoes* initAtualizacoes() {
    // Aloca a struct de atualizacoes
    Atualizacoes* atualizacoes = (Atualizacoes*) malloc(sizeof(Atualizacoes));
    if (atualizacoes == NULL) {
        printf("Erro ao alocar o vetor de atualizacoes!\n");
        exit(-1);
    }
    // Atribui os valores iniciais
    atualizacoes->ultimaAtualizacao = 0;
    atualizacoes->nAtual = 0;
    atualizacoes->nMax = 10; // Valor inicial maximo definido como 10

    // Aloca o vetor de atualizacoes
    atualizacoes->vetor = (Atualizacao**) malloc(atualizacoes->nMax * sizeof(Atualizacao*));
    if (atualizacoes->vetor == NULL) {
        printf("Erro ao alocar o vetor de atualizacoes!\n");
        exit(-1);
    }

    // Aloca cada atualizacao
    for (int i = 0; i < atualizacoes->nMax; i++) {
        atualizacoes->vetor[i] = (Atualizacao*) malloc(sizeof(Atualizacao));
    }
    
    return atualizacoes;
}

// Funcao que libera o vetor de atualizacoes
// Entrada: vetor de atualizacoes
// Saida: void
void liberaAtualizacoes(Atualizacoes* atualizacoes) {
    // Libera cada atualizacao
    for (int i = 0; i < atualizacoes->nMax; i++) {
        free(atualizacoes->vetor[i]);
    }
    // Libera o vetor de atualizacoes e a struct
    free(atualizacoes->vetor);
    free(atualizacoes);
}

// Funcao que insere uma atualizacao no vetor de atualizacoes
// Entrada: vetor de atualizacoes, origem, destino, instante e velocidade
// Saida: void
void insereAtualizacao(Atualizacoes* atualizacoes, int origem, int destino, int instante, double velocidade) {
    // Se o vetor estiver cheio, dobra o tamanho e realoca
    if (atualizacoes->nAtual == atualizacoes->nMax) {
        atualizacoes->nMax *= 2;
        atualizacoes->vetor = (Atualizacao**) realloc(atualizacoes->vetor, atualizacoes->nMax * sizeof(Atualizacao*));
        if (atualizacoes->vetor == NULL) {
            printf("Erro ao alocar o vetor de atualizacoes!\n");
            exit(-1);
        }
        // Aloca cada atualizacao apos o dobro do tamanho
        for (int i = atualizacoes->nAtual; i < atualizacoes->nMax; i++) {
            atualizacoes->vetor[i] = (Atualizacao*) malloc(sizeof(Atualizacao));
        }
    }
    // Atribui os valores da atualizacao
    atualizacoes->vetor[atualizacoes->nAtual]->origem = origem;
    atualizacoes->vetor[atualizacoes->nAtual]->destino = destino;
    atualizacoes->vetor[atualizacoes->nAtual]->instante = instante;
    atualizacoes->vetor[atualizacoes->nAtual]->velocidade = velocidade;
    // Incrementa o numero de atualizacoes
    atualizacoes->nAtual++;
}

// Funcao que retorna a origem de uma atualizacao
// Entrada: vetor de atualizacoes e indice da atualizacao
// Saida: origem da atualizacao
int getOrigemAtualizacao(Atualizacoes* atualizacoes, int i) {
    return atualizacoes->vetor[i]->origem;
}

// Funcao que retorna o destino de uma atualizacao
// Entrada: vetor de atualizacoes e indice da atualizacao
// Saida: destino da atualizacao
int getDestinoAtualizacao(Atualizacoes* atualizacoes, int i) {
    return atualizacoes->vetor[i]->destino;
}

// Funcao que retorna o instante de uma atualizacao
// Entrada: vetor de atualizacoes e indice da atualizacao
// Saida: instante da atualizacao
int getInstanteAtualizacao(Atualizacoes* atualizacoes, int i) {
    return atualizacoes->vetor[i]->instante;
}

// Funcao que retorna a velocidade de uma atualizacao
// Entrada: vetor de atualizacoes e indice da atualizacao
// Saida: velocidade da atualizacao
double getVelocidadeAtualizacao(Atualizacoes* atualizacoes, int i) {
    return atualizacoes->vetor[i]->velocidade;
}

// Funcao que retorna o vetor de atualizacoes
// Entrada: Struct de atualizacoes
// Saida: vetor de atualizacoes
Atualizacao** getVetorAtualizacao(Atualizacoes* atualizacoes) {
    return atualizacoes->vetor;
}

// Funcao que retorna qual foi a ultima atualizacao realizada do vetor
// Entrada: vetor de atualizacoes
// Saida: ultima atualizacao realizada
int getUltimaAtualizacao(Atualizacoes* atualizacoes) {
    return atualizacoes->ultimaAtualizacao;
}

// Funcao que altera qual foi a ultima atualizacao realizada do vetor
// Entrada: vetor de atualizacoes e ultima atualizacao realizada
// Saida: void
void setUltimaAtualizacao(Atualizacoes** atualizacoes, int ultimaAtualizacao) {
    (*atualizacoes)->ultimaAtualizacao = ultimaAtualizacao;
}

// Funcao que retorna o numero de atualizacoes do vetor
// Entrada: vetor de atualizacoes
// Saida: numero de atualizacoes existentes
int getNAtual(Atualizacoes* atualizacoes) {
    return atualizacoes->nAtual;
}


