#include <stdio.h>
#include <stdlib.h>

#include "file.h"

#define ERROR -1

// verifica os argumentos de entrada para os arquivos
// Entrada: argc - numero de argumentos
//          argv - vetor de argumentos
// Saida:   void
void verificaArgumentos(int argc, char** argv) {
    if (argc != 3) {
        printf("Numero de argumentos invalido!\n");
        exit(ERROR);
    }

    for (int i = 1; i < argc; i++) {
        if (argv[i] == NULL) {
            printf("Erro ao ler argumento!\n");
            exit(ERROR);
        }
    }
}

// Abre o arquivo de entrada
// Entrada: nomeArquivoEntrada - nome do arquivo de entrada
// Saida:   ponteiro para o arquivo de entrada
FILE* abreArquivoEntrada(char* nomeArquivoEntrada) {
    FILE* arquivoEntrada = fopen(nomeArquivoEntrada, "r");
    if (arquivoEntrada == NULL) {
        printf("Erro ao abrir o arquivo de entrada!\n");
        exit(ERROR);
    }
    return arquivoEntrada;
}

// Abre o arquivo de saida
// Entrada: nomeArquivoSaida - nome do arquivo de saida
// Saida:   ponteiro para o arquivo de saida
FILE* abreArquivoSaida(char* nomeArquivoSaida) {
    FILE* arquivoSaida = fopen(nomeArquivoSaida, "w");
    if (arquivoSaida == NULL) {
        printf("Erro ao abrir o arquivo de saida!\n");
        exit(ERROR);
    }
    return arquivoSaida;
}

// Fecha o arquivo
// Entrada: arquivo - ponteiro para o arquivo
// Saida:   void
void fechaArquivo(FILE* arquivo) {
    fclose(arquivo);
}

// Imprime o menor caminho
// Entrada: vetor - vetor de vertices
//          vOrigem - vertice de origem
//          vDestino - vertice de destino
//          fp - ponteiro para o arquivo de saida
// Saida:   void
void imprimeCaminho(FILE* fp, int* vetor, int vOrigem, int vDestino) {
    if (vetor[vDestino] == 0) {
        fprintf(fp,"%d;", vOrigem);
        return;
    }
    
    imprimeCaminho(fp, vetor, vOrigem, vetor[vDestino]);

    static int primeiro = 1;

    if (primeiro) {
        fprintf(fp,"%d", vDestino);
        primeiro = 0;
    } else {
        fprintf(fp,";%d", vDestino);
    }
}

void imprimeTempo(FILE* fp, double tempoPercorrido){
    int horas = 0;
    int minutos;
    double segundos;
    
    horas = tempoPercorrido / 3600;
    minutos = (tempoPercorrido - (3600 * horas)) / 60;
    segundos = tempoPercorrido - ((3600 * horas) + (minutos * 60));

    fprintf(fp,"%02d:%02d:%lf", horas, minutos, segundos);
}

void imprimeDistancia(FILE* fp, double distanciaPercorrida){
    fprintf(fp, "%lf\n", distanciaPercorrida / 1000);
}

void imprimeArquivo(FILE* fp, int* vetor, int vOrigem, int vDestino, double tempoDecorrido, double distanciaPercorrida) {
    imprimeCaminho(fp, vetor, vOrigem, vDestino);
    fprintf(fp,"\n");
    imprimeDistancia(fp, distanciaPercorrida);
    imprimeTempo(fp, tempoDecorrido);
}