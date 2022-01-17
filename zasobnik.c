#include <stdio.h>
#include <stdlib.h>
//#include "structures.h"
#include "zasobnik.h"



void zas_init(t_zasob* zasobnik){
    zasobnik->first = NULL;
}

RreturnWalues zas_push(t_zasob* zasobnik,token_t token){
    t_zaznam* tmp = malloc(sizeof(t_zaznam));
    if(tmp == NULL){
        return ERROR_ALLOCATION;
    }
    tmp->next = zasobnik->first;
    tmp->data = token;
    zasobnik->first = tmp;
    return OK_CHAR_APP;
}


RreturnWalues zas_pop(t_zasob* zasobnik, token_t* token){
    if(zasobnik->first == NULL){
        return ERROR_PODTECENI;
    }
    *token = zasobnik->first->data;
    t_zaznam *tmp = zasobnik->first;
    zasobnik->first = zasobnik->first->next;
    free(tmp);
    return OK_CHAR_APP;
}


RreturnWalues zas_top(t_zasob* zasobnik, token_t* token){
    if(zasobnik->first == NULL){
        return ERROR_PODTECENI;
    }
    *token = zasobnik->first->data;
    return OK_CHAR_APP;
}