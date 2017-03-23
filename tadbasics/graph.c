//
// Created by Blue on 29/04/2016.
//

#include "graph.h"
#include "stack.h"
#include "xcpt.h"
#include <stdlib.h>
#include <stdio.h>


#define G_GRAPH_NOT_FOUND "Error: Graph is null."


struct _graph {
    unsigned short vertex;
    List *adj; // Vetor de 'vertex' elementos com as lista de adjacências.
};


/* As cores são utilizadas para marcar quando um vertice ainda não foi visitado (BRANCO),
 * está sendo visitado (CINZA) ou já foi visitado (PRETO).
 * */
typedef enum colors {WHITE = 0, GRAY, BLACK} g_color_t;


static int g_depht_first_search(Graph G, const unsigned short v, Stack P, g_color_t *c);


/* F: Inicializa o TAD Graph.
 * */
Graph g_init(const unsigned short n) {
    Graph G = malloc(sizeof(struct _graph));
    G->vertex = n;
    G->adj = calloc(n, sizeof(List));
    return G;
}


/* F: Verifica se o vértice 'u' em 'G' é um vértice válido.
 * */
int g_vertex_is_valid(const unsigned short u, Graph G) {
    return u >= 0 && u < G->vertex;
}


/* F: Destrói (desaloca da memória) toda a memória alocada pelo
 * TAD Graph. */
void g_destroy(Graph *G) {
    if (G == NULL || *G == NULL)
        return;
    int i;
    for (i = 0; i < (*G)->vertex; i++)
        ic_clear(&((*G)->adj[i]));
    free((*G)->adj);
    free(*G);
    *G = NULL;
}


/* F: Insere no grafo 'G' uma aresta ligando 'u' ao 'v'.
 * */
void g_insert_edge(Graph G, const unsigned short u, const unsigned short v) {
    if (!g_vertex_is_valid(u, G) || !g_vertex_is_valid(v, G))
        return;
    ic_insertion_sort(v, &G->adj[u]);
}


/* F: Remove em 'G' uma aresta ligando 'u' ao 'v'.
 * */
void g_remove_edge(Graph G, const unsigned short u, const unsigned short v) {
    if (!g_vertex_is_valid(u, G) || !g_vertex_is_valid(v, G))
        return;
    ic_remove(v, &G->adj[u]);
}


/* F: Função auxiliar que imprime na tela os dados do grafo 'G'.
 * */
void g_print(Graph G) {
    if (G == NULL)
        return;
    Cell *it;
    int i;
    for (i = 0; i < G->vertex; i++) {
        printf("( %d ) --> ", i);
        it = G->adj[i];
        while (it != NULL) {
            printf("%d", it->info);
            if (it->next != NULL)
                printf(" -- ");
            it = it->next;
        }
        putchar('\n');
    }
}


/* F: Recebe o grafo 'G' e devolve uma lista encadeada contendo os vértices
 * de 'G' ordenados topologicamente.
 * */
List g_topological_sorting(Graph G) {

    if (G == NULL)
        xcpt(G_GRAPH_NOT_FOUND);
    List L = NULL;
    Stack P = st_init();
    g_color_t *c = calloc(G->vertex, sizeof(g_color_t));
    unsigned short i;
    
    for (i = 0; i < G->vertex; i++) {
        if (c[i] == WHITE && g_depht_first_search(G, i, P, c)) {
            st_destroy(&P); // Caso haja ciclo, a pilha de visitação será esvaziada.
            break;
        }
    }
    while (!st_is_empty(P)) {
        ic_insert_end(st_pop(P), &L);    
    }
    st_destroy(&P);
    free(c);
    return L;
}


/* F: Função que recebe que recebe um grafo 'G' e um vértice 'v' e calcula o percurso
 * em profundidade obtido a partir de 'v'. Os vértices visitados neste percurso
 * são inseridos na Lista 'L' em ordem de visitação.
 * A função devolve 1 se há um ciclo alcançável a partir de v e 0 caso contrário.
 * */
static int g_depht_first_search(Graph G, const unsigned short v, Stack P, g_color_t *c) {

    List adj;
    int cycle = 0;

    if (c[v] == GRAY) /* Ciclo */
        return 1;
    if (c[v] == WHITE) {
        c[v] = GRAY;
        // G->adj[v] é a lista de adjacência do vértice 'v' em 'G'.
        for (adj = G->adj[v]; adj != NULL; adj = adj->next)
            cycle = (cycle || g_depht_first_search(G, adj->info, P, c));
        c[v] = BLACK;
        st_push(v, P);
    }
    return cycle;
}
