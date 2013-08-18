/*
 ============================================================================
 TRABALHO PRÁTICO 2 - Art Gallery Problem
 Algoritmos e Estruturas de Dados III

 Bruno Maciel Peres
 brunomperes@dcc.ufmg.br

 LISTA.C - Define as funções que operam sobre o TAD lista criado.
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#include "lista.h"
#include "ordena.h"

#define SIM 1
#define NAO 0

//Cria uma lista vazia em O(1)
void lista_criar(LISTA *lista) {
    lista->inicio = NULL;
    lista->tam = 0;
    lista->fim = NULL;
}

//Verifica se uma lista está vazia em O(1)
int lista_vazia(LISTA *lista) {
    if (lista->inicio == NULL && lista->fim==NULL) return SIM;
    else return NAO;
}

//Apaga uma lista em O(n)
void lista_apagar(LISTA *lista) {
    if (!lista_vazia(lista)) {
        NO *paux = lista->inicio;

        while (paux != NULL) {
            NO *prem = paux;
            paux = paux->proximo;
            free(prem);
        }
    }

    lista->inicio = NULL;
    lista->fim = NULL;
    lista->tam = 0;
}

void lista_remover_inicio(LISTA* lista) {
    if (!lista_vazia(lista)) { //verifica se a lista não está vazia
        NO *paux = lista->inicio;

        if (lista->inicio == lista->fim) { //lista com um elemento
            lista->inicio = NULL;
            lista->fim = NULL;
        } else { //lista com mais de um elemento
            lista->inicio = paux->proximo; //2º elemento == aux2
            lista->inicio->anterior = NULL;
        }

        free(paux); //removo o nó da memória

        lista->tam--;

        return ;
    } else {
        return ;
    }
}

void lista_ordenar(LISTA* lista) {
    int *vet, i;
    int size = lista->tam;
    ITEM aux;

    vet = (int *)malloc(lista->tam * sizeof(int));
    if (vet == NULL) exit(1);

    for (i=0; i<size; i++) {
        vet[i] = lista->inicio->item.id;
        lista_remover_inicio(lista);
    }

    MergeSort(vet, size);

    for (i=0; i<size; i++) {
        aux.id = vet[i];
        lista_inserir_fim(lista, &aux);
    }

    free(vet);
}

void lista_remover_fim(LISTA* lista) {
    if (!lista_vazia(lista)) { //verifica se a lista não está vazia
        NO *paux = lista->fim;

        if (lista->inicio == lista->fim) { //lista com um elemento
            lista->fim = NULL;
            lista->inicio = NULL;
        } else { //lista com mais de um elemento
            lista->fim = paux->anterior;
            lista->fim->proximo = NULL;
        }

        free(paux); //removo o nó da memória

        lista->tam--;

        return ;
    } else {
        return ;
    }
}

//O(n)
void lista_remover_por_id(LISTA* lista, int id) {
    NO* aux;
    NO* ant;
    aux = lista_busca(lista, id);
    if (aux != NULL) { //verifica se a lista não está vazia pelo retorno da função acima

        if (lista->inicio == lista->fim) { //lista com um elemento
            lista->inicio = NULL;
            lista->fim = NULL;
        } else { //lista com mais de um elemento
            ant = aux->anterior; //aux = aluno de menor nota
            if (ant != NULL) //Verifica se ó nó a ser removido não é o primeiro elemento
                ant->proximo = aux->proximo;
            else lista->inicio = aux->proximo;

            ant = aux->proximo;
            if (ant != NULL) //Verifica se ó nó a ser removido não é o último elemento
                ant->anterior = aux->anterior;
            else lista->fim =  aux->anterior;
        }

        free(aux); //removo o nó da memória

        lista->tam--;

        return;
    } else {
        return;
    }
}

//O(1)
NO* lista_remover_por_no(LISTA* lista, NO* aux) {
    NO* ant;
    if (aux != NULL) {

        if (lista->inicio == lista->fim) { //lista com um elemento
            lista->inicio = NULL;
            lista->fim = NULL;
        } else { //lista com mais de um elemento
            ant = aux->anterior; //aux = aluno de menor nota
            if (ant != NULL) //Verifica se ó nó a ser removido não é o primeiro elemento
                ant->proximo = aux->proximo;
            else lista->inicio = aux->proximo;

            ant = aux->proximo;
            if (ant != NULL) //Verifica se ó nó a ser removido não é o último elemento
                ant->anterior = aux->anterior;
            else lista->fim =  aux->anterior;
        }

        lista->tam--;

        return aux;

    } else {
        return aux;
    }
}


void lista_copiar (LISTA* origem, LISTA* destino) {
    lista_apagar(destino);

    NO* cursor = origem->inicio;
    ITEM item_temp;

    while (cursor!= NULL) {
        item_temp.id = cursor->item.id;
        lista_inserir_fim(destino, &item_temp);
        cursor = cursor->proximo;
    }
}

//Push_front, O(1). Retorna 0 em caso de erro
int lista_inserir_inicio(LISTA *lista, ITEM *item) {
    NO *pnovo = (NO *)malloc(sizeof(NO)); //crio um novo nó

    if (pnovo != NULL) { //verifica se existe memória disponível
        //preenche o os dados
        pnovo->item = *item;
        pnovo->proximo = lista->inicio;
        pnovo->anterior = NULL;
        if (lista->inicio != NULL) {
            lista->inicio->anterior = pnovo;
        } else {
            lista->fim = pnovo; //ajusta ponteiro para fim
        }

        lista->inicio = pnovo; //ajusta ponteiro início

        lista->tam++;

        return 1;

    } else {
        //Em caso de erro
        return 0;
    }
}

//Push_back, O(1). Retorna 0 em caso de erro
int lista_inserir_fim(LISTA *lista, ITEM *item) {
    NO *pnovo = (NO *)malloc(sizeof(NO)); //Cria um novo nó

    if (pnovo != NULL) { //Verifica se existe memória disponível
        //Preenche os dados do nó
        pnovo->item = *item;
        pnovo->proximo = NULL;
        pnovo->anterior = lista->fim;

        if (lista->fim != NULL) {
            lista->fim->proximo = pnovo;
        } else {
            lista->inicio = pnovo; //Ajusta ponteiro para início
        }

        lista->fim = pnovo; //Ajusta ponteiro fim

        lista->tam++;

        return 1;

    } else {
        //Em caso de erro
        return 0;
    }
}

//Busca um valor contido em um nó em O(n)
NO* lista_busca(LISTA* lista, int valor_procurado) {
    NO* cursor = lista->inicio;
    while (cursor->item.id != valor_procurado && cursor != NULL) {
        cursor = cursor->proximo;
        if (cursor == NULL) break;
    }
    return cursor;
}

//Imprime os valores de nó de uma lista encadeada
void lista_imprimir(LISTA *lista) {
    NO* aux;
    aux = lista->inicio;
    if (!lista_vazia(lista)) {
        printf ("%d ", aux->item.id); //Mostra o 1º valor
        aux = aux->proximo ;
        while (aux != NULL ) {
            printf ("%d ", aux->item.id);
            if (aux->proximo != NULL) aux = aux->proximo ;
            else break;
        }
        printf("\n");
    } else printf("Lista vazia\n");
}
