#include <stdio.h>
#include "tadbasics/graph.h"


int main() {

    Graph dmap; // Grafo que representa o diagrama de disciplinas.
    List A = NULL; // Lista contendo os valores da ordenação topológica.
    int n;
    unsigned short d, pr, orig, dest; // Vértices do grafo.

    scanf("%d", &n);
    while (n > 0) {
        scanf("%hu %hu", &d, &pr);
        dmap = g_init(d);
        while (pr > 0) {
            scanf("%hu %hu", &orig, &dest);
            g_insert_edge(dmap, orig, dest);
            pr--;
        }
        //g_print(dmap);
        A = g_topological_sorting(dmap);
        if (A != NULL)
            ic_print(A);
        else
            printf("Ciclo!.\n");
        g_destroy(&dmap);
        ic_clear(&A);
        n--;
    }

    return 0;
}
