/*
 ============================================================================
 TRABALHO PRÁTICO 2 - Art Gallery Problem
 Algoritmos e Estruturas de Dados III

 Bruno Maciel Peres
 brunomperes@dcc.ufmg.br

 HEURISTICA1.C - Define o funcionamento da heurística 1.
 ============================================================================
 */

#include <stdlib.h>
#include <stdio.h>

#include "heuristica1.h"
#include "grafo.h"
#include "poligono.h"
#include "io.h"

#define SIM 1
#define NAO 0
#define CW -1
#define CCW +1
#define FALSE 0
#define TRUE 1
#define AZUL 1
#define VERDE 2
#define BRANCO 3

void MostraTriangulos(TRIANGULO triangulos[], int qnt) {
    int i;
    for (i=0; i<qnt; i++) {
        printf ("triangulo[%d]: %d - %d - %d\n", i, triangulos[i].id[0],triangulos[i].id[1], triangulos[i].id[2]);
    }
}

void MostraCores(GRAFO* G) {
    int i;
    for (i=1; i<=G->NumVertices; i++) {
        printf ("%d: cor = %d\n", i, G->Vertice[i].Cor);
    }
}

int point_in_triangle(COORDENADA p, TRIANGULO t[]) {
    int i;    /* counter */
    for (i=0; i<3; i++)
        if (ccw(t->ponto[i],t->ponto[(i+1)%3], p) == CW) return(FALSE);
    return(TRUE);
}
//Retorna TRUE caso essa combinação de pontos possa ser um triangulo, verificando se há algum ponto dentro desse triangulo e se estão em sentido horário
int ear_Q(int i, int j, int k, GRAFO* G) { //O(v)
    //Recebe a id de tres vertices e o poligono

    TRIANGULO t;    /* coordinates for points i,j,k */
    int m;    /* counter */

    //Copia as coordenadas dos tres pontos para o triangulo t
    t.ponto[0].x = G->Vertice[i].coord.x;
    t.ponto[0].y = G->Vertice[i].coord.y;
    t.ponto[1].x = G->Vertice[j].coord.x;
    t.ponto[1].y = G->Vertice[j].coord.y;
    t.ponto[2].x = G->Vertice[k].coord.x;
    t.ponto[2].y = G->Vertice[k].coord.y;

    if (ccw(t.ponto[0],t.ponto[1],t.ponto[2]) != CCW) return(FALSE); //Verifica se estão em sentido horário

    //Testa se existe algum ponto dentro do triangulo i,j,k
    for (m=1; m<=G->NumVertices; m++) {
        if ((m!=i) && (m!=j) && (m!=k))
            if (point_in_triangle(G->Vertice[m].coord, &t)) return(FALSE);
    }
    return(TRUE);
}
//Retorna o vetor de triangulos //O(v³)
void triangulacao(GRAFO* G, TRIANGULO triangulos[]) {

    int i;
    int qnttriangularizados = 0;
    int *l, *r;    /* left/right neighbor indices */

    l = (int *)malloc((G->NumVertices+1) * sizeof (int));
    r = (int *)malloc((G->NumVertices+1) * sizeof (int));

    for (i=1; i<=G->NumVertices; i++) {
        l[i] = G->Vertice[i].VerticeAnterior;
        r[i] = G->Vertice[i].VerticeSeguinte;
    }

    i = G->NumVertices;
    int cont = 0;
    while (qnttriangularizados < (G->NumVertices - 2)) { //Cada polígono de n lados possui n-2 triangulos após a triangulação (propriedade) //O(v)
        i = r[i];
        if (ear_Q(l[i],i,r[i],G)) { //O(v)

            if (!ExisteAresta(G, r[i],l[i])) //O(v)
                InsereAresta(G, r[i], l[i]);

            //Adiciona os três pontos ao vetor de triangulos do polígono
            triangulos[cont].id[0] = l[i];
            triangulos[cont].id[1] = i;
            triangulos[cont].id[2] = r[i];
            cont++;

            l[ r[i] ] = l[i];
            r[ l[i] ] = r[i];
            qnttriangularizados++;
        }
    }

    free(l);
    free(r);
}

