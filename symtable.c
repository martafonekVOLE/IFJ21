/**
 * @file symtable.c
 * @author Matěj Konopík
 * @brief funkce pro práci s rozšířenou tabulkou rozptýlených položek pro skladování proměnných a funkcí překladače jazyka IFJ21
 * @version 1.0
 * @date 2021-11-23
 * 
 * @copyright Copyright Matěj Konpoík (c) 2021
 * 
 */
//TODO free pokud se někde nezdaří alokace ve funkci

#include "symtable.h"

int HTAB_SIZE = HTAB_MAX;


unsigned hash_function(const char *str){
    uint32_t h=0;   
    const unsigned char *p;
    for(p=(const unsigned char*)str; *p!='\0'; p++){
        h = 65599*h + *p;
    }
    return h % HTAB_SIZE;
}


htab_t *htab_init(){
  htab_t *tab = (htab_t *)malloc(sizeof(htabItem_t*) * HTAB_MAX);
  if(tab == NULL){
    fprintf(stderr, "Warning: hash table allocation failed.\n");
    return NULL;
  }
	for (int i = 0; i < HTAB_SIZE; i++){
		(*tab)[i] = NULL;
	}
  return tab;
}


htabItem_t *htab_add(htab_t *htab, char *key){
  if(htab == NULL || key == NULL){
    return NULL;
  }

  htabItem_t *tmp = htab_find(htab, key);
  if(tmp != NULL){
    return NULL;
  }

  htabItem_t * tmp_ins = (htabItem_t*)malloc(sizeof(htabItem_t));
  if(tmp_ins == NULL){
    fprintf(stderr, "Warning: hash table allocation failed.\n");
    return NULL;
  }

  //inicializace položky 
  tmp_ins->key = malloc(sizeof(char)*strlen(key)+1);
  strcpy(tmp_ins->key, key);
  tmp_ins->next = NULL;

  //data položky
  tmp_ins->data = (data_t*)malloc(sizeof(data_t));
  if(tmp_ins->data == NULL){
    fprintf(stderr, "Warning: hash table allocation failed.\n");
    return NULL;
  }

  //FIXME domluvit se jak bude inicializovano
  tmp_ins->data->defined = false;
  tmp_ins->data->declared = false;
  tmp_ins->data->id = NULL;
  tmp_ins->data->isnil = false;
  tmp_ins->data->number = 0;
  
  tmp_ins->data->var_type = 5;

  tmp_ins->data->input_id = NULL;
  tmp_ins->data->input_id_len = 0;

  tmp_ins->data->input_type = NULL;
  tmp_ins->data->input_type_len = 0;

  tmp_ins->data->output_type = NULL;
  tmp_ins->data->output_type_len = 0;

  //vložení na začátek seznamu synonym
  if((tmp = (*htab)[hash_function(key)]) != NULL){
    tmp_ins->next = tmp;
  }

  (*htab)[hash_function(key)] = tmp_ins;

  return tmp_ins;
    
}


bool htab_set_data(htab_t *htab, char *key, bool defined, bool declared, char *id, type_t var_type){
  if(htab == NULL || key == NULL || id == NULL){
    return false;
  }

  htabItem_t *tmp = htab_find(htab, key);
  if(tmp == NULL){
    return false;
  }

  tmp->data->defined = defined;
  tmp->data->declared = declared;
  tmp->data->var_type = var_type;
  tmp->data->id = (char*)malloc(sizeof(char) * strlen(id) + 1); 
  if(tmp->data->id == NULL){
    fprintf(stderr, "Warning: hash table allocation failed.\n");
    return false;
  }
  strcpy(tmp->data->id, id);

  
  return true;
}


bool htab_add_input_type(htab_t *htab, char *key, type_t type){
  if(htab == NULL || key == NULL){
    return false;
  }

  htabItem_t *tmp = htab_find(htab, key);
  if(tmp == NULL){
    return false;
  }

  if(tmp->data->input_type == NULL){
    tmp->data->input_type_len = 1;
    tmp->data->input_type = (type_t*)malloc(sizeof(type_t));
    if(tmp->data->input_type == NULL){
      fprintf(stderr, "Warning: hash table allocation failed.\n");
      return false;
    }
    tmp->data->input_type[0] = type;
    return true;
  }

  if(tmp->data->input_type != NULL){
    tmp->data->input_type_len++;
    tmp->data->input_type = realloc(tmp->data->input_type, (sizeof(type_t)*(tmp->data->input_type_len)));
    if(tmp->data->input_type == NULL){
      fprintf(stderr, "Warning: hash table allocation failed.\n");
      return false;
    }
    tmp->data->input_type [tmp->data->input_type_len -1] = type;
    return true;
  }
  return false;
}


