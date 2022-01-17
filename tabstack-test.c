/**
 * @file tabstack-test.c
 * @author Matěj Konopík
 * @brief Test bench pro stack tabulek pro skladování symbolů překladače jazyka IFJ 21
 * @date 2021-11-24
 * 
 * @copyright Copyright Matěj Konopík (c) 2021
 * 
 */

#include "tabstack.h"

bool print_table(htab_t *htab);
void print_stack(tsStack_t *stack);
void htab_print_type(int num);
void htab_display_data(data_t* data);


int main(int argc, char **argv){
    //STACK
    tsStack_t *stack = ts_init(stack);

    
    printf("Tablework 0\n");
    //TABULKA 1
    htab_t *htab1 = htab_init();
    
    htab_add(htab1, "ITEM1.1");
    htab_add(htab1, "ITEM1.2");

    //TABULKA 2
    htab_t *htab2 = htab_init();
    htab_add(htab2, "ITEM2.1");
    htab_add(htab2, "ITEM2.2");

    htab_t *htab3 = htab_init();
    htab_add(htab3, "ITEM3.1");
    htab_add(htab3, "ITEM3.2");

    printf("Tablework 1\n");


    //PUSH NA STACK
    printf("TEST: pushing existing 1\n");
    ts_push_existing(stack, htab1);

    printf("TEST: pushing existing 2\n");
    ts_push_existing(stack, htab2);

    //PUSH FRESH TABULKY
    printf("TEST: Pushing 1 fresh ..\n");
    ts_push_fresh(stack);
    printf("TEST: Fresh pushed. 1\n");  
    
    printf("TEST: Pushing fresh 2..\n");
    ts_push_fresh(stack);
    printf("TEST: Fresh 2 pushed. \n"); 

    printf("TEST: Pushing fresh 3..\n");
    ts_push_fresh(stack);
    printf("TEST: Fresh 3 pushed. \n");   

    printf("TEST: pushing existing 3\n");
    ts_push_existing(stack, htab3);

    printf("\n--------------------------------------\n\t\t TEST: FIND IN TOP TABLE: ITEM3.1 - should be present\n -----------------------------------\n ");
    htabItem_t *found_top = ts_find_item_top(stack, "ITEM3.1");
    printf("\tFound: assigned\n");
    if(found_top != NULL){
        htab_display_data(found_top->data);
    }
    else{
        printf("\tnot found: %p\n", found_top);
    }
    print_stack(stack);

    printf("\n--------------------------------------\n\t\t TEST: FIND IN TOP TABLE: hello - should not be present\n -----------------------------------\n ");
    found_top = ts_find_item_top(stack, "hello");
    printf("\tFound: assigned");
    if(found_top != NULL){
        htab_display_data(found_top->data);
    }
    else{
        printf("\tnot found: %p\n", found_top);
    }

    
    printf("\n--------------------------------------\n\t\t TEST: FIND IN TOP TABLE: ITEM2.2 - should be present\n -----------------------------------\n ");
    found_top = ts_find_item(stack, "ITEM2.2");
    printf("\tFound: assigned");
    if(found_top != NULL){
        htab_display_data(found_top->data);
    }
    else{
        printf("\tnot found: %p\n", found_top);
    }

    printf("\n--------------------------------------\n\t\t TEST: FIND IN TOP TABLE: pain - should not be present  \n -----------------------------------\n ");
    found_top = ts_find_item(stack, "pain");
    printf("\tFound: assigned");
    if(found_top != NULL){
        htab_display_data(found_top->data);
    }
    else{
        printf("\tnot found: %p\n", found_top);
    }


    printf("\n\n--------------------------------------\n\t\t TEST: POP ITEM\n -----------------------------------\n ");
    bool pop = ts_pop(stack);
    pop ? printf("Pop returned true\n") : printf("Pop returned false\n\n");

    

    printf("\n--------------------------------------\n\t\t TEST: GET TOP\n -----------------------------------\n ");
    tsItem_t* top = ts_top(stack);
    printf("\tTop item current items: %d, itmes lower: %d\n", top->current_items, top->items_lower);
    printf("\tTop item table: \n");
    
    if(!(print_table(top->tab))){
        printf("\t ! table is empty\n\n");
    }

    print_stack(stack);

    
    ts_pop(stack);
    ts_pop(stack);
    ts_pop(stack);
    
    printf("\n\n--------------------------------------\n\tITEM COUNT\n------------------------------------------\n");
    int cnt_top = get_itemcount_top(stack);
    int cnt_blw = get_itemcount_bellow(stack);
    printf("items in top item: %d\nitems bellow: %d\n", cnt_top, cnt_blw);

    printf("TEST: ADD ITEM TO THE TOP TABLE\n");
    ts_create_item_top(stack, "TSCIT");

    print_stack(stack);



    printf("\n\nPOP TILL EMPTY \n");
    while(stack->top_index != -1){
        ts_pop(stack);
    }



    int che = get_itemcount_bellow(stack);
    printf("TEST: ITEMS BELLOW ON EMPTY STACK: %d\n\n",che);


    

























   
   
   
   
   
   
    ts_delete_stack(stack);
    
    printf("\n\n DEALLOC'D, EXITING.\n");

    print_stack(stack);
    // printf("TEST: Finding item\n");
    // htabItem_t *found = ts_find_item(stack, "ITME1.2");
    // printf("TEST: Found item's key: %s", found->key);

    return 0;
}

