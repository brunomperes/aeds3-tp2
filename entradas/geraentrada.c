#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main() {
    FILE* output = fopen("entrada_tp2.txt", "w");
    int i, v, a, x, y, j = 1;
    int xaux=5, yaux=1, xaux0=0,yaux0=2, qntvertices, aux;
    printf("Insira a quantidade de instancias:\n");
    scanf("%d", &i);
    fprintf(output, "%d\n", i);
    srand ( time(NULL) );
    while(j <= i) {
        FILE* plotar = fopen("gerado.txt", "w");
        printf("Insira a quantidade de vertices(maior que 4, menor que 251) da instancia %d:\n", j);
        scanf("%d", &v);
        while( v <= 4 || v > 250 ) {
            printf("O numero de vertices deve ser maior que 4 e menor que 251\n Insira novamente:\n");
            scanf("%d", &v);
        }
        qntvertices = v;
        fprintf(output, "%d\n", v);
        fprintf(output, "%d/%d %d/%d\n", 5, 1, 1, 1);
        fprintf(plotar, "%d/%d %d/%d\n", 5, 1, 1, 1);
        v--;
        y=0;
        for(a = 0; a < v/2; a++) {
            do {
                x = rand()%40+61;
                y = y + rand()%20+((qntvertices%100)+(qntvertices%10)+v%50);
            } while (y == yaux || (xaux == x) || (yaux-yaux0)/(xaux-xaux0) == (y-yaux)/(x-xaux));
            yaux0 = yaux;
            xaux0 = xaux;
            xaux = x;
            yaux = y;

            fprintf(output, "%d/%d ", x, 1);
            fprintf(plotar, "%d/%d ", x, 1);

            fprintf(output, "%d/%d\n", y, 1);
            fprintf(plotar, "%d/%d\n", y, 1);


        }
        if(v%2==1) {
            do {
                x = (rand()%30);
                y = y+rand()%10+1;
            } while (y == yaux || xaux == x || (yaux-yaux0)/(xaux-xaux0) == (y-yaux)/(x-xaux));
            yaux0 = yaux;
            xaux0 = xaux;
            xaux = x;
            yaux = y;

            fprintf(output, "%d/%d %d/%d\n", x, 1, y, 1);
            fprintf(plotar, "%d/%d %d/%d\n", x, 1, y, 1);
            v--;
        }
        for(a = 0; a < v/2; a++) {
            do {
                x = rand()%40+1;
                aux = y - (rand()%10+(qntvertices%100)+(qntvertices%10)+v%50);
//        		y = y - (10+80+10+30); //Pior caso
                if (aux<0) {
                    puts("A execução encontrou um erro e precisa ser reiniciada");
                    return main();
                }
            } while (aux == yaux || (xaux == x) || (yaux-yaux0)/(xaux-xaux0) == (aux-yaux)/(x-xaux));
            y = aux;
            yaux0 = yaux;
            xaux0 = xaux;
            xaux = x;
            yaux = y;

            fprintf(output, "%d/%d ", x, 1);
            fprintf(plotar, "%d/%d ", x, 1);

            fprintf(output, "%d/%d\n", y, 1);
            fprintf(plotar, "%d/%d\n", y, 1);

        }

        j++;
        fprintf(plotar, "%d/%d %d/%d\n", 5, 1, 1, 1);
        fclose(plotar);
    }
    fclose(output);
    return 0;
}
