#ifndef __GRAFOS_H_
#define __GRAFOS_H_
#define N 62
typedef struct Item *Ponteiro;

typedef struct Item{
    int conteudo;
    Ponteiro proximo;
    int grau;
}Item;

typedef struct Lista{
    Ponteiro primeiro,ultimo;
}Lista;

typedef struct Grafo{
    Lista list_adj[N];
    float coef_medio;
}Grafo;

Lista criar_lista_vazia(void);

Lista inserir_lista(Lista lista,int num);

void imprimir_lista(Lista lista);

Grafo criar_grafo_vazio(void);

void imprimir_grafo(Grafo grafo);

typedef struct Triangulos *Ponteiro_T;

typedef struct Triangulos{
    int v1,v2,v3;
    Ponteiro_T proximo_t;
}Triangulos;

typedef struct Lista_T{
    Ponteiro_T primeiro_t,ultimo_t;
    int ti;
}Lista_T;

Lista_T criar_lista_t_vazia(void);

Lista_T inserir_lista_t(Lista_T lista, Ponteiro_T t);

int busca_triangulo(Grafo grafo,int i);

void coef_aglomeracao(Grafo grafo);

#endif