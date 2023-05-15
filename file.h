#ifndef FILE_H
#define FILE_H

#include <stdio.h>

void verificaArgumentos(int argc, char** argv);

FILE* abreArquivoEntrada(char* nomeArquivoEntrada);

FILE* abreArquivoSaida(char* nomeArquivoSaida);

void fechaArquivo(FILE* arquivo);

#endif