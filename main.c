#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
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
    char nome[40];
    Lista *mao;
} jogador;

int igual(peca *p, peca *d) {
    if (p->a == d->a && p->b == d->b)
        return 1;
    else
        return 0;
}

void wait() {
    fflush(stdin);
    printf("\nPressione ENTER para continuar. \n");
    getchar();
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

int aleatorio(int n) {  //Gera um numero de 0 a n inclusivamente
    int f = (double)rand() / RAND_MAX * (n+1);
    return f;
}

int escolha(int n, int m) { //Pega do usuário um numero de 1 a m (inclusivamente) através do getch
    int c;
    do {
        fflush(stdin);
        scanf("%d", &c);
    } while (c<n || c>m);
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
    printf("\n");
    c = escolha(1,3);
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

int carroca(jogador j, int i, int f) {
    printf("Quem tiver (%d, %d) comeca!\n", i, i);
    peca *c = malloc(sizeof(peca));
        c->a = i;
        c->b = i;
    int pos;
    if (f != 0) {
        printf("O %s tem a carroca de %d!\n", j.nome, i);
        printf("O %s jogou a peca (%d, %d)\n\n", j.nome, i, i);
        pos = buscaPos(j.mao, c);
        return pos;
    }
    else {
        pos = buscaPos(j.mao, c);
        printf("Voce tem a carroca de %d! Pressione %d para joga-la! ", i, pos+1);
        return pos;
    }
}

void printmesa(Lista* l) { //Imprime a lista de peças que estão na mesa com a formatação certa
    printf("\tMESA");
    printf("\n");
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
        printf("\t%d - ", i);
        printp(p->dados);
        printf("\n");
        p = p->prox;
        i++;
    }
    printf("\n");
}

int passa_vez(Lista* mao, int v[], int tam) {
    Lista* l = mao;
    peca* p;
    int i = 0;

    while(l!=NULL) {
        p = (peca*) l->dados;
        if(p->a != v[0] && p->b != v[0] && p->a != v[1] && p->b != v[1])
            i++;
        l = l->prox;
    }
    if(i == tam)
        return 1;
    else
        return 0;
}

int todos_passam(jogador pc[], int v[], int tampc[]) {
    int i;

    for(i=0; i<4; i++) {
        if(!(passa_vez(pc[i].mao, v, tampc[i])))
            return 0;
    }

    return 1;
}

int somapecas(Lista* mao){
    Lista* l = mao;
    peca* p;
    int soma;

    while(l != NULL) {
        p = l->dados;
        soma = p->a + p->b;
        l = l->prox;
    }

    return soma;
}

int game(jogador pc[], Lista* mesa, Lista* pecasAll) {
    int i, v[2] = {0}, aux, j, tampc[4];
    for(i=0; i<4; ++i) {
        tampc[i] = lst_tam(pc[i].mao);
    }
    int rodada = 0, ordem, e = 0;
    Lista *l = mesa;
    peca *table;

    while (1) {
        //system("cls");
        if(todos_passam(pc, v, tampc)) {
            jogador vencedor;

            strcpy(vencedor.nome,pc[0].nome);
            vencedor.pc = somapecas(pc[0].mao);
            for(i=1; i<4; i++) {

                if(somapecas(pc[i].mao) < vencedor.pc) {
                    strcpy(vencedor.nome, pc[i].nome);
                    vencedor.pc = somapecas(pc[i].mao);
                } else if(somapecas(pc[i].mao) == vencedor.pc)
                    strcat(strcat(vencedor.nome, " e "), pc[i].nome);
            }

            printf("O(s) vencedor(es) foi(ram) %s com %d pontos", vencedor.nome, vencedor.pc);
            break;
        }
        else {

            if (rodada == 0) { //Verificando quem tem a maior carroca e joga primeiro.
                int pos;
                char opcao=7;
                peca *c = malloc(sizeof(peca));

                for (i = 6; i>=0; i--) {
                    c->a = i;
                    c->b = i;
                    for (j=0; j<4; j++) {
                        if (buscaPeca(pc[j].mao, c)) {
                            if (j != 0) {
                                pos = carroca(pc[j], i, j);
                                pc[j].mao = lst_del(pc[j].mao, pos);
                                mesa = lst_criar(c);
                                tampc[j]--;
                                ordem = j+1;
                                break;
                            }
                            else {
                                pos = carroca(pc[0], i, j);
                                do {
                                    opcao = escolha(1, 6);
                                } while (opcao != pos+1);
                                printf("\n");
                                pc[0].mao = lst_del(pc[0].mao, opcao-1);
                                mesa = lst_criar(c);
                                tampc[0]--;
                                ordem = 1;
                                break;
                            }
                        }
                    }
                    if(mesa != NULL)
                        break;
                    printf("Ninguem tem (%d, %d), proxima carroca...\n", i, i);
                }
                printmesa(mesa);
                wait();
            }
            else {
                for(j=0; j<4; ++j) {
                    l = mesa;
                    i = 0;
                    if(ordem%4 != 0) {
                        table = (peca *)l->dados;
                        v[0] = table->a; //numero livre para jogadas no começo da mesa
                        while(l->prox != NULL)
                            l = l->prox;
                        table = (peca *)l->dados;
                        v[1] = table->b; //numero livre para jogadas no fim da mesa


                        l = pc[ordem%4].mao;
                        if(passa_vez(pc[ordem%4].mao, v, tampc[ordem%4])) {
                            printf("Computador %d passou a jogada\n", ordem%4);
                        }
                        else {
                            while(l!= NULL) {
                                table = (peca *)l->dados;

                                if(table->a == v[0]) {
                                    aux = table->a;
                                    table->a = table->b;
                                    table->b = aux;

                                    mesa = lst_add_inicio(table, mesa);
                                    pc[ordem%4].mao = lst_del(pc[ordem%4].mao, i);
                                    tampc[ordem%4]--;
                                    break;
                                }
                                else if(table->b == v[0]) {
                                    mesa = lst_add_inicio(table, mesa);
                                    pc[ordem%4].mao = lst_del(pc[ordem%4].mao, i);
                                    tampc[ordem%4]--;
                                    break;
                                }
                                else if(table->a == v[1]) {
                                    mesa = lst_add_fim(table, mesa);
                                    pc[ordem%4].mao = lst_del(pc[ordem%4].mao, i);
                                    tampc[ordem%4]--;
                                    break;
                                }
                                else if(table->b == v[1]) {
                                    aux = table->a;
                                    table->a = table->b;
                                    table->b = aux;

                                    mesa = lst_add_fim(table, mesa);
                                    pc[ordem%4].mao = lst_del(pc[ordem%4].mao, i);
                                    tampc[ordem%4]--;
                                    break;
                                }
                                i++;
                                l = l->prox;
                            }
                            printf("Computador %d jogou a peca (%d, %d)\n\n", ordem%4, table->a, table->b);
                            printmesa(mesa);
                        }
                        wait();

                        if(tampc[i] == 0) {
                            printf("\n\tComputador %d ganhou o jogo!\n", ordem%4);
                            exit(1);
                        }
                        ordem++;
                    }
                    else {
                        int valido;
                        table = (peca *)l->dados;
                        v[0] = table->a; //numero livre para jogadas no começo da mesa
                        while(l->prox != NULL)
                            l = l->prox;
                        table = (peca *)l->dados;
                        v[1] = table->b; //numero livre para jogadas no fim da mesa

                        for(i=3; i>=0; --i)
                            printf("%s (%d pecas)\n", pc[i].nome, tampc[i]);
                        printf("\n");
                        printmesa(mesa);
                        i = 0;
                        printmao(pc[0].mao);
                        printf("Sua vez!\n");
                        do{
                            fflush(stdin);
                            printf("Escolha a peca, digite -1 pra passar a vez ou 0 para sair: ");
                            scanf("%d", &e);
                            valido = 1;

                            if (e == -1) {
                                valido = passa_vez(pc[ordem%4].mao, v, tampc[ordem%4]);
                                if(valido==1) {
                                    printf("\nVoce passou a vez!\n\n");
                                    break;
                                }
                                else {
                                    printf("\nVoce nao pode passar a vez, jogue uma peca valida!\n");
                                    valido = 0;
                                    continue;
                                }
                            } else if( e == 0) {
                                do {
                                    printf("\n\tDeseja salvar o jogo? (1 para sim, 0 caso desejar sair sem salvar)\n");
                                    scanf("%d", &valido);
                                } while(valido != 1 && valido != 0);

                                if(valido == 1) {
                                    //salvar o jogo
                                    exit(1);
                                }
                                else {
                                    exit(1);
                                }

                            } else if (e>0 && e <= tampc[ordem%4]) {
                                l = pc[ordem%4].mao;
                                for(i=1; i<e; ++i)
                                    l = l->prox;
                                table = (peca *)l->dados;
                                if((table->a == v[0] && table->b == v[1]) || (table->b == v[0] && table->a == v[1])){
                                    do {
                                        printf("Digite 1 para jogar na esquerda e 2 para jogar na direita: ");
                                        scanf("%d", &e);
                                    } while (e!= 1 && e != 2);

                                    if(e==1) {
                                        if(table->a == v[0]) {
                                            aux = table->a;
                                            table->a = table->b;
                                            table->b = aux;

                                            mesa = lst_add_inicio(table, mesa);
                                            pc[ordem%4].mao = lst_del(pc[ordem%4].mao, i-1);
                                            tampc[ordem%4]--;
                                        }
                                        else if(table->b == v[0]) {
                                            mesa = lst_add_inicio(table, mesa);
                                            pc[ordem%4].mao = lst_del(pc[ordem%4].mao, i-1);
                                            tampc[ordem%4]--;
                                        }
                                    }else {
                                        if(table->a == v[1]) {
                                            mesa = lst_add_fim(table, mesa);
                                            pc[ordem%4].mao = lst_del(pc[ordem%4].mao, i-1);
                                            tampc[ordem%4]--;
                                        }
                                        else if(table->b == v[1]) {
                                            aux = table->a;
                                            table->a = table->b;
                                            table->b = aux;

                                            mesa = lst_add_fim(table, mesa);
                                            pc[ordem%4].mao = lst_del(pc[ordem%4].mao, i-1);
                                            tampc[ordem%4]--;
                                        }
                                    }
                                } else if (table->a == v[0]) {
                                    aux = table->a;
                                    table->a = table->b;
                                    table->b = aux;

                                    mesa = lst_add_inicio(table, mesa);
                                    pc[ordem%4].mao = lst_del(pc[ordem%4].mao, i-1);
                                    tampc[ordem%4]--;
                                } else if (table->b == v[0]) {
                                    mesa = lst_add_inicio(table, mesa);
                                    pc[ordem%4].mao = lst_del(pc[ordem%4].mao, i-1);
                                    tampc[ordem%4]--;
                                } else if(table->a == v[1]) {
                                    mesa = lst_add_fim(table, mesa);
                                    pc[ordem%4].mao = lst_del(pc[ordem%4].mao, i-1);
                                    tampc[ordem%4]--;
                                } else if(table->b == v[1]) {
                                    aux = table->a;
                                    table->a = table->b;
                                    table->b = aux;

                                    mesa = lst_add_fim(table, mesa);
                                    pc[ordem%4].mao = lst_del(pc[ordem%4].mao, i-1);
                                    tampc[ordem%4]--;
                                }
                                else {
                                    valido = 0;
                                    printf("\nJogada invalida, tente outra peca!\n\n");
                                }
                            }
                            else
                                valido = 0;

                            if (valido == 1) {
                                printf("\nVoce jogou a peca (%d, %d)\n\n", table->a,table->b);
                                printmesa(mesa);
                            }
                        }while (valido == 0);

                        if(tampc[ordem%4] == 0) {
                            printf("\n\tParabens, voce ganhou o jogo!\n");
                            exit(1);
                        }
                        i++;
                        ordem++;
                    }
                }
            }
            rodada++;
            //system("PAUSE");
        }

    }

    return 1;
}

int main() {
    //SetConsoleTitle("Projeto Metodos Computacionais - Domino Lista");
    srand(time(NULL)*getpid());

    peca p[28];
    jogador pc[4];
    strcpy(pc[0].nome, "Jogador");
    strcpy(pc[1].nome, "Computador 1");
    strcpy(pc[2].nome, "Computador 2");
    strcpy(pc[3].nome, "Computador 3");
    Lista* mesa = NULL;
    Lista* pecasAll;
    int i, j, tam, aleat;

    int c = menu();
    printf("\n\n");
    switch (c) {
        case 1:
            pecasAll = gerarpecas(pecasAll, p);
            for (i=0; i<4; i++) {
                tam = lst_tam(pecasAll) - 1;
                Dados d;
                for (j=0; j<6; j++) {
                    aleat = aleatorio(tam);
                    d = lst_get(pecasAll, aleat);
                    pecasAll = lst_del(pecasAll, aleat);
                    if (j==0) {
                        pc[i].mao = lst_criar(d);
                    }
                    else {
                        pc[i].mao = lst_add_fim(d, pc[i].mao);
                    }
                tam--;
                }
            }
            game(pc, mesa, pecasAll);
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
