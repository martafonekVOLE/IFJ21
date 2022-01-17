
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "charAppender.h"
#include "scanner.h"

#include "semantika.h"
#include "typeZas.h"
#include "structures.h"
#include "codegen.h"
//TO DO kolize nazvu fc a prom
/* Zkontroluje ID fc pro definici, pripadne ho prida do tabulky
*/
//htab_t * fc_table;
//tsStack_t * prom_table;

void sem_init(htab_t** fc_table, tsStack_t** prom_table){
    
    *fc_table = htab_init();
    *prom_table = ts_init();
}

void sem_destroy(htab_t** fc_table, tsStack_t** prom_table){
    htab_free(*fc_table);
    ts_delete_stack(*prom_table);
    
    //TO DO destructory
}
void sem_push(htab_t** fc_table, tsStack_t** prom_table){
    ts_push_fresh(*prom_table);
}
void sem_pop(htab_t** fc_table, tsStack_t** prom_table){
    ts_pop(*prom_table);
}
#ifdef DEBUGER
#include <stdio.h>
#endif
bool sem_FCIdDef(token_t token, htab_t** fc_table, tsStack_t** prom_table){//TO DO co kdyz bude prvne identifikator promene a pak fc?
    //fprintf(stderr, "PANI\n");
    htabItem_t* akt = htab_find(*fc_table, token.attribute.text);
    //fprintf(stderr, "PANI22\n");
    if(NULL != akt){
        //fprintf(stderr, "PANI33\n");
        if(!(akt->data->defined)){
            akt->data->defined = true;
        }
        else{
            //fprintf(stderr, "PANI\n");
            return false;
        }
        //fprintf(stderr, "PANI\n");
        return true;
    }
    //fprintf(stderr, "PANI4\n");
    
    
    // TO DO co je string id a k cemu je
    //char gen_id[50]; 
    //gen_id[0] = '\0'; 
    //fprintf(stderr, "PANI5JJJJ%d\n",get_itemcount_bellow(*prom_table) +  get_itemcount_top(*prom_table));

    //snprintf(gen_id, 49, "%48d", get_itemcount_bellow(*prom_table) +  get_itemcount_top(*prom_table));
    //htab_add(token.attribute.text);
    //fprintf(stderr, "PANI6\n");
    htab_add(*fc_table, token.attribute.text);
    htab_set_data(*fc_table, token.attribute.text, true, false, token.attribute.text, NIL_T);//Nil protoze to nevyuzivam
    #ifdef DEBUGER
    if(htab_find(*fc_table, token.attribute.text) == NULL ){
        fprintf(stderr, "\nALDE NE\n");
        //exit( 250);
    }
    #endif
    return true;
}

bool sem_FCIdDecler(token_t token, htab_t** fc_table, tsStack_t** prom_table){//TO DO co kdyz bude prvne identifikator promene a pak fc?
    htabItem_t* akt = htab_find(*fc_table, token.attribute.text);
    if(NULL != akt){
        if(!akt->data->declared){
            akt->data->declared = true;
        }
        else{
            return false;
        }
        return true;
    }
    //char gen_id[50];
    //gen_id[0] = '\0'; 
    //snprintf(gen_id, 49, "%49d", get_itemcount_bellow(*prom_table) +  get_itemcount_top(*prom_table));
    //htab_add(token.attribute.text);
    htab_add(*fc_table, token.attribute.text);
    htab_set_data(*fc_table, token.attribute.text, true, false, token.attribute.text, NIL_T);
    return true;
}

