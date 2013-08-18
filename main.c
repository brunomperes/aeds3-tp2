/*
 ============================================================================
 TRABALHO PRÁTICO 2 - Art Gallery Problem
 Algoritmos e Estruturas de Dados III

 Bruno Maciel Peres
 brunomperes@dcc.ufmg.br

 MAIN.C - Arquivo principal do programa, contém as chamadas de funções de entrada e saída e a chamada de execução das heurísticas.
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#include "heuristica1.h"
#include "heuristica2.h"
#include "io.h"
#include "timerlinux.h"
#include "poligono.h"
#include "lista.h"

#include "tempo.h"

#define SIM 1
#define NAO 0
#define TAMMAXNOMEARQ 256

//Limpa o status modificado por uma heurística para execução da próxima
void LimpaStatus(GRAFO* G, int *QntGuardas) {
    int i;
    ITEM recupera;
    for (i=1; i<=G->NumVertices; i++) {
        G->Vertice[i].Guarda = NAO;
        G->Vertice[i].Cor = 0;
        while (G->Vertice[i].Adjacentes->tam > 2) {
            lista_apagar(G->Vertice[i].Adjacentes);
            recupera.id = G->Vertice[i].VerticeSeguinte;
            lista_inserir_inicio(G->Vertice[i].Adjacentes, &recupera);
            recupera.id = G->Vertice[i].VerticeAnterior;
            lista_inserir_inicio(G->Vertice[i].Adjacentes, &recupera);
        }
    }
    *QntGuardas = 0;
}

int main(int argc, char **argv) {

    char NomeArqEntrada[TAMMAXNOMEARQ];
    char NomeArqSaida[TAMMAXNOMEARQ];

    int Analise;
    char *NomeArqAnaliseHeur1 = "resultadosheur1.dat";
    char *NomeArqAnaliseHeur2 = "resultadosheur2.dat";
    stopWatch cronometro;
    double tempogasto;

    int j;
    int instancias, QntGuardas;

    if (checaEntrada(argc, argv, NomeArqEntrada, NomeArqSaida, &Analise) != 0) {
        puts ("\n[ERRO] Verifique se os parâmetros de nome de arquivo de entrada e de saída foram passados corretamente!\n");
        exit(1);
    }

    //Manter um arquivo aberto para evitar ter que percorrer todo o arquivo cada vez que precisar de um dado específico
    FILE *ArqEntrada = fopen(NomeArqEntrada, "r");
    if (ArqEntrada == NULL) {
        printf("\n[ERRO] Problema ao abrir o arquivo de entrada\nVerifique se o arquivo passado como argumento realmente existe\n\n");
        exit(1); //Finaliza o programa com status de erro
    }

    FILE *ArqSaida = fopen (NomeArqSaida,"w");
    FILE *ArqAnaliseHeur1 = fopen (NomeArqAnaliseHeur1,"a");
    FILE *ArqAnaliseHeur2 = fopen (NomeArqAnaliseHeur2,"a");

    instancias = LeInt(ArqEntrada);

    for (j=0; j<instancias; j++) {

        GRAFO Banco;
        Banco.NumVertices = LeInt(ArqEntrada);

        //Criar vetor de listas alocadas dinamicamente que representa os vértices, preenchendo os VerticeSeguinte e VerticeAnterior, as coordenadas de cada vértice e os valores default (Cor e Guarda)
        IniciaPoligono(ArqEntrada, &Banco);

        //Heurística 1
        if (Analise == SIM) startTimer(&cronometro);
        QntGuardas = heuristica1(&Banco);
        if (Analise == SIM) stopTimer(&cronometro);
        if (Analise == SIM) tempogasto = getElapsedTime(&cronometro);

        //Escreve os resultados no arquivo
        EscreveNumHeuristica(ArqSaida, 1);
        EscreveResultados(ArqSaida, &Banco, QntGuardas);
        if (Analise == SIM) EscreveDadosAnalise(ArqAnaliseHeur1, tempogasto, Banco.NumVertices, QntGuardas);

        //Limpar os status modificados pela heurística 1
        LimpaStatus(&Banco, &QntGuardas);

        //Heurística 2
        if (Analise == SIM) startTimer(&cronometro);
        QntGuardas = heuristica2(&Banco);
        if (Analise == SIM) stopTimer(&cronometro);
        if (Analise == SIM) tempogasto = getElapsedTime(&cronometro);

        //Escreve os resultados no arquivo
        EscreveNumHeuristica(ArqSaida, 2);
        EscreveResultados(ArqSaida, &Banco, QntGuardas);
        if (Analise == SIM) EscreveDadosAnalise(ArqAnaliseHeur2, tempogasto, Banco.NumVertices, QntGuardas);

        //Libera a memória alocada para o grafo
        LiberaGrafo(&Banco);

    }

    fclose(ArqEntrada);
    fclose(ArqSaida);
    if (Analise == SIM)fclose(ArqAnaliseHeur1);
    if (Analise == SIM)fclose(ArqAnaliseHeur2);

    return 0;
}
