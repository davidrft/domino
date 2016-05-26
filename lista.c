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
    int tam = 0;
    Lista* p;

    p = l;
    while(p != NULL) {
        tam++;
        p = p->prox;
    }

    return tam;
}

Lista* lst_add_inicio(Dados d, Lista* l) {
    if (l == NULL)
        return lst_criar(d);
    else {
        Lista *l_aux;

        l_aux = lst_criar(d);
        l_aux->prox = l;

        return l_aux;
    }
}

Lista* lst_add_fim(Dados d, Lista* l) {
    if (l == NULL) {
        return lst_criar(d);
    }
    else if (l->prox == NULL)
        l->prox = lst_criar(d);
    else
        lst_adicionar(d, l->prox);
    return l;
}

Lista* lst_del(Lista* l, int pos) {
    if (l == NULL)
        return l;
    else {
        int i;
        Lista* p, *a;

        p = l->prox;
        a = l;
        for(i=0; i<pos; ++i) {
            a = p;
            p = p->prox;
        }
        a->prox = p->prox;
    	free(p);

        return l;
    }
}

Dados lst_get(Lista* l, int pos) {
    if (l == NULL)
	return l;
    else {
    	int i;
    	Lista* p;

    	for(i=0; i<pos; i++)
    	    p = p->prox;
    	lst_del(l, pos);

    	return p->dados;
    }
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
