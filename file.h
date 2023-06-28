#ifndef FILE_H
#define FILE_H

#include <stdio.h>

void verificaArgumentos(int argc, char** argv);

FILE* abreArquivoEntrada(char* nomeArquivoEntrada);

FILE* abreArquivoSaida(char* nomeArquivoSaida);

void fechaArquivo(FILE* arquivo);

void imprimeArquivo(FILE* fp, int* vetor, int vOrigem, int vDestino, double tempoDecorrido, double distanciaPercorrida);
void imprimeCaminhoTerminal(int* vetor, int vOrigem, int vDestino);
#endif