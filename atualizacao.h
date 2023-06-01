#ifndef ATUALIZACAO_H
#define ATUALIZACAO_H

typedef struct atualizacao Atualizacao;

typedef struct atualizacoes Atualizacoes;

Atualizacoes* initAtualizacoes();

void liberaAtualizacoes(Atualizacoes* atualizacoes);

void insereAtualizacao(Atualizacoes* atualizacoes, int origem, int destino, int instante, double velocidade);

int getOrigemAtualizacao(Atualizacoes* atualizacoes, int i);

int getDestinoAtualizacao(Atualizacoes* atualizacoes, int i);

int getInstanteAtualizacao(Atualizacoes* atualizacoes, int i);

double getVelocidadeAtualizacao(Atualizacoes* atualizacoes, int i);

Atualizacao** getVetorAtualizacao(Atualizacoes* atualizacoes);

int getUltimaAtualizacao(Atualizacoes* atualizacoes);

void setUltimaAtualizacao(Atualizacoes** atualizacoes, int ultimaAtualizacao);

int getNAtual(Atualizacoes* atualizacoes);




#endif