//
// Created by Blue on 29/04/2016.
//

#ifndef TP4_GRAPH_H
#define TP4_GRAPH_H


#include "cell.h"

/* DAG */

typedef struct _graph* Graph;


Graph g_init(const unsigned short n);

void g_destroy(Graph *G);

int g_vertex_is_valid(const unsigned short u, Graph G);

void g_insert_edge(Graph G, const unsigned short u, const unsigned short v);

void g_remove_edge(Graph G, const unsigned short u, const unsigned short v);

List g_topological_sorting(Graph G);

void g_print(Graph G);


#endif //TP4_GRAPH_H
