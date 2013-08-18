/*
 ============================================================================
 TRABALHO PR�TICO 2 - Art Gallery Problem
 Algoritmos e Estruturas de Dados III

 Bruno Maciel Peres
 brunomperes@dcc.ufmg.br

 IO.C - Realiza a comunica��o do programa com o ambiente, lendo o arquivo de entrada e armazenamento das informa��es lidas e escrevendo os resultados.
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //getopt()
#include <string.h> //strncpy()

#include "io.h"
#include "lista.h"
#include "grafo.h"

#define TAMMAXNOMEARQ 256
#define CLOCKWISE -1
#define COUNTERCLOCKWISE +1
#define SIM 1
#define NAO 0

//Limpa o conte�do de um arquivo
void LimpaArquivo(char *NomeArqSaida) {
    FILE * ArqSaida = fopen (NomeArqSaida,"w");
    fclose (ArqSaida);
}

//Preenche os par�metros necess�rios � execu��o do programa
int checaEntrada(int argc, char **argv, char *NomeArqEntrada, char *NomeArqSaida, int *Analise) {

    int opcao, checkInput=0, checkOutput=0;

    *Analise = 0;

    char *temp1 = NULL;
    char *temp2 = NULL;

    strncpy(NomeArqEntrada, " ", 2);
    strncpy(NomeArqSaida, " ", 2);

    while( (opcao = getopt(argc, argv, "i:o:a")) != -1 ) {
        switch( opcao ) {
        case 'i':
            checkInput=1 ;
            temp1 = optarg ;
            break ;
        case 'o':
            checkOutput=1 ;
            temp2 = optarg ;
            break ;
        case 'a':
            *Analise=1;
            break ;
        case '?':
            break ;
        default :
            return 1;
        }
    }

    //Verifica se os par�metros necess�rios foram preenchidos
    if (checkInput == 0 || NomeArqEntrada == NULL) return(1);
    if (checkOutput == 0 || NomeArqSaida == NULL) return(1);

    strncpy(NomeArqEntrada, temp1, TAMMAXNOMEARQ);
    strncpy(NomeArqSaida, temp2, TAMMAXNOMEARQ);

    return 0;
}

//Retorna o pr�ximo n�mero inteiro de um arquivo aberto como leitura
int LeInt(FILE *ArqEntrada) {
    int x;
    fscanf(ArqEntrada, "%d", &x);
    return x;
}

//Faz a leitura das ids de prefer�ncia dos alunos e insere os valores default
void LeituraVertices(FILE* ArqEntrada, GRAFO* G) {

    int i=1;
    int x1, x2, y1, y2;

    ITEM proxVertice; //V�rtice de destino da aresta
    ITEM antVertice; //V�rtice de destino da aresta

    for (i=1; i<=G->NumVertices; i++) {

        fscanf(ArqEntrada, "%d", &x1);
        fgetc(ArqEntrada);
        fscanf(ArqEntrada, "%d", &x2);
        fgetc(ArqEntrada);

        fscanf(ArqEntrada, "%d", &y1);
        fgetc(ArqEntrada);
        fscanf(ArqEntrada, "%d", &y2);
        fgetc(ArqEntrada);

        G->Vertice[i].coord.x = x1/x2;
        G->Vertice[i].coord.y = y1/y2;

        if (i == G->NumVertices) proxVertice.id = 1;
        else proxVertice.id = i+1;

        if (i == 1) antVertice.id = G->NumVertices;
        else antVertice.id = i-1;

        lista_inserir_fim(G->Vertice[i].Adjacentes, &antVertice);
        lista_inserir_fim(G->Vertice[i].Adjacentes, &proxVertice);
    }
}

void EscreveNumHeuristica(FILE *ArqSaida, int x) {
    fprintf(ArqSaida, "#Heuristica%d:\n",x);
}

//Escreve no arquivo de sa�da o resultado de aloca��o e as m�tricas j� calculadas
void EscreveResultados(FILE *ArqSaida, GRAFO* G, int QntGuardas) {

    int i=1;
    NO* cursor;
    LISTA* listaAux;

    fprintf(ArqSaida, "%d\n", QntGuardas);
    for (i=1; i<=G->NumVertices; i++) {
        if (G->Vertice[i].Guarda == SIM) {
            fprintf(ArqSaida, "%d: ", i);
            listaAux = G->Vertice[i].Adjacentes;
            cursor = listaAux->inicio;
            while (cursor != NULL) {
                fprintf (ArqSaida, "%d ", cursor->item.id);
                cursor = cursor->proximo;
            }
            fprintf(ArqSaida, "\n");
        }
    }
}

//Escreve as coordenadas do pol�gono num arquivo para plotar o pol�gono
void EscreveCoordenadas(FILE* ArqSaida, GRAFO* Banco) {
    int i;
    for (i=1; i<=Banco->NumVertices; i++) {
        fprintf(ArqSaida, "%f\t%f\n", Banco->Vertice[i].coord.x, Banco->Vertice[i].coord.y);
    }
    fprintf(ArqSaida, "%f\t%f\n", Banco->Vertice[1].coord.x, Banco->Vertice[1].coord.y);
}

//Escreve o resultado das an�lise de execu��o das heur�sticas
void EscreveDadosAnalise(FILE *ArqAnaliseRes, double tempogasto, int qntvertices, int qntguardas) {

    fprintf(ArqAnaliseRes, "%d\t &%lf\t &%d\t", qntvertices, tempogasto, qntguardas);
    fprintf(ArqAnaliseRes, "\\\\ \\hline\n");
}