/* Prida ID pro prom, jeli na teto urovni vyrobeno tak nastane chyba
*/
#define UNUSED
#ifndef UNUSED
bool sem_PromDef(token_t token, htab_t** fc_table, tsStack_t** prom_table, /*int number,*/ type_t typ, bool* chybaPameti){ //TO DO rozpoznani definovaneho a declarovaneho
    htabItem_t* akt = ts_find_item_top(*prom_table, token.attribute.text);
    *chybaPameti = false;
    if(NULL == akt){
        if(!sem_PromDecler(token, fc_table, prom_table, typ, chybaPameti)){
            return false;
        }   
        
        akt->data->defined = true;
        akt->data->declared = true;
        akt->data->var_type = typ;
        
        return true;
    }
    //if(akt->data->defined)
    return true;
}
#endif //UNUSED
/* Prida ID pro prom, jeli na teto urovni vyrobeno tak nastane chyba
*/
//byla sem_PromDecler
bool sem_PromDef(char* name, htab_t** fc_table, tsStack_t** prom_table, /*int number,*/ type_t typ, bool* chybaPameti,bool nula, bool nil){//TO DO rozpoznani definovaneho a declarovaneho
//kdy vubec pouzit tu fc, hledat vsude
    htabItem_t* akt = ts_find_item_top(*prom_table, name);
    
    *chybaPameti = false;
    if(akt != NULL){ 
        return false;
    }
    #ifdef DEBUGER
        fprintf(stderr, "Alan\n");
    #endif
    if(NULL != akt){
        #ifdef DEBUGER
            fprintf(stderr, "jouda\n");
        #endif
        //Je v tabulce*chybaPameti = true;
        return false;
    }
    #ifdef DEBUGER
        fprintf(stderr, "%p ulma %s\n",*prom_table,name);
    #endif
    akt = ts_create_item_top(*prom_table, name);//CHYBA dvoji tvoreni nahore
    if(akt == NULL){
        #ifdef DEBUGER
        fprintf(stderr, "ZaseNetvori\n");
        #endif
        *chybaPameti = true;
        return false;
    }
    #ifdef DEBUGER
        fprintf(stderr, "Hospoda\n");
    #endif
    akt->data->defined = true;//redundantni
    akt->data->declared = true;//redundantni
    akt->data->var_type = typ;
    akt->data->isnil = nil;
    akt->data->number = 1;//Protoze jsem si neobjednal isZero
    if(nula){
        akt->data->number = 0;    
    }
        //akt->data->isnil = true;
        /*akt->data->number = number;*/
    //#ifdef DEBUGER
    //fprintf(stderr, "\nALDE JO\n");
    //#endif
    #ifdef DEBUGER
    strcpy(velmiMalePoleZnaku,name);
    fprintf(stderr, "%p ;%s;TOZ\n",ts_find_item_top(*prom_table,name),name);
    fprintf(stderr, "%p ;%s; %d##########################\n", ts_find_item_top(*prom_table,velmiMalePoleZnaku),velmiMalePoleZnaku, ts_top(*prom_table)->current_items );
    #endif
    return true;
}


//Overi ze se jedna o declarovanou fc akceptuje i defaultni fc
bool sem_isFC(token_t token,htab_t** fc_table, tsStack_t** prom_table){
    htabItem_t* akt = htab_find(*fc_table, token.attribute.text);
    if(akt == NULL){
        return false;
    }
    return true;
}

//Overi ze se jedna o declarovanou prom
bool sem_isProm(token_t token, htab_t** fc_table, tsStack_t** prom_table){
    htabItem_t* akt = ts_find_item(*prom_table, token.attribute.text);
    if(NULL == akt){
        return false;
    }
    //if(akt->data->defined)
    return true;
}

//Kontrola pri tvorbe fc. pro vstup, pouze kontrola
bool sem_addInputControl(htab_t** fc_table, char* nameFc, type_t type, int kolikatyIndex, bool* chybaAlok){
    
    data_t *fc = htab_get_data(*fc_table, nameFc);
    *chybaAlok = false;
    if(fc->declared && fc->defined){
        if(kolikatyIndex + 1 > fc->input_type_len)
        {
            return false;
        }
        return (fc->input_type[kolikatyIndex] == type);
        //kontrola;
    }
    else{
        #ifdef DEBUGER
            fprintf(stderr, "zajimava  %d %d;\n",htab_find(*fc_table, nameFc)->data->input_type_len,kolikatyIndex);
            fprintf(stderr, "data %d;%d;\n",htab_find(*fc_table, nameFc)->data->input_type[0], htab_find(*fc_table, nameFc)->data->input_type[1]);
        #endif
        //tvorba
        //*chybaAlok = !htab_add_input_type(*fc_table, nameFc, type); //Tuto operaci delam uz predtim
        return true;
    }
}

//Kontrola pri tvorbe fc. pro vystup
bool sem_addOutputControl(htab_t** fc_table, char* nameFc, type_t type, int kolikatyIndex, bool* chybaAlok){
    data_t *fc = htab_get_data(*fc_table, nameFc);
    *chybaAlok = false;
    if(fc->declared && fc->defined){
        if(kolikatyIndex + 1 > fc->output_type_len)
        {
            return false;
        }
        return (fc->output_type[kolikatyIndex] == type);
        //kontrola;
    }
    else{
        //tvorba
        *chybaAlok = !htab_add_return_type(*fc_table, nameFc, type);
        return true;
    }
}
//kontrola u return
bool sem_checkReturn(htab_t** fc_table, char* nameFc, type_t type, int kolikatyIndex){
    data_t *fc = htab_get_data(*fc_table, nameFc);
    if(kolikatyIndex + 1 > fc->output_type_len)
    {
        return false;
    }
    if(!(fc->output_type[kolikatyIndex] == type)){
        if(fc->output_type[kolikatyIndex] == NUMBER_T && type == INTEGER_T){
            int2floats();
            return true;
        }
    }
    return true;
        
}