bool print_table(htab_t *htab){
    htabItem_t *tmp;
    bool nonempty_flag = false;
    for(int i = 0; i < HTAB_MAX; i++){
        tmp = (*htab)[i];
        while(tmp != NULL){
            printf("\tKEY: %s\n", tmp->key);
            htab_display_data(tmp->data);
            tmp = tmp->next;
            nonempty_flag = true;
        }
    }
    return nonempty_flag;
}


void print_stack(tsStack_t *stack){
    printf("\n----------------------------------\nPRINTING STACK: STACK HAS %d ITEMS.\n----------------------------------\n", (stack->top_index + 1));
    int index = stack->top_index;
    while(index != -1){
        if((stack->stack_ptr + index)->tab != NULL){
            printf("TABLE ON INDEX %d: \n", index);
            print_table((stack->stack_ptr + index)->tab);
        }
        index--;
    }
    printf("\n----------------------------------\n\n");
}


void htab_print_type(int num){
   if(num == 0){
      printf("NUMBER\n");
   }
   else if(num == 1){
      printf("INTEGER\n");
   }
   else if(num == 2){
      printf("STRING\n");
   }
   else if(num == 3){
      printf("BOOL\n");
   }
   else if(num == 4){
      printf("NIL\n");
   }
   else{
      printf("%d - not defined as type\n", num);
   }
}

void htab_display_data(data_t* data){
   printf("\t\tDefined: ");
   if(data->defined == true){
      printf("True\n");
   }
   else if(data->defined == false){
      printf("False\n");
   }


   printf("\t\tDeclared: ");
   if(data->declared == true){
      printf("True\n");
   }
   else if(data->declared == false){
      printf("False\n");
   }


   printf("\t\tIs NILL: ");
   if(data->isnil == true){
      printf("True\n");
   }
   else if(data->isnil == false){
      printf("False\n");
   }


   printf("\t\tName:  ");
   if(data->id == NULL){
      printf("NULL\n");
   }
   else{
      printf("%s\n", data->id);
   }


   //input types
   printf("\t\tINPUT TYPES:\n");
   if(data->input_type != NULL){         
      for(int i = 0; i < data->input_type_len; i++){
         printf("\t\t\tNo. %d: ",i);
         htab_print_type(data->input_type[i]);
      }
   }

   //output types
   printf("\t\tOUTPUT TYPES:\n");
   if(data->output_type != NULL){
      for(int i = 0; i < data->output_type_len; i++){
         printf("\t\t\tNo. %d: ",i);
         htab_print_type(data->output_type[i]);
      }
   }


   printf("\t\tINPUT ID's:\n");
   if(data->input_id != NULL){
      printf("In input cycle\n");
      for(int i = 0; i < data->input_id_len; i++){
         printf("\t\t\tNo. %d: %s\n", i, data->input_id[i]);
      }
   }

}