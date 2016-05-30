#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <math.h>
#include <time.h>
#include "lista.h"

typedef struct {
    int a;
    int b;
} peca;

int igual(peca *p, peca *d) {
    if (p->a == d->a && p->b && d->b)
        return 1;
    else
        return 0;
}

int random(int n) {  //Gera um numero de 0 a n inclusivamente
    int f = (double)rand() / RAND_MAX * (n+1);
    return f;
}

int escolha(int m) { //Pega do usuário um numero de 1 a m (inclusivamente) através do getch
    int c;
    do {
        c = getch();
        c = (int)(c - '0');
    } while (c<1 || c>m);
    return c;
}

int menu() { //Menu inicial
    int c;
    printf("\t______                _             \n");
    printf("\t|  _  \\              (_)            \n");
    printf("\t| | | |___  _ __ ___  _ _ __   ___  \n");
    printf("\t| | | / _ \\| '_ ` _ \\| | '_ \\ / _ \\ \n");
    printf("\t| |/ / (_) | | | | | | | | | | (_) |\n");
    printf("\t|___/ \\___/|_| |_| |_|_|_| |_|\\___/ \n");
    printf("\n");
    printf("\t\t1. Novo Jogo");
    printf("\n\t\t2. Continue Jogo");
    printf("\n\t\t3. Sair");
    c = escolha(3);
    return c;
}

Lista* gerarpecas(Lista* v, peca *p) { //Gera todas as peças do domino
    int i, j, k=0;
    for (i=0; i <= 6; i++) {
        for (j = 0; j <= i; j++) {
            p[k].a = i;
            p[k].b = j;
            if (i==0 && j==0) {
                v = lst_criar((Dados)(&p[k]));
            } else {
                v = lst_add_fim((Dados)(&p[k]), v);
            }
            k++;
        }
    }
    return v;
}

void printp(Dados d) { //Imprime uma peça do domino
    peca *p = (peca*) d;
	printf("(%d, %d)", p->a, p->b);
}

void printmesa(Lista* l) { //Imprime a lista de peças que estão na mesa com a formatação certa
    Lista* p;
    if (l->prox != NULL) {
        p = l->prox;
        printf("   ");
        while (1) {
            printp(p->dados);
            if (p->prox != NULL)
                p = p->prox;
            else
                break;
            if (p->prox != NULL)
                p = p->prox;
            else
                break;
        }
    }
    p = l;
    printf("\n");
    while (1) {
        printp(p->dados);
        if (p->prox != NULL)
            p = p->prox;
        else
            break;
        if (p->prox != NULL)
                p = p->prox;
        else
            break;
    }
}

void atribuirpecas(Lista* l, Lista *v, int n) { //Atribui n peças aleatórias da lista v para a lista p
    int i, aleat, tam;
    peca* p;
    tam = lst_tam(v);
    for (i=0; i<n; i++) {
        aleat = random(tam);
        if (i==0)
            l = lst_criar(lst_get(v, aleat));
        else
            l = lst_add_fim(lst_get(v, aleat), l);
        tam--;
    }
}

void printmao(Lista* l) {
    Lista* p = l;

    if(p != NULL) {
        do {
            printp(p->dados);
            printf("\n");
            p = p->prox;
        } while(p->prox != NULL);
    }
}

int main() {
    srand(time(NULL)*getpid());
    SetConsoleTitle("Projeto Metodos Computacionais - Domino Lista");

    peca p[28];
    Lista *pecasAll, *pc1, *pc2, *pc3, *player, *mesa;
    int i, j, k=0;
    pecasAll = gerarpecas(pecasAll, p);

    int c = menu();
    if (c == 1) {
        system("cls");
        atribuirpecas(pc1, pecasAll, 6);
        atribuirpecas(pc2, pecasAll, 6);
        atribuirpecas(pc3, pecasAll, 6);
        atribuirpecas(player, pecasAll, 6);
        printmesa(pecasAll);
    }

    return 0;
}
