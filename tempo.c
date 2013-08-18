#include <math.h>
#include <stdio.h>
#include <time.h>

#include "tempo.h"

void Converte(double msec, tempo *t) { //recebe segundos com decimais que representam microsegundos e transforma em horas, mins, segs, e usegs
    t->hora = 0;
    t->min = 0;
    t->seg = 0;
    t->useg = 0;
    if (msec >= 3600) {
        t->hora = msec/3600;
        msec = msec - (t->hora*3600);
    } else t->hora = 0;

    if (msec >= 60) {
        t->min = msec/60;
        msec = msec - (t->min*60);
    } else t->min = 0;

    if (msec >= 1) {
        t->seg = msec;
        msec = msec - (t->seg*0.000001);
    } else t->seg = 0;

    if (msec >= 0) {
        t->useg = msec;
    } else t->useg = 0;
}

void MostraHora() {
    struct tm *ptr;
    time_t tm;
    char str[60];
    tm = time(NULL);
    ptr = localtime(&tm);
    strftime(str, 100, "%X.\n",ptr);
    puts(str);
}

void MostraTempo (double msec) { //Mostra os segundos no formato 2h30min47segs
    tempo t;
    Converte(msec, &t);
    printf ("%dh%dmin%dsegs\n", t.hora, t.min, t.seg);
}

double EstimaTempo(double msec, int fatorcomplexidade, double fatorcrescimento) {
    double multiplicador = -1;
    switch (fatorcomplexidade) {
    case O1:
        multiplicador = fatorcomplexidade;
        break;
    case LOGN:
        multiplicador = log(fatorcrescimento)/log(2);
        break;
    case N:
        multiplicador = fatorcrescimento;
        break;
    case NLOGN:
        multiplicador = fatorcrescimento*(log(fatorcrescimento)/log(2)); //Log na base 2
        break;
    case N2:
        multiplicador = pow(fatorcrescimento,2);
        break;
    case N3:
        multiplicador = pow(fatorcrescimento,3);
        break;
    }
    msec *= multiplicador;
    return msec;
}
