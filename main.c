#include <stdio.h>
#include <stdlib.h>
//#include <conio.h>
//#include <windows.h>
#include <math.h>
#include <time.h>
#include "lista.h"
#include <string.h>

typedef struct {
    int a;
    int b;
} peca;

typedef struct {
    int pc;
    char nome[20];
    Lista *mao;
} jogador;

int igual(peca *p, peca *d) {
    if (p->a == d->a && p->b == d->b)
        return 1;
    else
        return 0;
}

int buscaPeca(Lista *l, peca *p) {
    Lista *v = l;
    while (v != NULL) {
        if (igual((peca*)(v->dados), p)) {
            return 1;
        }
        v = v->prox;
    }
    return 0;
}

int buscaPos(Lista *l, peca *p) {
    Lista *v = l;
    int pos = 0;
    while (v != NULL) {
        if (igual((v->dados), p))
            return pos;
        v = v->prox;
        pos++;
    }
    return pos;
}

int random(int n) {  //Gera um numero de 0 a n inclusivamente
    srand(time(NULL));
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

int carroca(jogador j, int i) {
    printf("Quem tiver (%d, %d) comeca!\n", i, i);
    peca *c = malloc(sizeof(peca));
        c->a = i;
        c->b = i;
    int pos;
    if (j.pc == 1) {
        printf("O %s tem a carroca de %d!\n\n", j.nome, i);
        pos = buscaPos(j.mao, c);
        return pos;
    }
    else {
        pos = buscaPos(j.mao, c);
        printf("Voce tem a carroca de %d! Pressione %d para joga-la!\n\n", i, pos+1);
        return pos;
    }
}

void printmesa(Lista* l) { //Imprime a lista de peças que estão na mesa com a formatação certa
    printf("\tMESA");
    Lista* p;
    if (l == NULL) {
        printf("\n");
    }else {
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
        printf("\n\n");
    }
}
void printmao(Lista* l) {
    Lista* p = l;
    int i = 1;
    while (p != NULL) {
        printf("%d - ", i);
        printp(p->dados);
        printf("\n");
        p = p->prox;
        i++;
    }
    printf("\n");
}

int gameEasy() {
    peca p[28];

    jogador player, pc1, pc2, pc3;
    strcpy(player.nome, "Jogador");
    player.pc = 0;
    strcpy(pc1.nome, "Computador 1");
    pc1.pc = 1;
    strcpy(pc2.nome, "Computador 2");;
    pc2.pc = 1;
    strcpy(pc3.nome, "Computador 3");;
    pc3.pc = 1;

    Lista *pecasAll, *mesa = NULL;
    pecasAll = gerarpecas(pecasAll, p);
    int i, aleat, tam;

    //Atribuindo pc1
    tam = lst_tam(pecasAll) - 1;
    Dados d;
    for (i=0; i<6; i++) {
        aleat = random(tam);
        d = lst_get(pecasAll, aleat);
        pecasAll = lst_del(pecasAll, aleat);
        if (i==0) {
            pc1.mao = lst_criar(d);
        }
        else {
            pc1.mao = lst_add_fim(d, pc1.mao);
        }
    tam--;
    }

    //Atribuindo pc2
    tam = lst_tam(pecasAll) - 1;
    for (i=0; i<6; i++) {
        aleat = random(tam);
        d = lst_get(pecasAll, aleat);
        pecasAll = lst_del(pecasAll, aleat);
        if (i==0) {
            pc2.mao = lst_criar(d);
        }
        else {
            pc2.mao = lst_add_fim(d, pc2.mao);
        }
    tam--;
    }

    //Atribuindo pc3
    tam = lst_tam(pecasAll) - 1;
    for (i=0; i<6; i++) {
        aleat = random(tam);
        d = lst_get(pecasAll, aleat);
        pecasAll = lst_del(pecasAll, aleat);
        if (i==0) {
            pc3.mao = lst_criar(d);
        }
        else {
            pc3.mao = lst_add_fim(d, pc3.mao);
        }
    tam--;
    }

    //Atribuindo player
    tam = lst_tam(pecasAll) - 1;
    for (i=0; i<6; i++) {
        aleat = random(tam);
        d = lst_get(pecasAll, aleat);
        pecasAll = lst_del(pecasAll, aleat);
        if (i==0) {
            player.mao = lst_criar(d);
        }
        else {
            player.mao = lst_add_fim(d, player.mao);
        }
    tam--;
    }

    int tampc1 = lst_tam(pc1.mao);
    int tampc2 = lst_tam(pc2.mao);
    int tampc3 = lst_tam(pc3.mao);
    int tamplayer = lst_tam(player.mao);
    int rodada = 0;
    while (tampc1 != 0 || tampc2 != 0 || tampc3 != 0 || tamplayer != 0) {
        //system("cls");

        printf("%s (%d)", player.nome, tamplayer);
        printf("\n");
        printmao(player.mao);
        printf("%s (%d)", pc1.nome, tampc1);
        printf("\n");
        printmao(pc1.mao);
        printf("%s (%d)", pc2.nome, tampc2);
        printf("\n");
        printmao(pc2.mao);
        printf("%s (%d)", pc3.nome, tampc3);
        printf("\n");
        printmao(pc3.mao);
        printf("Dorme (4)");
        printf("\n");
        printmao(pecasAll);

        printmesa(mesa);
        //system("PAUSE");
        if (rodada == 0) { //Verificando quem tem a maior carroca e joga primeiro.
            int pos;
            char opcao=7;
            for (i = 6; i>=0; i--) {
                peca *c = malloc(sizeof(peca));
                    c->a = i;
                    c->b = i;
                if (buscaPeca(pc1.mao, c) == 1) {
                    pos = carroca(pc1, i);
                    pc1.mao = lst_del(pc1.mao, pos);
                    mesa = lst_criar(c);
                    tampc1--;
                    break;
                }
                else if (buscaPeca(pc2.mao, c) == 1) {
                    pos = carroca(pc2, i);
                    pc2.mao = lst_del(pc2.mao, pos);
                    mesa = lst_criar(c);
                    tampc2--;
                    break;
                }
                else if (buscaPeca(pc3.mao, c) == 1) {
                    pos = carroca(pc3, i);
                    pc3.mao = lst_del(pc3.mao, pos);
                    mesa = lst_criar(c);
                    tampc3--;
                    break;
                }
                else if (buscaPeca(player.mao, c) == 1) {
                    pos = carroca(player, i);
                    do {
                        fflush(stdin);
                        opcao = escolha(6);
                    } while (opcao != pos+1);
                    player.mao = lst_del(player.mao, opcao-1);
                    mesa = lst_criar(c);
                    break;
                }
                else {
                    printf("Ninguem tem (%d, %d), proxima carroca...\n", i, i);
                }
            }
        }
        rodada++;
        //system("PAUSE");
        break;
    }




    return 1;
}

int main() {
    //SetConsoleTitle("Projeto Metodos Computacionais - Domino Lista");

    int c = menu();
    printf("\n\n");
    switch (c) {
        case 1:
            gameEasy();
            scanf("%d", &c);
            break;
        case 2:
            break;
        case 3:
            return 1;
            break;
        default:
            return 1;
    }

    return 0;
}