bool htab_add_return_type(htab_t *htab, char *key, type_t type){
  if(htab == NULL || key == NULL){
    return false;
  }

  htabItem_t *tmp = htab_find(htab, key);
  if(tmp == NULL){
    return false;
  }

  if(tmp->data->output_type == NULL){
    tmp->data->output_type_len = 1;
    tmp->data->output_type = (type_t*)malloc(sizeof(type_t));
    if(tmp->data->output_type == NULL){
      fprintf(stderr, "Warning: hash table allocation failed.\n");
      return false;
    }
    tmp->data->output_type[0] = type;
    return true;
  }

  if(tmp->data->output_type != NULL){
    tmp->data->output_type_len++;
    tmp->data->output_type = realloc(tmp->data->output_type, (sizeof(type_t)*(tmp->data->input_type_len)));
    if(tmp->data->output_type == NULL){
      fprintf(stderr, "Warning: hash table allocation failed.\n");
      return false;
    }
    tmp->data->output_type[tmp->data->output_type_len - 1] = type;
    return true;
  }
  return false;
}


bool htab_add_input_id(htab_t *htab, char *key, char *id){
  if(htab == NULL || key == NULL){
    return false;
  }

  htabItem_t *tmp = htab_find(htab, key);
  if(tmp == NULL){
    return false;
  }

  //init
  if(tmp->data->input_id == NULL){
    //nsatavit ctr na 1
    tmp->data->input_id_len = 1;

    //alokavoat první char ptr
    tmp->data->input_id = malloc(sizeof(char*));
    if(tmp->data->input_id == NULL){
      fprintf(stderr, "Warning: hash table allocation failed.\n");
      return false;
    }

    //naalokovat prostor pro ID
    tmp->data->input_id[0] = malloc(sizeof(char)*strlen(id)+1);
    if(tmp->data->input_id[0] == NULL){
      fprintf(stderr, "Warning: hash table allocation failed.\n");
      return false;
    }

    //nakopírovat hodnotu do tydle kokotiny
    strcpy(tmp->data->input_id[0], id);
    return true;
  }

  if(tmp->data->input_id != NULL){
    //inkr counter
    tmp->data->input_id_len++;
    //přidat pamet pro jeden pointer jeden pointer
    tmp->data->input_id = realloc(tmp->data->input_id, sizeof(char*)*tmp->data->input_id_len);
    if(tmp->data->input_id == NULL){
      fprintf(stderr, "Warning: hash table allocation failed.\n");
      return false;
    }
    //alokovat paměť pro string
    tmp->data->input_id[tmp->data->input_id_len -1] = malloc(sizeof(char)*strlen(id)+1);
    if (tmp->data->input_id[tmp->data->input_id_len -1] == NULL){
      fprintf(stderr, "Warning: hash table allocation failed.\n");
      return false;
    }
    
    //nakopirovat do pamenti
    strcpy(tmp->data->input_id[tmp->data->input_id_len -1], id);
    return true;
  }
  return false;
}


data_t *htab_get_data(htab_t* htab, char *key){
  if(htab == NULL || key == NULL){
    return NULL;
  }
  htabItem_t *tmp = htab_find(htab, key);
  if(tmp == NULL){
    return NULL;
  }
  if(tmp->data != NULL){
    return tmp->data;
  }
  else{
    return NULL;
  }
}


htabItem_t *htab_find(htab_t *htab, const char *key){
    if(htab == NULL ||key == NULL){
        return NULL;
    }
    htabItem_t *tmp = (*htab)[hash_function(key)];
    while(tmp != NULL){
        if(!strcmp(key, tmp->key)){
            return tmp;
        }
        tmp = tmp->next;
    }
    return NULL;
}


bool htab_delete(htab_t *htab, char *key){
  if(htab == NULL || key == NULL){
    return false;
  }

  htabItem_t *tmp = (*htab)[(hash_function(key))];
  htabItem_t *tmp_prev = NULL;
  htabItem_t *tmp_next = NULL;

  while(tmp != NULL){
    tmp_next = tmp->next;
    if(!strcmp(tmp->key, key)){
      free(tmp->data);
      free(tmp);
      if(tmp_prev == NULL){
        (*htab)[(hash_function(key))] = tmp_next;
        return true;
      }
      tmp_prev->next = tmp_next;
      return true; 
    }
    tmp_prev = tmp;
    tmp = tmp->next;
  }
  return false;
}



void htab_free(htab_t *htab){
    if(htab == NULL){
        return;
    }
    htabItem_t *tmp, *tmp2;

    for(int i = 0; i < HTAB_SIZE; i++){
        tmp = (*htab)[i];
        while(tmp != NULL){
            tmp2 = tmp;
            tmp = tmp->next;

            free(tmp2->data->input_type);
            free(tmp2->data->output_type);

            for(int i = 0; i < tmp2->data->input_id_len; i++){
              free(tmp2->data->input_id[i]);
            }
            free(tmp2->data->input_id);
            free(tmp2->data->id);
            free(tmp2->data);
            free(tmp2->key);
            free(tmp2);
        }
        (*htab)[i] = NULL;
    }
    free(htab);
    return;
}

int htab_count(htab_t *htab){ 
  if(htab == NULL){
    return 0;
  }

  htabItem_t *tmp;

  int ctr = 0;
  for(int i = 0; i < HTAB_SIZE; i++){
    if((*htab)[i] != NULL){
      tmp = (*htab)[i];
      while(tmp != NULL){
        tmp = tmp->next;
        ctr++;
      }
    }
  }
  return ctr;
}