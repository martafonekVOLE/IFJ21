#ifndef TYPEZAS_H_INCLUDED
#define TYPEZAS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "structures.h"
#include "symtable.h"


typedef struct t_typeZas{
    struct t_typeZas* next;
    type_t typ;
}t_typeZas;

//typedef struct{
//    t_typeZasItem* first;
//}t_typeZas;
 
typedef enum token_type_t scanerTyp;


RreturnWalues typZas_init(t_typeZas* zas);

RreturnWalues typZas_push(t_typeZas* zas, type_t typ);

type_t redukce(scanerTyp in);

type_t typZas_pop(t_typeZas* zas);

bool typZas_isEmpty(t_typeZas* zas);

//void typZas_dest();

#endif // TYPEZAS_H_INCLUDED

