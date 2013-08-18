/*
 ============================================================================
 TRABALHO PRÁTICO 2 - Art Gallery Problem
 Algoritmos e Estruturas de Dados III

 Bruno Maciel Peres
 brunomperes@dcc.ufmg.br

 ORDENA.C - Contém funções para ordenação de vetor necessárias para impressão dos vértices cobertos por outro vértice ordenados crescentemente.
 ============================================================================
 */

#include <stdlib.h>

#include "ordena.h"

//Intercalação de dois vetores já ordenados
void merge(int* vet, int p, int q, int r) {
    int i=p, j=q+1, k=0;
    int* B = (int*)malloc((r-p+1) * sizeof (int)); //Aloca um vetor de listas para guardar as ids de preferências de n homens
    if (B == NULL) exit (1); //Finaliza o programa com status de erro
    while(i<=q && j<=r) {
        if(vet[i]<vet[j])
            B[k]=vet[i++];
        else
            B[k]=vet[j++];
        k++;
    }
    while(i<=q) {
        B[k]=vet[i];
        i++,k++;
    }
    while(j<=r) {
        B[k]=vet[j];
        j++,k++;
    }
    for(i=p,k=0; i<=r; i++,k++)
        vet[i]=B[k];
    free(B);
}

//Divisão
void mergeS(int* vet, int p, int r) {
    if(p<r) {
        int q = (p+r)/2; //Define o meio do vetor
        mergeS(vet, p, q);
        mergeS(vet, q+1, r);
        merge(vet, p, q, r);
    }
}

void MergeSort(int* vet, int size) {
    mergeS(vet, 0, size-1);
}
