#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

Lista* lst_criar(Dados d) {
    Lista* l = (Lista*) malloc(sizeof(Lista));
    l->dados = d;
    l->prox = NULL;
    return l;
}

void lst_liberar(Lista* l) {
    Lista* p = l;
    Lista* t;
    while (p != NULL) {
        t = p->prox;
        free(p);
        p = t;
    }
}

int lst_tam(Lista *l) {
    int tam = 1;
    Lista* p = l;

    while(p->prox != NULL) {
        tam++;
        p = p->prox;
    }

    return tam;
}

Lista* lst_add_inicio(Dados d, Lista *l) {
    Lista *p;

    p = lst_criar(d);
    p->prox = l;

    return p;
}

Lista* lst_add_fim(Dados d, Lista* l) {
    Lista* p = l;

    while(p->prox != NULL) {
        p = p->prox;
    }
    p->prox = lst_criar(d);
    return l;
}

Lista* lst_del(Lista* l, int pos) {
    if (pos == 0) {
        return l->prox;
    } else {
    int i;
    Lista *p = l;
    Lista *v = l->prox->prox;
    for (i=1; i<pos; i++) {
      p = p->prox;
      v = v->prox;
    }
    free(p->prox);
    p->prox = v;
    return l;
  }
}

Dados lst_get(Lista* l, int pos) {
    Lista *p = l;
    Dados d;
    int i=0;

    if (i==0) {
        d = p->dados;
    }

    while(p->prox!=NULL && i<pos) {
        p = p->prox;
        i++;
    }
    d = p->dados;

    return d;
}

Lista* lst_buscar(Dados d,int(*igual)(Dados, Dados), Lista* l) {
    if (l == NULL) {
        return NULL;
    }
    if (igual(d, l->dados))
        return l;
    else
        return lst_buscar(d, igual, l->prox);
}
