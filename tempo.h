#ifndef TEMPO_H_INCLUDED
#define TEMPO_H_INCLUDED

/*
Criado por: Bruno Maciel Peres
            brunomperes@dcc.ufmg.br

Exemplo de uso:
MostraTempo(tempogasto);
MostraTempo(EstimaTempo(tempogasto, N3, 10));
*/

enum Complexidade { //Definindo um tipo int para complexidade de funçao
    O1, // 0
    LOGN, // 1
    N, // 2
    NLOGN, // 3
    N2, // 4
    N3, //5
};

typedef struct {
    int hora;
    int min;
    int seg;
    int useg; //microssegundos
} tempo;

//Mostra a hora atual
void MostraHora();

//Mostra as horas no formato 2h30min a partir de double segundos
void MostraTempo (double msec);

//recebe segundos com decimais que representam microsegundos
void Converte(double msec, tempo *t);

//Estima o tempo de execução do algoritmo em segundos, a partir de uma execução anterior de mesma complexidade
double EstimaTempo(double msec, int fatorcomplexidade, double fatorcrescimento);

#endif // TEMPO_H_INCLUDED
