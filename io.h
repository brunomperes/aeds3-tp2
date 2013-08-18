/*
 ============================================================================
 TRABALHO PR�TICO 2 - Art Gallery Problem
 Algoritmos e Estruturas de Dados III

 Bruno Maciel Peres
 brunomperes@dcc.ufmg.br

 IO.H - Cont�m o cabe�alho das fun��es de entrada e sa�da.
 ============================================================================
 */

#ifndef IO_H_INCLUDED
#define IO_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>

#include "lista.h"
#include "grafo.h"


//Verifica se os par�metros com o nome do arquivo de entrada e sa�da foram passados corretamente
//Retorna 1 caso falte algum par�metro essencial, 0 caso o programa possa continuar execu��o
int checaEntrada(int argc, char **argv, char *NomeArqEntrada, char *NomeArqSaida, int *Analise);

//Limpa o conte�do de um arquivo
void LimpaArquivo(char *NomeArqSaida);

//L� um n�mero inteiro de um arquivo aberto como leitura
int LeInt(FILE *ArqEntrada);

//L� e armazena as coordenadas dos v�rtices do pol�gono/grafo
void LeituraVertices(FILE* ArqEntrada, GRAFO* G);

//Escreve o n�mero da heur�stica num arquivo
void EscreveNumHeuristica(FILE *ArqSaida, int x);

//Escreve no arquivo de sa�da o resultado a quantidade de guardas e os v�rtices que cada um desses guardas cobre
void EscreveResultados(FILE *ArqSaida, GRAFO* G, int QntGuardas);

//Escreve o resultado das an�lise de execu��o das heur�sticas
void EscreveDadosAnalise(FILE *ArqAnaliseRes, double tempogasto, int qntvertices, int qntguardas);

#endif // IO_H_INCLUDED
