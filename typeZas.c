
#include "typeZas.h"


RreturnWalues typZas_init(t_typeZas* zas){
    zas = NULL;

}

type_t redukce(scanerTyp in){
    switch (in){
    case INTEGER_KW:
        return INTEGER_T;
    case NUMBER_KW:
        return NUMBER_T;
    case STRING_KW:
        return STRING_T;
    default:
        return NIL_T;
    }
}

RreturnWalues typZas_push(t_typeZas* zas, type_t typ){
    t_typeZas* tmp = malloc(sizeof(t_typeZas));
    if(tmp == NULL){
        return ERROR_ALLOCATION;
    }
    tmp->typ = typ;
    tmp->next = zas;
    zas = tmp;
    return OK_CHAR_APP;
}

type_t typZas_pop(t_typeZas* zas){
    if(zas == NULL){
        return NIL_T;
    }
    type_t typTmp = zas->typ;
    t_typeZas* tmp = zas->next;
    free(zas);
    zas = zas->next;
    return typTmp;
    /*
    switch(typTmp){
        case NIL_T:       
        case INTEGER_T:
        case NUMBER_T:
        case STRING_T:
        case BOOL_T :
    }
   */ 
}

bool typZas_isEmpty(t_typeZas* zas){
    return zas == NULL;
}