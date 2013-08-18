/*
 ============================================================================
 TRABALHO PRÁTICO 2 - Art Gallery Problem
 Algoritmos e Estruturas de Dados III

 Bruno Maciel Peres
 brunomperes@dcc.ufmg.br

 POLIGONO.C - Contém o cabeçalho das funções para operações comuns em polígonos e define estruturas básicas, como ponto, linha e triângulo.
 ============================================================================
 */

#ifndef POLIGONO_H_INCLUDED
#define POLIGONO_H_INCLUDED

#include "grafo.h"

typedef struct {
    COORDENADA ponto[3];
    int id[3];
} TRIANGULO;
typedef struct {
    COORDENADA p1;
    COORDENADA p2;
} LINHA;

//Calcula a visibilidade de um vértice genérico O(v²)
void CalculaVisibilidadeGenerica(GRAFO* G, int i);

//Retorna se 3 pontos estão em sentido horário ou anti-horário
int ccw(COORDENADA p0, COORDENADA p1, COORDENADA p2);

//O(v²)
short eVisivel(GRAFO *poligono, int idOrigem, int idTestada);

#endif // POLIGONO_H_INCLUDED
