#include "symtable.h"

void htab_display(htab_t* htab) {
   int i = 0;
   
   for(i = 0; i<HTAB_MAX; i++) {
      htabItem_t *tmp;
      if((*htab)[i] != NULL){
          tmp = (*htab)[i];
          int c = 0;
          while(tmp != NULL){
             printf("item %d: ALLOCATED ", i+c);
             tmp = tmp->next;
             c++;
          }
          printf("\n");
      }
          
      else
         printf("item %d: ~~ \n", i);
   }
	
   printf("\n");
}



void htab_display_active(htab_t* htab) {
   int i = 0;
	htabItem_t *tmp;
   for(i = 0; i<HTAB_MAX; i++) {
      if((*htab)[i] != NULL){
          tmp = (*htab)[i];
          int c = 0;
          while(tmp != NULL){
             if(c != 0){
                printf("\t -> ");
             }
             printf("item %d: %s ", i+c, tmp->key);
             tmp = tmp->next;
             c++;
          }
          printf("\n");
      }
   }
   printf("\n");
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
   else if(num == 5){
      printf("UNDEFINED\n");
   }
   else{
      printf("%d - not defined as type\n", num);
   }
}

void htab_display_data(data_t* data){
   printf("Defined: ");
   if(data->defined == true){
      printf("True\n");
   }
   else if(data->defined == false){
      printf("False\n");
   }
   printf("\n");

   printf("Declared: ");
   if(data->declared == true){
      printf("True\n");
   }
   else if(data->declared == false){
      printf("False\n");
   }
   printf("\n");

   printf("Is NILL: ");
   if(data->isnil == true){
      printf("True\n");
   }
   else if(data->isnil == false){
      printf("False\n");
   }
   printf("\n");

   printf("Name:  ");
   if(data->id == NULL){
      printf("NULL\n");
   }
   else{
      printf("%s\n", data->id);
   }
   printf("\n");

   printf("VARIABLE TYPE: ");
   htab_print_type(data->var_type);
   printf("\n");

   //input types
   printf("INPUT TYPES:\n");
   if(data->input_type != NULL){         
      for(int i = 0; i < data->input_type_len; i++){
         printf("No. %d: ",i);
         htab_print_type(data->input_type[i]);
      }
   }
   printf("INPUT TYPE LEN:");
   printf("%d\n", data->input_type_len);
   printf("\n");
   //output types
   printf("OUTPUT TYPES:\n");
   if(data->output_type != NULL){
      for(int i = 0; i < data->output_type_len; i++){
         printf("No. %d: ",i);
         htab_print_type(data->output_type[i]);
      }
   }
   printf("OUTPUT TYPE LEN:");
   printf("%d\n", data->output_type_len);
   printf("\n");

   printf("INPUT ID's\n");
   if(data->input_id != NULL){
      printf("In input cycle\n");
      for(int i = 0; i < data->input_id_len; i++){
         printf("No. %d: %s\n", i, data->input_id[i]);
      }
   }
   printf("INPUT ID LEN:");
   printf("%d\n", data->input_id_len);
   printf("\n");
}

void add_20_items(htab_t *htab){
   htab_add(htab, "polozka1");
   htab_add(htab, "polozka2");
   htab_add(htab, "polozka3");
   htab_add(htab, "polozka4");
   htab_add(htab, "polozka5");
   htab_add(htab, "polozka6");
   htab_add(htab, "polozka7");
   htab_add(htab, "polozka8");
   htab_add(htab, "polozka9");
   htab_add(htab, "polozka10");
   htab_add(htab, "polozka11");
   htab_add(htab, "polozka12");
   htab_add(htab, "polozka13");
   htab_add(htab, "polozka14");
   htab_add(htab, "polozka15");
   htab_add(htab, "polozka16");
   htab_add(htab, "polozka17");
   htab_add(htab, "polozka18");
   htab_add(htab, "polozka19");
   htab_add(htab, "polozka20");
}

int main(){

    htab_t *htab = htab_init();
    
   //  printf("------ prázdná tabulka na začátku: -----\n");
   //  htab_display(htab);

   // unsigned hello_key = hash_function("hello");
   // unsigned bye_key = hash_function("bye");
   // unsigned cau_key = hash_function("cau");
   printf("Count empty table: \n");
   printf("%d\n", htab_count(htab));
   htab_add(htab, "hello");
   //  printf("hash key for hello: %d\n\n", hello_key);

   //  htab_add(htab, "bye");
   //  printf("hash key for bye: %d\n\n", bye_key);

   //  htab_add(htab, "cau");
   //  printf("hash key for bye: %d\n\n", cau_key);

   printf("\n------ PRIDAVAM DVACET POLOZEK ------\n");
    add_20_items(htab);
   



    printf("\n------ Celá tabulka: ------\n");
    htab_display(htab);

    printf("\n------ Alokované položky: ------\n");
    htab_display_active(htab);


   /**
    * @brief nastavení tabulky
    * 
    */
    htab_set_data(htab, "hello", true, true, "NAME", 3);
    htab_add_input_type(htab, "hello", STRING_T);
    htab_add_return_type(htab, "hello", INTEGER_T);

    htab_add_input_type(htab, "hello", NUMBER_T);
    htab_add_return_type(htab, "hello", NUMBER_T);

    htab_add_input_id(htab, "hello", "AHOJ");
    htab_add_input_id(htab, "hello", "CAU");
    htab_add_input_id(htab, "hello", "MEJSE");
    htab_add_input_id(htab, "hello", "MEJSE");
    htab_add_input_id(htab, "hello", "MEJSE");
    htab_add_input_id(htab, "hello", "MEJSE");
    htab_add_input_id(htab, "hello", "MEJSE");
    htab_add_input_id(htab, "hello", "MEJSE");
    htab_add_input_id(htab, "hello", "MEJSE");
    htab_add_input_id(htab, "hello", "MEJSE");
    htab_add_input_id(htab, "hello", "MEJSE");


   htab_add_input_type(htab, "hello", 5);
   
   htab_add_input_type(htab, "hello", NUMBER_T);


    data_t* hello_data = htab_get_data(htab, "hello");

   /**
    * @brief Kontrola a výpis dat v tabulce
    * 
    */
   printf("\n -----------KONTROLA DAT ----------\n");

    if(hello_data != NULL){    
      htab_display_data(hello_data);
    }
    else{
       printf("RETRUNED NULL FROM DATA!\n");
    }

   /**
    * @brief součet prvků tabulky
    * 
    */
   printf("Počet prvků: %d\n", htab_count(htab));

   printf("FIND TEST: polozka4 - should be present \n");
   htabItem_t* found = htab_find(htab, "polozka4");
   if(found!=NULL){
      printf("\t FOUND :)\n");
   }
   else{
      printf("\t NOT FOUND :(\n");
   }

   /**
    * @brief uvolnění tabulky
    * 
    */
    printf("----- Uvolnění tabulky ------\n");
    htab_free(htab);
    
   /**
 * @brief součet prvků tabulky
 * 
 */
   
    return 0;
}