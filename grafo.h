/*
 ============================================================================
 TRABALHO PRÁTICO 2 - Art Gallery Problem
 Algoritmos e Estruturas de Dados III

 Bruno Maciel Peres
 brunomperes@dcc.ufmg.br

 POLIGONO.C - Define a estrutura do TAD e as funções que operam sobre o TAD grafo.
 ============================================================================
 */

#ifndef GRAFO_H_INCLUDED
#define GRAFO_H_INCLUDED

#include <stdio.h> //FILE*

#include "lista.h"

typedef struct {
    float x, y;
} COORDENADA;

typedef struct {
    int VerticeAnterior; //Vértice originalmente anterior ao vértice no polígono
    int VerticeSeguinte; //Vértice originalmente após ao vértice no polígono
    int Cor;
    int Guarda; //Indica se há um guarda nesse vértice
    COORDENADA coord;
    LISTA* Adjacentes;
} VERTICE;

typedef struct {
    int NumVertices;
    VERTICE *Vertice;
} GRAFO;

//Insere uma aresta entre os vértices de idV1 e idV2 (nas listas de ambos) em O(1)
void InsereAresta(GRAFO * G, int idV1, int idV2);

//Retorna se exste aresta entre o vértice idV1 e idV2
int ExisteAresta(GRAFO* G, int idV1, int idV2);

//Preenche os campos de VerticeSeguinte e VerticeAnterior de todos os vértices e aloca as listas de adjacências de cada vértice
void IniciaPoligono(FILE *ArqEntrada, GRAFO* G);

//O(v)
void RemoveAresta(GRAFO *G , int idV1, int idV2);

void LiberaGrafo(GRAFO* G);

void ImprimirGrafo(GRAFO* G);

void ImprimirArestas(LISTA* Vertice, int NumVertices);

#endif // GRAFO_H_INCLUDED