//Colore 3 vértices que interligados (formam um triângulo de um grafo com 3 cores distintas)
//O(1)
int ColoreTrianguloCorRestante(GRAFO* G, TRIANGULO t) {
    int idVertNaoColorido, i;
    int azul=0, verde=0, branco=0; //Status de cores em uso, 0 para não utilizada, 1 para já utilizada

    //Encontra vértice não colorido e identifica quais cores já foram utilizadas no triangulo
    for (i=0; i<3; i++) {
        if (G->Vertice[t.id[i]].Cor != 0) { //Caso o vértice esteja colorido, descobre qual cores já estão em uso
            if (G->Vertice[t.id[i]].Cor == BRANCO)
                branco = 1;//Indica que já existe um vértice branco
            else if (G->Vertice[t.id[i]].Cor == VERDE)
                verde = 1;//Indica que já existe um vértice verde
            else if (G->Vertice[t.id[i]].Cor == AZUL)
                azul = 1;//Indica que já existe um vértice azul
        } else idVertNaoColorido = t.id[i]; //Encontrou vértice não colorido
    }

    if (azul == 0) {
        G->Vertice[idVertNaoColorido].Cor = AZUL;
        return AZUL;
    } else if (branco == 0) {
        G->Vertice[idVertNaoColorido].Cor = BRANCO;
        return BRANCO;
    } else if (verde == 0) {
        G->Vertice[idVertNaoColorido].Cor = VERDE;
        return VERDE;
    }

    return -1;

}
//Retorna a id de triângulo com apenas dois vértices coloridos
//O(v)
int BuscaTriangulo2Colorido(GRAFO* G, TRIANGULO t[]) {
    int i=0;
    for (i=0; i<G->NumVertices-2; i++) {
        //Testa as 3 possibilidades de ter apenas dois vétrices coloridos
        if (((G->Vertice[t[i].id[0]].Cor == 0) && (G->Vertice[t[i].id[1]].Cor != 0)) && (G->Vertice[t[i].id[2]].Cor != 0))
            return i;
        if (((G->Vertice[t[i].id[0]].Cor != 0) && (G->Vertice[t[i].id[1]].Cor == 0)) && (G->Vertice[t[i].id[2]].Cor != 0))
            return i;
        if (((G->Vertice[t[i].id[0]].Cor != 0) && (G->Vertice[t[i].id[1]].Cor != 0)) && (G->Vertice[t[i].id[2]].Cor == 0))
            return i;
    }
    return -1;
}
//O(v²)
int coloracao3(GRAFO *G, TRIANGULO triangulos[]) {
    int i, qntverde=0, qntazul=0, qntbranco=0;
    int menorqntcores, CorMenosUsada, id;
    int corAux;

    //Reseta a coloração de todos os vértices
    for (i=1; i<=G->NumVertices; i++) {
        G->Vertice[i].Cor = 0;
    }

    //Colore triangulo inicial, que sempre é formado pelo primeiro vértice, segundo e último.
    G->Vertice[triangulos[0].id[0]].Cor = BRANCO;
    qntbranco++;
    G->Vertice[triangulos[0].id[1]].Cor = VERDE;
    qntverde++;
    G->Vertice[triangulos[0].id[2]].Cor = AZUL;
    qntazul++;

    for (i=1; i<=G->NumVertices-2; i++) {
        id = BuscaTriangulo2Colorido(G, triangulos);  //Procura triangulo com apenas 2 vertices coloridos
        if (id != -1) {
            corAux = ColoreTrianguloCorRestante(G, triangulos[id]);//colore ponto com cor restante
            switch (corAux) {
            case AZUL:
                qntazul++;
                break;
            case BRANCO:
                qntbranco++;
                break;
            case VERDE:
                qntverde++;
                break;
            }
        } else break; // Caso não hajam mais triangulos para serem coloridos
    }

    //Decide qual a cor menos utilizada
    menorqntcores = qntverde;
    CorMenosUsada = VERDE;
    if (qntazul < menorqntcores) {
        menorqntcores = qntazul;
        CorMenosUsada = AZUL;
    }
    if (qntbranco < menorqntcores) {
        menorqntcores = qntbranco;
        CorMenosUsada = BRANCO;
    }

    return CorMenosUsada;
}

//O(v³)
int heuristica1(GRAFO* G) {

    int i=1;
    int CorMenosUsada, QntGuardas=0;

    TRIANGULO triangulos[G->NumVertices-2]; //Triângulos contidos no polígono
    triangulacao(G, triangulos); //O(v³)

    CorMenosUsada = coloracao3(G, triangulos); //O(v²)

    for (i=1; i<=G->NumVertices; i++) {
        if (G->Vertice[i].Cor == CorMenosUsada) {
            CalculaVisibilidadeGenerica(G, i); //O(v²)

            lista_ordenar(G->Vertice[i].Adjacentes); //O(vlogv)

            G->Vertice[i].Guarda = SIM;
            QntGuardas++;
        }
    }

    return QntGuardas;
}
