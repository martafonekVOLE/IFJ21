/**
 * @file tabstack.h
 * @author Matěj Konopík
 * @brief Stack of symbol tables for IFJ21 compiler
 * @version 0.1
 * @date 2021-11-24
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef TABSTACK_H_INCLUDED
#define TABSTACK_H_INCLUDED
#include "symtable.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct tabstackItem{
    htab_t *tab;
    int current_items;
    int items_lower; 
}tsItem_t;

typedef struct tsStack{
    tsItem_t *stack_ptr; 
    int top_index;
}tsStack_t;

//vytvoří stack
tsStack_t *ts_init();

//přidá tabulku na stack, načte
htabItem_t *ts_create_item_top(tsStack_t *stack, char *key);

tsItem_t *ts_push_existing(tsStack_t *stack, htab_t* htab);

tsItem_t *ts_push_fresh(tsStack_t *stack);

bool ts_pop(tsStack_t *stack);

int get_itemcount_bellow(tsStack_t *stack);

int get_itemcount_top(tsStack_t *stack);

tsItem_t *ts_top(tsStack_t *stack);

htabItem_t *ts_find_item_top(tsStack_t *stack, char *key);

htabItem_t *ts_find_item(tsStack_t *stack, char *key);

bool ts_delete_stack(tsStack_t *stack);

int get_lower(tsStack_t *stack);

#endif //TABSTACK_H_INCLUDED