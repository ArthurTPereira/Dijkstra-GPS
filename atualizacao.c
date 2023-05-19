#include <stdio.h>
#include <stdlib.h>

#include "atualizacao.h"

struct atualizacao {
    int origem;
    int destino;
    int instante;
    float velocidade;
};

struct atualizacoes {
    int ultimaAtualizacao;
    int nAtual;
    int nMax;
    Atualizacao** vetor;
};

Atualizacoes* initAtualizacoes() {
    Atualizacoes* atualizacoes = (Atualizacoes*) malloc(sizeof(Atualizacoes));
    if (atualizacoes == NULL) {
        printf("Erro ao alocar o vetor de atualizacoes!\n");
        exit(-1);
    }
    atualizacoes->ultimaAtualizacao = -1;
    atualizacoes->nAtual = 0;
    atualizacoes->nMax = 10;
    atualizacoes->vetor = (Atualizacao**) malloc(atualizacoes->nMax * sizeof(Atualizacao*));
    if (atualizacoes->vetor == NULL) {
        printf("Erro ao alocar o vetor de atualizacoes!\n");
        exit(-1);
    }
    for (int i = 0; i < atualizacoes->nMax; i++) {
        atualizacoes->vetor[i] = (Atualizacao*) malloc(sizeof(Atualizacao));
    }
    
    return atualizacoes;
}

void liberaAtualizacoes(Atualizacoes* atualizacoes) {
    for (int i = 0; i < atualizacoes->nMax; i++) {
        free(atualizacoes->vetor[i]);
    }
    free(atualizacoes->vetor);
    free(atualizacoes);
}

void insereAtualizacao(Atualizacoes* atualizacoes, int origem, int destino, int instante, float velocidade) {
    if (atualizacoes->nAtual == atualizacoes->nMax) {
        atualizacoes->nMax *= 2;
        atualizacoes->vetor = (Atualizacao**) realloc(atualizacoes->vetor, atualizacoes->nMax * sizeof(Atualizacao*));
        if (atualizacoes->vetor == NULL) {
            printf("Erro ao alocar o vetor de atualizacoes!\n");
            exit(-1);
        }
        for (int i = atualizacoes->nAtual; i < atualizacoes->nMax; i++) {
            atualizacoes->vetor[i] = (Atualizacao*) malloc(sizeof(Atualizacao));
        }
    }
    atualizacoes->vetor[atualizacoes->nAtual]->origem = origem;
    atualizacoes->vetor[atualizacoes->nAtual]->destino = destino;
    atualizacoes->vetor[atualizacoes->nAtual]->instante = instante;
    atualizacoes->vetor[atualizacoes->nAtual]->velocidade = velocidade;
    atualizacoes->nAtual++;
}

int getOrigemAtualizacao(Atualizacoes* atualizacoes, int i) {
    return atualizacoes->vetor[i]->origem;
}

int getDestinoAtualizacao(Atualizacoes* atualizacoes, int i) {
    return atualizacoes->vetor[i]->destino;
}

int getInstanteAtualizacao(Atualizacoes* atualizacoes, int i) {
    return atualizacoes->vetor[i]->instante;
}

float getVelocidadeAtualizacao(Atualizacoes* atualizacoes, int i) {
    return atualizacoes->vetor[i]->velocidade;
}

Atualizacao** getVetorAtualizacao(Atualizacoes* atualizacoes) {
    return atualizacoes->vetor;
}

int getUltimaAtualizacao(Atualizacoes* atualizacoes) {
    return atualizacoes->ultimaAtualizacao;
}

void setUltimaAtualizacao(Atualizacoes* atualizacoes, int ultimaAtualizacao) {
    atualizacoes->ultimaAtualizacao = ultimaAtualizacao;
}

int getNAtual(Atualizacoes* atualizacoes) {
    return atualizacoes->nAtual;
}


