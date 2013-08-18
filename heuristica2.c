/*
 ============================================================================
 TRABALHO PRÁTICO 2 - Art Gallery Problem
 Algoritmos e Estruturas de Dados III

 Bruno Maciel Peres
 brunomperes@dcc.ufmg.br

 HEURISTICA2.C - Define o funcionamento da heurística 2.
 ============================================================================
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "heuristica2.h"
#include "grafo.h"
#include "io.h"
#include "poligono.h"

#define SIM 1
#define NAO 0
#define AZUL 1

//Calcula a visibilidade de todos os vértices do polígono em O(V³)
void setVertexesVision(GRAFO *G) {
    int i;
    for (i = 1; i <= G->NumVertices; i++) {
        CalculaVisibilidadeGenerica(G, i); //O(v²)
    }
}

//Retorna o vetor de maior grau
int Maximo(VERTICE vet[], int size) {
    int minpos=1;//Guarda a posição do menor elemento
    int i;
    for (i=1; i<=size; i++) {
        if (vet[i].Adjacentes->tam > vet[minpos].Adjacentes->tam)
            minpos = i;
    }
    return minpos;
}

//Remove das listas de adjacência todos os vértices já cobertos
void LimpaVerticesCobertos(GRAFO* G) {
    int i;
    NO* cursor;
    NO* aux;
    for (i=1; i<=G->NumVertices; i++) {
        cursor = G->Vertice[i].Adjacentes->inicio;
        while (cursor != NULL) { //Percorre todos os nós da lista
            if (G->Vertice[cursor->item.id].Cor != 0) { //À procura de um vértice já colorido
                aux = cursor;
                cursor = cursor->proximo;
                aux = lista_remover_por_no(G->Vertice[i].Adjacentes, aux);
                free(aux);
            } else cursor = cursor->proximo;
        }
    }
}

//Nenhum vértice terá menos que 2 arestas
int heuristica2(GRAFO* G) {
    int QntGuardas = 0, i;
    int idVertMaiorGrau, idVertCoberto;
    int QntVerticesCobertos = 0;
    ITEM arestas_originais;

    setVertexesVision(G); //O(v³)

    while (QntVerticesCobertos < G->NumVertices) { //O(v³)
        //Remove todos os adjacentes ao vertice de maior grau e coloca um guarda nesse vértice
        idVertMaiorGrau = Maximo(G->Vertice, G->NumVertices); //O(v)
        G->Vertice[idVertMaiorGrau].Guarda = SIM;
        QntGuardas++;
        if (G->Vertice[idVertMaiorGrau].Cor == 0) { //Marca o vértice com guarda como coberto
            G->Vertice[idVertMaiorGrau].Cor = AZUL;
            QntVerticesCobertos++;
        }

        while (!lista_vazia(G->Vertice[idVertMaiorGrau].Adjacentes)) {
            idVertCoberto = G->Vertice[idVertMaiorGrau].Adjacentes->fim->item.id;
            lista_remover_fim(G->Vertice[idVertMaiorGrau].Adjacentes);
            if (G->Vertice[idVertCoberto].Cor == 0) { //Caso o vértice não esteja colorido/coberto
                G->Vertice[idVertCoberto].Cor = AZUL;
                QntVerticesCobertos++;
            }
        }

        LimpaVerticesCobertos(G); //Remove os vértices cobertos da lista de todos os outros vértices em O(v²)
    }

    for (i=1; i<=G->NumVertices; i++) { //O(v³)
        if (G->Vertice[i].Guarda == SIM) {

            arestas_originais.id = G->Vertice[i].VerticeSeguinte;
            lista_inserir_inicio(G->Vertice[i].Adjacentes, &arestas_originais);

            arestas_originais.id = G->Vertice[i].VerticeAnterior;
            lista_inserir_inicio(G->Vertice[i].Adjacentes, &arestas_originais);

            CalculaVisibilidadeGenerica(G, i); //Recalcula a visibilidade do vértice i. O(v²)

            lista_ordenar(G->Vertice[i].Adjacentes); //O(vlogv)
        }
    }

    return QntGuardas;
}
