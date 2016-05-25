#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <math.h>
#include <time.h>

srand(time(NULL)*getpid());

typedef struct {
    int a;
    int b;
}peca;

int random(int n) {
    int f = (double)rand() / RAND_MAX * (n+1);
    return f;
}

int escolha(int n, int m) {
    int c;
    do {
        c = getch();
        c = (int)(c - '0');
    } while (c<n || c>m);
    return c;
}

int menu() {
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
    c = escolha(1, 3);
    if (c == 3) {
        exit(3);
    }
}

Lista* gerarpecas() {
    int i, j, k=0;
    Lista* v;
    peca p;
    for (i=0; i <= 6; i++) {
        for (j = 0; j <= i; j++) {
            pedra.a = i;
            pedra.b = j;
            if (i=0 && j=0) {
                v = lst_criar(p);
            } else {
                lst_add_fim(p, v);
            }
        }
    }
}

void printp(peca p) {
    printf("(%d, %d)", p.a, p.b);
}

void printl(Lista* l) {
    Lista* p = l->proximo;
    printf("   ");
    while (1) {
        printp(p->dados);
        p = p->proximo;
        if (p == NULL)
            break;
        p = p->proximo;
        if (p == NULL)
            break;
    }
    p = l;
    printf("\n");
    while (1) {
        printp(p->dados);
        p = p->proximo;
        if (p == NULL)
            break;
        p = p->proximo;
        if (p == NULL)
            break;
    }

}

void atribuirpecas(lista* p, lista *v, int n) {
    int i, aleat, tam;
    tam = lst_tam(v);
    for (i=0; i<n; i++) {
        aleat = random(tam)
        if (p==NULL) {
            lst_criar(lst_get(v, aleat));
            lst_del(v, aleat);
            tam--;
        }
        else {
            lst_add_end(lst_get(v, aleat));
            lst_del(v, aleat);
            tam--;
        }
    }
}

int main() {
    SetConsoleTitle("Projeto Métodos Computacionais - Domino Lista");
    menu();
    return 0;
}
