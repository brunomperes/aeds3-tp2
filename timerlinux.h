#ifndef TIMER_H_INCLUDED
#define TIMER_H_INCLUDED

#include <sys/time.h>

typedef struct {
    struct timeval start;
    struct timeval stop;
} stopWatch;

//Inicia o contador de tempo
void startTimer( stopWatch *timer) ;

//Para o contador de tempo
void stopTimer( stopWatch *timer) ;

//Retorna o tempo gasto em milissegundos
double getElapsedTime( stopWatch *timer) ;

#endif // TIMER_H_INCLUDED
