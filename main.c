#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

typedef struct {
    int a;
    int b;
}peca;


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
    do {
        c = getch();
        c = (int)(c - '0');
    } while (c<1 || c>3);
    if (c == 3) {
        exit(3);
    }
}

Lista* gerarpecas() {
    int i, j, k=0;
    Lista* v;
    peca pedra;
    for (i=0; i <= 6; i++) {
        for (j = 0; j <= i; j++) {
            pedra.a = i;
            pedra.b = j;
            if (i=0 && j=0) {
                v = lst_criar(pedra);
            } else {
                lst_adicionar(pedra, v);
            }
        }
    }
}

void printp (peca p) {
    printf("(%d, %d)", p.a, p.b);
}

void printl (Lista* l) {
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


int main() {
    inicializar();
    peca pecasAll[28];

    gerarpecas(pecasAll);

    menu();
    //printl(mesa);
    printf("\n");
    return 0;
}
