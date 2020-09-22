#include "grafos.h"

Lista criar_lista_vazia(){//cria uma lista vazia
    Lista nova_lista;
    nova_lista.primeiro = (Ponteiro)malloc(sizeof(Item));
    nova_lista.primeiro->proximo = NULL;
    nova_lista.ultimo = nova_lista.primeiro;
    return nova_lista;
}

Lista inserir_lista(Lista lista,int num){//insere um elemento na lista
    lista.ultimo->proximo = (Ponteiro)malloc(sizeof(Item));
    lista.ultimo = lista.ultimo->proximo;
    lista.ultimo->conteudo = num;
    lista.ultimo->proximo = NULL;
    return lista;
}

void imprimir_lista(Lista lista){//imprime uma lista
    Ponteiro atual = lista.primeiro;
    while(1){
        if(atual->proximo == NULL){
            printf("|%d|\n",atual->conteudo);
            return;
        }
        else printf("|%d|->",atual->conteudo);
        atual = atual->proximo_i;
    }
}

Grafo criar_grafo_vazio(){//criar um grafo vazio
    Grafo grafo;
    int i;
    //pra cada vértice criar uma lista vazia
    for(i=0;i<NumeroDeGolfinhos;i++){
        Lista vertice = criar_lista_vazia();
        vertice.primeiro->conteudo = i+1;
        vertice.primeiro->grau=0;
        grafo.list_adj[i] = vertice;        
    }
    return grafo;
}

void imprimir_grafo(Grafo grafo){//imprime o grafo e os graus de cada vértice (tarefa 1)
    int i;
    Lista vertice;
    system("clear");
    for(i=0;i<NumeroDeGolfinhos;i++){
        vertice = grafo.list_adj[i];
        imprimir_lista(vertice);
        printf("Grau: %d\n",vertice.primeiro->grau);
    }
}

Lista_T criar_lista_t_vazia(){//cria uma lista de triangulos vazia
    Lista_T nova_lista_t;
    nova_lista_t.primeiro_t = (Ponteiro_T)malloc(sizeof(Triangulos));
    nova_lista_t.primeiro_t->proximo_t = NULL;
    nova_lista_t.ti = 0;
    nova_lista_t.ultimo_t = nova_lista_t.primeiro_t;
    return nova_lista_t;
}
Lista_T inserir_lista_t(Lista_T lista_t, Ponteiro_T t){
    lista_t.ultimo_t->proximo_t = (Ponteiro_T)malloc(sizeof(Triangulos));
    lista_t.ultimo_t = lista_t.ultimo_t->proximo_t;
    lista_t.ultimo_t->v1 = t->v1;
    lista_t.ultimo_t->v2 = t->v2;
    lista_t.ultimo_t->v3 = t->v3;
    lista_t.ultimo_t->proximo_t = NULL;
    return lista_t;
}

int busca_triangulo(Grafo grafo, int i){
    int j,k,l;
    Ponteiro ref,ref_v,subref,subref_v,subsubref,subsubref_v; 
    Lista_T triangulos = criar_lista_t_vazia();
    Ponteiro_T t = (Ponteiro_T)malloc(sizeof(Triangulos));

    ref = grafo.list_adj[i].primeiro; //ponteiro pra ref
    t->v1 = ref->conteudo;//salvando v1 em caso de formação de triângulo
    //percorrer a lista de vizinhos de ref
    ref_v = ref->proximo;
    for(j=0;j<ref->grau;j++){
        //capturar o ponteiro de ref_v no grafo e salvar em subref
        for(k=0;k<NumeroDeGolfinhos;k++){
            if(grafo.list_adj[k].primeiro->conteudo == ref_v->conteudo){
                subref = grafo.list_adj[k].primeiro;
                break;
            }
        }
        t->v2 = subref->conteudo;//salvando v2 em caso de possível formação de triângulo
        subref_v = subref->proximo;
        for(l=0;l<subref->grau;l++){
            //percorrer a lista de vizinhos de subref
            //capturar o ponteiro de subref_v e salvar em subsubref
            for(k=0;k<NumeroDeGolfinhos;k++){
                if(grafo.list_adj[k].primeiro->conteudo == subref_v->conteudo){
                    subsubref = grafo.list_adj[k].primeiro;
                    break;
                }
            }
            //verificar se na lista de vizinhos de subsubref há ref
            subsubref_v = subsubref->proximo;
            for(k=0;k<subsubref->grau;k++){
                if(subsubref_v->conteudo == ref->conteudo){
                    t->v3 = subsubref->conteudo;//formado o triângulo
                    triangulos = inserir_lista_t(triangulos,t);
                    triangulos.ti++;
                    break;
                }
                subsubref_v = subsubref_v->proximo;
            }
            subref_v = subref_v->proximo;
        }
        //percorrer a lista de vizinhos de ref_v
        ref_v = ref_v->proximo;
    }
    return (triangulos.ti/2);
}
void coef_aglomeracao(Grafo grafo){
    int i,ti,ni,num,den;
    float c,c_medio = 0.0;
    Lista_T triangulos[NumeroDeGolfinhos];
    system("clear");
    for(i=0;i<NumeroDeGolfinhos;i++){
        ni = grafo.list_adj[i].primeiro->grau; 
        ti = busca_triangulo(grafo,i);
        num = 2*ti; den = ni*(ni-1);
        if(den != 0)
            c = (float)num/(float)den;
        else c = 0.000;
        c_medio += c;
        printf("|%d| -> c = %.3f\n",grafo.list_adj[i].primeiro->conteudo,c);
    }
    c_medio /= (float)NumeroDeGolfinhos;
    grafo.coef_medio = c_medio;
    printf("coef_medio = %.3f\n",grafo.coef_medio);
}