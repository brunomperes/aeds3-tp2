/*
 ============================================================================
 TRABALHO PRÁTICO 2 - Art Gallery Problem
 Algoritmos e Estruturas de Dados III

 Bruno Maciel Peres
 brunomperes@dcc.ufmg.br

 HEURISTICA1.C - Define o cabeçalho da função de execução da heurística 1.
 ============================================================================
 */

#ifndef HEURISTICA_H_INCLUDED
#define HEURISTICA_H_INCLUDED

#include "grafo.h"
#include "poligono.h"

/*#####################################################################################################################################
#   Definição: Marca no grafo os vértices que deverão possuir um guarda, através da triangularização e 3-coloração do grafo/polígono
#   Retorno: Quantidade de guardas necessários por essa heurística
#   Complexidade: O(v³)
#####################################################################################################################################*/
int heuristica1(GRAFO* G);

#endif // HEURISTICA_H_INCLUDED
