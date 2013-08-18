/*
 ============================================================================
 TRABALHO PRÁTICO 2 - Art Gallery Problem
 Algoritmos e Estruturas de Dados III

 Bruno Maciel Peres
 brunomperes@dcc.ufmg.br

 POLIGONO.C - Define as funções que operam sobre o TAD grafo.
 ============================================================================
 */

#include <stdlib.h>
#include <stdio.h>

#include "lista.h"
#include "grafo.h"

#include "io.h"

#define SIM 1
#define NAO 0

//O(1)
void InsereAresta(GRAFO * G, int idV1, int idV2) {
    ITEM nova_aresta;

    nova_aresta.id = idV1;
    lista_inserir_fim(G->Vertice[idV2].Adjacentes, &nova_aresta);

    nova_aresta.id = idV2;
    lista_inserir_fim(G->Vertice[idV1].Adjacentes, &nova_aresta);
}

//O(v)
int ExisteAresta(GRAFO* G, int idV1, int idV2) {
    NO* aux;
    aux = lista_busca(G->Vertice[idV1].Adjacentes, idV2);
    if (aux == NULL) return NAO;
    return SIM;
}

//O(v)
void RemoveAresta(GRAFO *G , int idV1, int idV2) {
    lista_remover_por_id(G->Vertice[idV1].Adjacentes, idV2);
    lista_remover_por_id(G->Vertice[idV2].Adjacentes, idV1);
}

void ImprimirGrafo(GRAFO* G) {
    int i;
    if (G->NumVertices < 1) puts ("Grafo Vazio");
    for (i=1; i<=G->NumVertices; i++) {
        printf ("[%d] s=%d: ", i, G->Vertice[i].Adjacentes->tam);
        if (G->Vertice[i].Guarda == SIM) printf ("G ");
        lista_imprimir(G->Vertice[i].Adjacentes);
    }
}

void IniciaPoligono(FILE* ArqEntrada, GRAFO* G) {
    int i;

    //Inicializa o vetor de vértices (listas) com a quantidade de vértices
    G->Vertice = (VERTICE *)malloc((G->NumVertices+1) * sizeof (VERTICE));
    if (G->Vertice == NULL) exit (1); //Finaliza o programa com status de erro

    for (i = 0; i <= G->NumVertices; i++) {
        G->Vertice[i].Adjacentes = (LISTA*)malloc(sizeof (LISTA));
        if (G->Vertice[i].Adjacentes == NULL) exit (1); //Finaliza o programa com status de erro
        lista_criar(G->Vertice[i].Adjacentes);
    }

    //Preenche os campos de VerticeSeguinte e VerticeAnterior
    for (i=1; i <= G->NumVertices; i++) {
        if (i == G->NumVertices) G->Vertice[i].VerticeSeguinte = 1;
        else G->Vertice[i].VerticeSeguinte = i+1;

        if (i == 1) G->Vertice[i].VerticeAnterior = G->NumVertices;
        else G->Vertice[i].VerticeAnterior = i-1;
        G->Vertice[i].Guarda = NAO;
    }

    LeituraVertices(ArqEntrada, G);
}

void MostraVertices(LISTA* Vertice, int NumVertices) {
    int i;
    for (i=1; i<=NumVertices; i++) {
        printf ("[%d] x = %f y = %f\n", i, Vertice[i].x, Vertice[i].y);
        printf ("\n");
    }
    printf ("\n");
}

//Desaloca a memória para as listas de adjacências dos vértices e o vetor de vértices
void LiberaGrafo(GRAFO* G) {
    int i;
    for (i=0; i<=G->NumVertices; i++) {
        lista_apagar(G->Vertice[i].Adjacentes);
        free(G->Vertice[i].Adjacentes);
    }
    free(G->Vertice);
}
