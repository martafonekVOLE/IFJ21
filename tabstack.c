/**
 * @file htabstack.c
 * @author Matěj Konopík    
 * @brief Implementace funkcí zásobníku tabulek symbolů
 * @version 0.1
 * @date 2021-11-23
 * @music: Alberto Balsalm by Aphex Twin
 * 
 * Poznamky:
 * 
 * push
 * pop
 * init
 * search v top tabulce
 * search v celým - priorita těm vrchním
 * každý item má počet svých položek + počet položek všech itemů pod ní <- toto vracet funkci
 * 
 * stack - zaobalit funkce pro např. přidání prvku do top vrstvy
 * 
 */

#include "tabstack.h"

//vytvoří stack
tsStack_t *ts_init(){
    tsStack_t *stack = (tsStack_t*)malloc(sizeof(tsStack_t));
    if(stack == NULL){
        return NULL;
    }
    stack->top_index = -1;
    stack->stack_ptr = NULL;
    return stack;
}

//přidá tabulku na stack, načte její metadata 
tsItem_t *ts_push_existing(tsStack_t *stack, htab_t *htab){
    if(stack->top_index == -1){
        stack->top_index = 0;
        stack->stack_ptr = (tsItem_t*)malloc(sizeof(tsItem_t));
        stack->stack_ptr->tab = htab;
        stack->stack_ptr->current_items = htab_count(htab);
        stack->stack_ptr->items_lower = 0;
        return stack->stack_ptr;
    }

    else if(stack->top_index != -1){
        stack->top_index++;
        stack->stack_ptr = (tsItem_t*)realloc(stack->stack_ptr, sizeof(tsItem_t) * (stack->top_index + 1));
        (stack->stack_ptr + stack->top_index)->tab = htab;
        (stack->stack_ptr + stack->top_index)->current_items = htab_count(htab);
        (stack->stack_ptr + stack->top_index)->items_lower = ((stack->stack_ptr + stack->top_index -1)->current_items + (stack->stack_ptr + stack->top_index -1)->items_lower);

        return stack->stack_ptr + stack->top_index;
    }

    return NULL;
     
}

tsItem_t *ts_push_fresh(tsStack_t *stack){
    htab_t *htab = htab_init(htab);
    

    if(stack->top_index == -1){
        stack->top_index = 0;
        stack->stack_ptr = (tsItem_t *)malloc(sizeof(tsItem_t));
        stack->stack_ptr->tab = htab;
        stack->stack_ptr->current_items = 0;
        stack->stack_ptr->items_lower = 0;
        return stack->stack_ptr;
    }   
    else if(stack->top_index != -1){
        stack->top_index++;
        stack->stack_ptr = (tsItem_t *)realloc(stack->stack_ptr, sizeof(tsItem_t) * (stack->top_index + 1));
        (stack->stack_ptr + stack->top_index)->tab = htab;
        (stack->stack_ptr + stack->top_index)->current_items = 0;
        (stack->stack_ptr + stack->top_index)->items_lower = ((stack->stack_ptr + stack->top_index - 1)->current_items + (stack->stack_ptr + stack->top_index - 1)->items_lower);
        return (stack->stack_ptr +stack->top_index);
    }

    return NULL;
}

bool ts_pop(tsStack_t *stack){
    if(stack->stack_ptr == NULL || stack->top_index == -1){
        fprintf(stderr, "Warning: pop called upon empty or NULL stack\n.");
        return false;
    }
    else{
        htab_free((stack->stack_ptr + stack->top_index)->tab);
        stack->top_index--;
        stack->stack_ptr = (tsItem_t*)realloc((stack->stack_ptr), sizeof(tsItem_t) * (stack->top_index + 1));        
        return true;
    }
}

int get_itemcount_top(tsStack_t *stack){
    if(stack->top_index == -1){
        return 0;
        fprintf(stderr, "Warning: itemcount_top called upon empty stack\n.");
    }
    tsItem_t *tmp = ts_top(stack);
    return tmp->current_items;
}

int get_itemcount_bellow(tsStack_t *stack){
    if(stack->top_index == -1){
        fprintf(stderr, "Warning: itemcount_bellow called upon empty stack\n.");
        return 0;
    }
    tsItem_t *tmp = ts_top(stack);
    return tmp->items_lower;
}

htabItem_t *ts_create_item_top(tsStack_t* stack, char *key){
    tsItem_t *item = ts_top(stack);
    if(item == NULL){
        fprintf(stderr, "Warning: create item top called upon empty stack\n");
        return NULL;
    }
    htabItem_t *tab = htab_add(item->tab, key);

    return tab;
}

tsItem_t *ts_top(tsStack_t *stack){
    if(stack->top_index == -1){
        return NULL;
        fprintf(stderr, "Warning: top called upon empty stack\n");
    }
    tsItem_t *tmp = (stack->stack_ptr + stack->top_index);
    return tmp;
}

htabItem_t *ts_find_item_top(tsStack_t *stack, char *key){
    htabItem_t *tab_item;
    tsItem_t *stack_item = ts_top(stack);
    tab_item = htab_find(stack_item->tab, key);
    return tab_item;    
}

htabItem_t *ts_find_item(tsStack_t *stack, char *key){
    int index = stack->top_index;
    htabItem_t *tmp = NULL;
    while(index != -1){
        tmp = htab_find((stack->stack_ptr + index)->tab, key);
        if(tmp != NULL){
            return tmp;
        }
        index--;
    }
    return NULL;
}

bool ts_delete_stack(tsStack_t *stack){
    while(stack->top_index != -1){
        if((stack->stack_ptr + stack->top_index)->tab != NULL){
            htab_free((stack->stack_ptr + stack->top_index)->tab);
        }
        stack->top_index--;
    }
    if(stack->stack_ptr != NULL){
        free(stack->stack_ptr);
    }
    if((stack != NULL)){
        free(stack);
    }
    return NULL;
}
