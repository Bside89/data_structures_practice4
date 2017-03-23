//
// Created by Blue on 28/02/2016.
//

#include "stack.h"
#include "cell.h"
#include "xcpt.h"
#include <stdlib.h>
#include <stdio.h>


#define ERROR_EMPTY_STACK "Error: Stack is empty."


struct _stack {
    Cell *top;
};


/* F: Inicializa uma pilha 'P' vazia.
 * */
Stack st_init(void) {
    Stack P = malloc(sizeof(struct _stack));
    P->top = NULL;
    return P;
}


/* F: Verifica se a pilha 'P' é uma pilha vazia.
 * */
int st_is_empty(Stack source) {
    return source == NULL || source->top == NULL;
}


/* F: Insere na pilha 'P' um elemento 'val'.
 * */
void st_push(const unsigned short val, Stack P) {
    ic_insert_begin(val, &(P->top));
}


/* F: Remove da pilha 'P' um elemento e o devolve.
 * */
unsigned short st_pop(Stack P) {

    if (st_is_empty(P))
        return (unsigned short) xcpt(ERROR_EMPTY_STACK);
    unsigned short val = P->top->info;
    ic_remove(val, &(P->top));
    return val;
}


/* F: Devolve o elemento no topo da pilha 'P'.
 * */
unsigned short st_get_top(Stack P) {
    if (st_is_empty(P))
        return (unsigned short) xcpt(ERROR_EMPTY_STACK);
    return P->top->info;
}


/* F: Recebe uma pilha 'P' e devolve a sua quantidade de elementos.
 * */
size_t st_size(Stack P) {

    Cell *it;
    size_t counter = 0;
    for (it = P->top; it != NULL; it = it->next)
        counter++;
    return counter;
}


/* F: Função auxiliar que recebe uma pilha 'P' e imprime na tela todos
 * os dados contidos nela.
 * */
void st_print(Stack P) {

    Cell *it;
    putchar('(');
    if (st_is_empty(P))
        putchar(' ');
    else for (it = P->top; it != NULL; it = it->next) {
        printf("%hu", it->info);
        if (it->next != NULL)
            printf(", ");
    }
    puts(")");
}


/* F: Destrói (desaloca da memória) toda a memória alocada pelo TAD Stack.
 * */
void st_destroy(Stack *P) {
    ic_clear(&((*P)->top));
    free(*P);
    *P = NULL;
}
