/*
 ============================================================================
 TRABALHO PRÁTICO 2 - Art Gallery Problem
 Algoritmos e Estruturas de Dados III

 Bruno Maciel Peres
 brunomperes@dcc.ufmg.br

 HEURISTICA2.C - Define o cabeçalho da função de execução da heurística 2.
 ============================================================================
 */

#ifndef HEURISTICA2_H_INCLUDED
#define HEURISTICA2_H_INCLUDED

#include "grafo.h"

/*#####################################################################################################################################
#   Definição: Marca no grafo os vértices que deverão possuir um guarda, através da cobertura de vértices
#   Retorno: Quantidade de guardas necessários por essa heurística
#   Complexidade: O(v³)
#####################################################################################################################################*/
int heuristica2(GRAFO* G);

#endif // HEURISTICA2_H_INCLUDED
