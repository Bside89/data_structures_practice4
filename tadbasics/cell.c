//
// Created by Blue on 28/02/2016.
//

#include "cell.h"
#include "xcpt.h"
#include <stdio.h>
#include <stdlib.h>


/* F: Cria uma nova célula da lista encadeada.
 * */
static Cell* ic_alloc(const unsigned short val) {

    Cell *c = malloc(sizeof(Cell));
    if (c == NULL)
        xcpt(ERROR_ALLOC);
    else
        c->info = val;
    return c;
}


/* F: Dado uma lista ordenada 'c' e número 'val', a função retorna o
 * endereço de memória da ÚLTIMA CÉLULA cujo valor é menor a 'val'.
 * Caso nenhum valor menor a 'val' seja encontrado a função retorna NULL.
 * Caso todos os valores sejam menores a 'val', a função retorna a
 * última célula da lista.
 * */
static Cell* ic_get_ref(const unsigned short val, Cell *c) {

    Cell *it = c;
    if (it == NULL || it->info >= val)
        return NULL;
    while (it->next != NULL && it->next->info < val)
        it = it->next;
    return it;
}


/* F: Insere uma nova célula no início da lista 'c'.
 * */
Cell* ic_insert_begin(const unsigned short val, List *L) {
    return ic_insert(val, NULL, L);
}


/* F: Insere uma nova célula no fim da lista.
 * */
Cell* ic_insert_end(const unsigned short val, List *L) {

    if (L == NULL)
        return NULL;
    if (*L == NULL)
        return ic_insert_begin(val, L);
    Cell *it = *L;
    while (it->next != NULL) // Garante a inserção no fim.
        it = it->next;
    return ic_insert(val, it, L); // it' é a última célula.
}


/* F: Insere uma nova célula na lista encadeada L,
 * imediatamente após a célula de referência 'refcell'.
 * */
static Cell* ic_insert(const unsigned short val, Cell *refcell, List *L) {

    if (refcell != NULL && refcell->next != NULL)
        if (refcell->next->info == val) // O valor já está na lista?
            return NULL;
    Cell *newcell = ic_alloc(val);
    if (refcell == NULL) {// Inserção no início.
        newcell->next = *L;
        *L = newcell;
    } else { // Inserção no meio ou no fim.
        newcell->next = refcell->next;
        refcell->next = newcell;
    }
    return newcell;
}


/* F: Insere ordenadamente uma nova célula de valor 'val' na lista 'c'.
 * Aqui, 'refcell' é a célula imediatamente anterior à que será inserida.
 * */
void ic_insertion_sort(const unsigned short val, List *L) {

    Cell *refcell = ic_get_ref(val, *L);
    if (refcell != NULL && refcell->info == val) // O valor já está na lista?
        return;
    ic_insert(val, refcell, L);
}


/* F: Retorna o endereço de memória da célula em 'c' contendo o
 * valor 'val'. Retorna NULL caso contrário.
 * */
Cell* ic_search(const unsigned short val, Cell *c) {

    Cell *it = c;
    while (it != NULL) {
        if (it->info == val)
            break;
        if (it->info > val) // A função extrapolou a lista?
            return NULL;
        it = it->next;
    }
    return it;
}


/* F: Remove uma célula de valor 'val' da lista 'L'.
 * */
void ic_remove(const unsigned short val, List *L) {

    Cell *it = *L, *removed = ic_search(val, *L);

    if (removed == NULL)
        return;
    if (removed == *L) // O valor está no início da lista?
        *L = removed->next;
    else {
        while (it->next != removed) // Busca a célula anterior à removida.
            it = it->next;
        it->next = removed->next;
    }
    free(removed);
}


/* F: Remove todas as células da lista 'L'.
 * */
void ic_clear(List *L) {

    if (L == NULL)
        return;
    Cell *it1 = *L, *it2; // Iteradores que percorrerão a lista.
    while (it1 != NULL) {
        it2 = it1;
        it1 = it1->next;
        free(it2);
    }
    *L = NULL;
}


/* F: Função auxiliar que imprime os elementos de uma lista 'L'.
 * */
void ic_print(List L) {

    if (L == NULL) {
        printf("Empty.");
        return;
    }
    Cell *it = L;
    while (it->next != NULL) {
        printf("%d => ", it->info);
        it = it->next;
    }
    printf("%d.\n", it->info);
}
