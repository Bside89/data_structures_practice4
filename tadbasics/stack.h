//
// Created by Blue on 28/02/2016.
//

#ifndef TP2_STACK_H
#define TP2_STACK_H


#include <stddef.h>


typedef struct _stack * Stack;


Stack st_init(void);

int st_is_empty(Stack source);

void st_push(const unsigned short val, Stack P);

unsigned short st_pop(Stack P);

unsigned short st_get_top(Stack P);

size_t st_size(Stack P);

void st_print(Stack P);

void st_destroy(Stack *P);


#endif //TP2_STACK_H
