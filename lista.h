#include <stdio.h>
#include <stdlib.h>

typedef void* Dados;

struct lista {
	Dados dados;
	struct lista *prox;
};
typedef struct lista Lista;

Lista* lst_criar(Dados d);
void lst_liberar(Lista* l);
int lst_tam(Lista *l);
Lista* lst_add_inicio(Dados d, Lista* l);
Lista* lst_add_fim(Dados d, Lista* l);
Lista* lst_del(Lista* l, int pos);
Lista* lst_buscar(Dados d,int(*igual)(Dados, Dados), Lista* l);
