/*
 ============================================================================
 TRABALHO PRÁTICO 2 - Art Gallery Problem
 Algoritmos e Estruturas de Dados III

 Bruno Maciel Peres
 brunomperes@dcc.ufmg.br

 POLIGONO.C - Contém funções comuns à operações sobre polígonos.
 ============================================================================
 */

#include <stdlib.h>

#include "poligono.h"
#include "grafo.h"
#include "io.h"

#define FALSE 0
#define TRUE 1
#define CW -1
#define CCW +1

//Retorna se, a partir do primeiro ponto até o 3º, gira-se no sentido horário ou anti-horário
/*
                {  1 if the turn from p0 to p1 to p2 is counter-clockwise.
                { -1 if the turn from p0 to p1 to p2 is clockwise.
ccw(p0,p1,p2) = { -1 if the points are collinear and p0 is in the middle.
                {  1 if the points are collinear and p1 is in the middle.
                {  0 if the points are collinear and p2 is in the middle.
                */
int ccw(COORDENADA p0, COORDENADA p1, COORDENADA p2) {
    float dx1, dx2, dy1,dy2;
    dx1 = p1.x - p0.x;
    dy1 = p1.y - p0.y;
    dx2 = p2.x - p0.x;
    dy2 = p2.y - p0.y;
    if (dx1*dy2 > dy1*dx2) return CCW;
    if (dx1*dy2 < dy1*dx2) return CW;
    if ((dx1*dx2 < 0) || (dy1*dy2 < 0)) return CW;
    if ((dx1*dx1+dy1*dy1) < (dx2*dx2+dy2*dy2)) return CCW;
    return 0;
}

//Calcula a visibilidade de um veŕtice i genérico, incluindo a visibilidade do próprio vértice. O(v²)
//Supõe que as arestas adjacentes já estão inseridas na lista
void CalculaVisibilidadeGenerica(GRAFO* G, int i) {
    int j;
    ITEM nova_aresta;
    for (j=1; j<=G->NumVertices; j++) {
        if (i == G->Vertice[i].VerticeSeguinte || i == G->Vertice[i].VerticeAnterior) continue;
        if ( i == j) {
            nova_aresta.id = i; //Insere o vértice que cobre o próprio vértice na lista
            lista_inserir_fim(G->Vertice[i].Adjacentes, &nova_aresta);
            continue;
        }
        if(!ExisteAresta(G, i,j) && eVisivel(G, i, j)) { //Testa a visibilidade do vértice 'i' com todos os vértices 'j' //O(v) e O(v²)
            nova_aresta.id = i;
            lista_inserir_fim(G->Vertice[j].Adjacentes, &nova_aresta);
            nova_aresta.id = j;
            lista_inserir_fim(G->Vertice[i].Adjacentes, &nova_aresta);
        }
    }
}

short mesmoPonto(COORDENADA p0, COORDENADA p1) { //O(1)
    return ((p0.x == p1.x) && (p0.y == p1.y));
}
short pontoEmComum(LINHA l1, LINHA l2) { //O(1)
    return ( (mesmoPonto(l1.p1, l2.p1)) || (mesmoPonto(l1.p1, l2.p2)) ||
             (mesmoPonto(l1.p2, l2.p1)) || (mesmoPonto(l1.p2, l2.p2)) );
}
short interceptaLinha(LINHA l1, LINHA l2) { //O(1)
    return ( ((ccw(l1.p1, l1.p2, l2.p1) * ccw(l1.p1, l1.p2, l2.p2)) <= 0) &&
             ((ccw(l2.p1, l2.p2, l1.p1) * ccw(l2.p1, l2.p2, l1.p2)) <= 0) && !pontoEmComum(l1, l2) );
}
short isInside(COORDENADA p0, COORDENADA p1, COORDENADA p2) { //O(1)
    return ((p1.x*p2.y + p0.x*p1.y + p0.y*p2.x - p0.y*p1.x - p1.y*p2.x - p0.x*p2.y) > 0);
}

void setLine(LINHA* linha, COORDENADA p1, COORDENADA p2) { //O(1)
    linha->p1 = p1;
    linha->p2 = p2;
}

short isVertically(COORDENADA p0, COORDENADA p1, COORDENADA p2) { //O(1)
    return ( ((p0.y > p1.y) && (p2.y < p1.y)) || ((p0.y < p1.y) && (p2.y > p0.y)) );
}

short collinear(COORDENADA p0, COORDENADA p1) { //O(1)
    return ((p0.y == p1.y) && (p0.x > p1.x));
}

//Recebe o ponto médio da reta que está sendo testada
//O(v)
short dentro(GRAFO *graph, COORDENADA ponto) {
    int count = 0;
    int n;
    COORDENADA maxPoint;
    COORDENADA p0, p1, p2;
    LINHA testLine, edgeLine;

    maxPoint.x = -1;
    maxPoint.y = ponto.y;
    setLine(&testLine, ponto, maxPoint);


    for (n = 1; n <= graph->NumVertices; n++) {

        p1 = graph->Vertice[n].coord;
        p2 = graph->Vertice[graph->Vertice[n].VerticeSeguinte].coord;
        p0 = graph->Vertice[graph->Vertice[n].VerticeAnterior].coord;

        setLine(&edgeLine, p1, p2);

        if (interceptaLinha(testLine, edgeLine) || collinear(ponto, edgeLine.p1) || collinear(ponto, edgeLine.p2)) {
            if (maxPoint.y != edgeLine.p1.y) {
                count++;
            } else if (!isVertically(p0, p1, p2)) {
                count++;
            }
        }
    }

    //Caso a quantidade de interceptações seja par, quer dizer que a linha saiu e entrou no polígono
    return !(count % 2 == 0);
}

//O(v²)
short interceptaPoligono(GRAFO* G, LINHA line1) {
    short flag=0;
    int k;
    LINHA line2;
    for (k = 1; k <= G->NumVertices; k++) { //Faz todas as possibilidade de linha entre os pontos do polígono para verificar se a linha de visão intercepta alguma delas
        line2.p1 = G->Vertice[G->Vertice[k].VerticeAnterior].coord;
        line2.p2 = G->Vertice[k].coord;
        if (interceptaLinha(line1, line2)) {
            flag = 1; //Retorna que intercepta outra aresta do polígono
            return flag;
        }

    }
    return flag;
}

//Verifica se um vertice é visível para outro vértice em O(v²)
short eVisivel(GRAFO *poligono, int idOrigem, int idTestada) {
    LINHA linha;
    COORDENADA ponto;

    if ((idTestada == poligono->Vertice[idOrigem].VerticeAnterior) || (idTestada == poligono->Vertice[idOrigem].VerticeSeguinte) || idOrigem == idTestada) { //Verifica se o vértice já é adjacente
        return FALSE;
    }

    setLine(&linha, poligono->Vertice[idOrigem].coord, poligono->Vertice[idTestada].coord);

    ponto.x = (linha.p1.x + linha.p2.x)/2;
    ponto.y = (linha.p1.y + linha.p2.y)/2;

    return (!interceptaPoligono(poligono, linha) && dentro(poligono, ponto)); //O(v²) e O(v)
}
