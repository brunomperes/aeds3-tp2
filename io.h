/*
 ============================================================================
 TRABALHO PRÁTICO 2 - Art Gallery Problem
 Algoritmos e Estruturas de Dados III

 Bruno Maciel Peres
 brunomperes@dcc.ufmg.br

 IO.H - Contém o cabeçalho das funções de entrada e saída.
 ============================================================================
 */

#ifndef IO_H_INCLUDED
#define IO_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>

#include "lista.h"
#include "grafo.h"


//Verifica se os parâmetros com o nome do arquivo de entrada e saída foram passados corretamente
//Retorna 1 caso falte algum parâmetro essencial, 0 caso o programa possa continuar execução
int checaEntrada(int argc, char **argv, char *NomeArqEntrada, char *NomeArqSaida, int *Analise);

//Limpa o conteúdo de um arquivo
void LimpaArquivo(char *NomeArqSaida);

//Lê um número inteiro de um arquivo aberto como leitura
int LeInt(FILE *ArqEntrada);

//Lê e armazena as coordenadas dos vértices do polígono/grafo
void LeituraVertices(FILE* ArqEntrada, GRAFO* G);

//Escreve o número da heurística num arquivo
void EscreveNumHeuristica(FILE *ArqSaida, int x);

//Escreve no arquivo de saída o resultado a quantidade de guardas e os vértices que cada um desses guardas cobre
void EscreveResultados(FILE *ArqSaida, GRAFO* G, int QntGuardas);

//Escreve o resultado das análise de execução das heurísticas
void EscreveDadosAnalise(FILE *ArqAnaliseRes, double tempogasto, int qntvertices, int qntguardas);

#endif // IO_H_INCLUDED
