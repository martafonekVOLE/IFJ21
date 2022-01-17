#ifndef SEMANTIKA_H_INCLUDED
#define SEMANTIKA_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "charAppender.h"
#include "scanner.h"

#include "symtable.h"
#include "tabstack.h"

#ifdef DEBUGER
extern char velmiMalePoleZnaku[90];
#endif
void sem_init(htab_t** fc_table, tsStack_t** prom_table);

void sem_destroy(htab_t** fc_table, tsStack_t** prom_table);

/* Zkontroluje ID fc pro definici, pripadne ho prida do tabulky
*/
bool sem_FCIdDef(token_t token, htab_t** fc_table, tsStack_t** prom_table);

/* Prida ID pro prom, jeli na teto urovni vyrobeno tak nastane chyba
*/
bool sem_PromDef(char* name, htab_t** fc_table, tsStack_t** prom_table, /*int number,*/ type_t typ, bool* chybaPameti,bool nula, bool nil);
//(char* name, htab_t** fc_table, tsStack_t** prom_table, /*int number,*/ type_t typ, bool* chybaPameti, bool definovano);

//Overi ze se jedna o declarovanou fc akceptuje i defaultni fc
bool sem_isFC(token_t token, htab_t** fc_table, tsStack_t** prom_table);

//Overi ze se jedna o declarovanou prom
bool sem_isProm(token_t token, htab_t** fc_table, tsStack_t** prom_table);

//bool sem_PromDecler(token_t token, htab_t** fc_table, tsStack_t** prom_table);//TO DO rozpoznani definovaneho a declarovaneho

bool sem_FCIdDecler(token_t token, htab_t** fc_table, tsStack_t** prom_table);//TO DO co kdyz bude prvne identifikator promene a pak fc?

bool sem_addInputControl(htab_t** fc_table, char* nameFc, type_t type, int kolikatyIndex, bool* chybaAlok);

bool sem_addOutputControl(htab_t** fc_table, char* nameFc, type_t type, int kolikatyIndex, bool* chybaAlok);

bool sem_checkReturn(htab_t** fc_table, char* nameFc, type_t type, int kolikatyIndex);

#ifdef COMENT_OUT_REGIOn 
//TO DO parametry funkci je potreba rozsirit o zasobnik a ukazatele na zaznamy

/* Zkontroluje ID fc pro definici, pripadne ho prida do tabulky, vrati na ni ukazatel
 * je li definovana tak chyba
*/
bool sem_FCIdDef(token_t token);

/* Zkontroluje ID fc pro declaraci, pripadne ho prida do tabulky, vrati na ni ukazatel
 * je li declarovana tak chyba
*/
bool sem_FCIdDecle(token_t token);

/* Prida ID pro prom, jeli na teto urovni vyrobeno tak nastane chyba, vrati na nej ukazatel, nastavi ze je nedefinovana ale declarovana
*/
bool sem_PromDec(token_t token);

//Overi ze se jedna o declarovanou nebo definovanou fc, akceptuje i defaultni fc (napr readi())
bool sem_isFC(token_t token);

//Overi ze se jedna o declarovanou prom, jestli ano, vrati na ni ukazatel
bool sem_isPromDecle(token_t token);

//Overi ze se jedna o definovanou prom, jestli ano, vrati na ni ukazatel
bool sem_isPromDef(token_t token);

/* prida novou tabulku symbolu na zasobnik tabulek (nova tabulka je prazna)
*/
void sem_novaTabNaZas();

/* odstrani tabulku z zasobniku tabulek, odstranovana obsahuje zaznamy
*/
void sem_popTabZeZas();

/* init pro tabulku fc, a zasobnik dabulek promenych
*/
void sem_init();

/* destruktor budeli treba
*/
void sem_destructor();
#endif

#endif //SEMANTIKA_H_INCLUDED