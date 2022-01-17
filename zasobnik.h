#ifndef ZASOBNIK_H_INCLUDED
#define ZASOBNIK_H_INCLUDED


#include <stdio.h>
#include <stdlib.h>
#include "structures.h"

typedef struct t_zaznam{
    struct t_zaznam* next;
    token_t data;
} t_zaznam;

typedef struct {
    t_zaznam* first;
} t_zasob;

 

void zas_init(t_zasob* zasobnik);
RreturnWalues zas_push(t_zasob* zasobnik,token_t token);
RreturnWalues zas_pop(t_zasob* zasobnik, token_t* token);
RreturnWalues zas_top(t_zasob* zasobnik, token_t* token);




#endif // ZASOBNIK_H_INCLUDED
