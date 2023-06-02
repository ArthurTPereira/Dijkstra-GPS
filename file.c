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

    // Caso o vertice de destino seja igual ao vertice de origem
    if (vetor[vDestino] == 0) {
        fprintf(fp,"%d;", vOrigem);
        return;
    }
    
    // Chamada recursiva para imprimir o menor caminho
    imprimeCaminho(fp, vetor, vOrigem, vetor[vDestino]);

    // Verificador estatico para nao imprimir o ponto e virgula no ultimo vertice do caminho
    static int primeiro = 1;

    // Imprime o vertice
    if (primeiro) {
        fprintf(fp,"%d", vDestino);
        primeiro = 0;
    } else {
        fprintf(fp,";%d", vDestino);
    }
}

// Funcao que imprime o tempo decorrido final
// Entrada: fp - ponteiro para o arquivo de saida
//          tempoPercorrido - tempo decorrido
// Saida:   void
void imprimeTempo(FILE* fp, double tempoPercorrido) {

    // Variaveis do tempo
    int horas;
    int minutos;
    double segundos;
    
    // Calcula as horas
    horas = tempoPercorrido / 3600;
    
    // Calcula os minutos pela diferenca entre o tempo decorrido e as horas
    minutos = (tempoPercorrido - (3600 * horas)) / 60;

    // Calcula os segundos pela diferenca entre o tempo decorrido e as horas e minutos
    segundos = tempoPercorrido - ((3600 * horas) + (minutos * 60));

    // Imprime no arquivo no formato especificado
    fprintf(fp,"%02d:%02d:%0.15lf", horas, minutos, segundos);
}

// Funcao para imprimir a distancia percorrida final
// Entrada: fp - ponteiro para o arquivo de saida
//          distanciaPercorrida - distancia percorrida
// Saida:   void
void imprimeDistancia(FILE* fp, double distanciaPercorrida){
    
    // Conversao para km antes de imprimir
    fprintf(fp, "%.15lf\n", distanciaPercorrida / 1000);
}

// Funcao para imprimir o arquivo de saida completo
// Entrada: fp - ponteiro para o arquivo de saida
//          vetor - vetor de vertices
//          vOrigem - vertice de origem
//          vDestino - vertice de destino
//          tempoDecorrido - tempo decorrido
//          distanciaPercorrida - distancia percorrida
// Saida:   void
void imprimeArquivo(FILE* fp, int* vetor, int vOrigem, int vDestino, double tempoDecorrido, double distanciaPercorrida) {
    // Imprime o menor caminho
    imprimeCaminho(fp, vetor, vOrigem, vDestino);
    
    // Quebra de linha
    fprintf(fp,"\n");

    // Imprime a distancia e o tempo decorrido
    imprimeDistancia(fp, distanciaPercorrida);
    imprimeTempo(fp, tempoDecorrido);
}