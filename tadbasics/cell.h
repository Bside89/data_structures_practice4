//
// Created by Blue on 28/02/2016.
//

#ifndef TP2_CELL_H
#define TP2_CELL_H


typedef struct _cell {
    unsigned short info;
    struct _cell *next;
} Cell;


typedef Cell* List;


static Cell* ic_alloc(const unsigned short val);

static Cell* ic_get_ref(const unsigned short val, Cell *c);

Cell* ic_insert_begin(const unsigned short val, List *L);

Cell* ic_insert_end(const unsigned short val, List *L);

static Cell* ic_insert(const unsigned short val, Cell *refcell, List *L);

void ic_insertion_sort(const unsigned short val, List *L);

Cell* ic_search(const unsigned short val, Cell *c);

void ic_remove(const unsigned short val, List *L);

void ic_clear(List *L);

void ic_print(List L);


#endif //TP2_CELL_H
