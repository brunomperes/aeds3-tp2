/*
 ============================================================================
 TRABALHO PRÁTICO 2 - Art Gallery Problem
 Algoritmos e Estruturas de Dados III

 Bruno Maciel Peres
 brunomperes@dcc.ufmg.br

 LISTA.H - Define a estrutura do TAD lista e o cabeçalho de suas funções.
 ============================================================================
 */

#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

//Guarda o conteúdo relativo ao nó (preferência da pessoa)
typedef struct {
    int id; //Id do vértice com o qual o vértice dessa lista se liga
} ITEM;

//Armazena os ponteiros para o próximo e para o nó anterior, além de uma estrutura contendo valores relativos à preferência da pessoa
typedef struct NO {
    ITEM item;
    struct NO *proximo;
    struct NO *anterior;
} NO;

//Define a lista, que representará um vértice
typedef struct {
    float x;
    float y;
    int tam; //Tamanho da lista
    NO *inicio;
    NO *fim;
} LISTA;

//Cria uma lista vazia em O(1)
void lista_criar(LISTA *lista);

//Verifica se uma lista está vazia em O(1)
int lista_vazia(LISTA *lista);

//Push_front, O(1). Retorna 0 em caso de erro
int lista_inserir_inicio(LISTA *lista, ITEM *item);

//Push_back, O(1). Retorna 0 em caso de erro
int lista_inserir_fim(LISTA *lista, ITEM *item);

//Remove o primeiro elemento da lista em O(1)
void lista_remover_inicio(LISTA* lista);

//Remove o último elemento da lista em O(1)
void lista_remover_fim(LISTA* lista);

//Remove um nó qualquer da lista em O(1), requer free() no ponteiro retornado
NO* lista_remover_por_no(LISTA* lista, NO* aux);

//Remove um nó da lista através da id contida em ITEM
void lista_remover_por_id(LISTA* lista, int id);

//Apaga uma lista em O(n)
void lista_apagar(LISTA *lista);

//Busca um valor contido em um nó em O(n)
NO* lista_busca(LISTA* lista, int valor);

//Ordena os elementos de uma lista em O(nlogn)
void lista_ordenar(LISTA* lista);

//Copia o conteúdo de uma lista para outra
void lista_copiar (LISTA* origem, LISTA* destino);

//Imprime os valores de nó de uma lista encadeada
void lista_imprimir(LISTA *lista);

#endif // LIST_H_INCLUDED
