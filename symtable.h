/**
 * Implentace překladače jazyka IFJ21
 * 
 * @file  htab.h
 * @brief knihovna vyhledávací tabulky
 *
 * @author Matěj Konopík    (xkonop03)
 */
#ifndef SYMTABLE_H_INCLUDET
#define SYMTABLE_H_INCLUDET
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#define HTAB_MAX 101  //FIXME	maximální velikost hashovací tabulky ! PRVOČÍSLO ! - nyní pro testing, do ostrého programu příjde něco okolo 65k

extern int HTAB_SIZE;

/** TYPY */

/**
 * @brief typy proměnných
 * 
 */
typedef enum{
    NUMBER_T,
    INTEGER_T,
    STRING_T,
    BOOL_T,
    NIL_T,
    UNDEFINED_T,
}type_t;

/**
 * @brief struktura pro data prvku - funkce i proměnná
 * 
 */
typedef struct htabData {
    bool declared;
    bool defined;
    bool isnil;

    type_t var_type;

    type_t *input_type;
    int input_type_len;

    type_t *output_type;
    int output_type_len;

    char **input_id;
    int input_id_len;
    
    char *id;
    int number;
} data_t;

/**
 * @brief struktura pro prvek tabulky
 * 
 */
typedef struct htab_item {
    data_t *data;
	char *key;
    struct htab_item *next;
} htabItem_t; 

/**
 * @brief struktura pro tabulku
 * 
 */
typedef htabItem_t* htab_t[HTAB_MAX];




/** FUNKCE */

/**
 * @brief hash funkce
 * 
 * @param str klíč k hashnutí
 * @return unsigned hash
 */
unsigned hash_function(const char *str); 

/**
 * @brief inicializuje tabulku - bez toho nelze použít jiné funkce !!!
 * 
 * @return dynamicky alokované pole ukazutelů na prvky tabulky ( == "tabulka")
 */
htab_t *htab_init();

/**
 * @brief přidá prvek do tabulky na základě klíče
 * 
 * @param htab tabulka, v níž bude prvek
 * @param key klíč prvku
 * @return ukazatel na vytvořený prvek. NULL pokud se nepovede
 */
htabItem_t *htab_add(htab_t *htab, char *key);

/**
 * @brief Nastaví data DEFINED, DECLARED a JMÉNO PROM./FCE
 * 
 * @param htab tabulka v níž je proměnná které se parametry nastavují
 * @param key klíč prvku
 * @param defined parametr prvku - je definovaný?
 * @param declared parametr prvku - je deklarovaný?
 * @param id jméno proměnné/funkce
 * @return true pokud se zdařilo, false pokud ne
 */
bool htab_set_data(htab_t *htab, char *key, bool defined, bool declared, char *id, type_t var_type);

/**
 * @brief Přidá argumentu funkce typ. Uchovává se v poli, je třeba je přidávát popořadě 
 * 
 * @param htab tabulka v níž je nastavovaná funkce
 * @param key klíč prvku
 * @param type jaký typ je argument - viz symtable.h -> types_t
 * @return true pokud se zdařilo, false pokud ne
 */
bool htab_add_input_type(htab_t *htab, char *key, type_t type);

/**
 * @brief přidá typ návratové hodnoty funkci. Uchovává se v poli, je třeba je přidávát popořadě
 * 
 * @param htab tabulka v níž je nastavovaná funkce
 * @param key klíč prvku
 * @param type jaký typ je funkce - viz symtable.h -> types_t
 * @return true pokud se zdařilo, false pokud ne
 */
bool htab_add_return_type(htab_t *htab, char *key, type_t type);

/**
 * @brief přidá název argumentu funkce. Uchovává se v poli, je třeba je přidávát popořadě
 * 
 * @param htab tabulka v níž je nastavovaná funkce
 * @param key klíč prvku
 * @param id název argumentu
 * @return true pokud se zdařilo, false pokud ne
 */
bool htab_add_input_id(htab_t *htab, char *key, char *id);

/**
 * @brief Najde a vratí uchovávaná data prvku pod zadaným klíčem
 * 
 * @param htab tabulka v níž je hledaný prvek
 * @param key klíč prvku
 * @return ukazatel na strukturu obsahující data prvku. Pokud nenalezne, vrací NULL
 */
data_t *htab_get_data(htab_t* htab, char *key);

/**
 * @brief nalezne prvek tabulky a vrátí ukazatel na něj. 
 * 
 * @param htab tabulka v níž je nastavovaná funkce
 * @param key klíč prvku
 * @return ukazatel na nalezený prvek. NULL pokud prvek nenajde 
 */
htabItem_t *htab_find(htab_t *htab, const char *key);

/**
 * @brief Smaže prvek tabulky
 * 
 * @param htab tabulka v ekteré je mazaný prvek
 * @param key klíč prvku
 * @return true pokud je smazán, false pokud ne (např. nebyl nalezen)
 */
bool htab_delete(htab_t *htab, char *key);

/**
 * @brief Smaže celou tabulku, dealokuje paměť
 * 
 * @param htab mazaná tabulka
 */
void htab_free(htab_t *htab);

/**
 * @brief spočítá prvky tabulky !!!NEVOLAT NAD VYPRÁZDNĚNOU TABULKOU!!!
 * 
 * @param htab tabulka k sečtení
 * @return int - počet prvků v tabulce
 */
int htab_count(htab_t *htab);

#endif //SYMTABLE_H_INCLUDET