/**
 * Implementace překladače jazyka IFJ21
 *
 * @file scanner.h
 * @brief Rozhraní lexikálního analyzátoru
 *
 * @author David Konečný (xkonec83)
 */
 

#ifndef _SCANNER_H
#define _SCANNER_H

#include <stdbool.h>

#include "structures.h"
#include "charAppender.h"

/**
 * Načte znak ze standartního vstupu a provede lexikální analýzu
 * Na základě rozpoznaného lexému uloží do tokenu příslušný typu, případně také také atribut
 *
 * @param token Ukazatel na token
 * @param option Nevyužito
 *
 * @return 0 nebo nenulovou hodnotu v případě chyby
 *
 * @retval 0: Funkce proběhla v pořádku
 * @retval 1: Chyba lexikální analýzy (špatný lexém)
 * @retval 99: Chyba alokace paměti
 */
int get_next_token(token_t *token, bool option);


/**
 * Destruktor pro token. 
 * Vola pouze destruktor pro charAppender 
 *
 * @param token Ukazatel na token
 */
void destToken (token_t* token);

#endif