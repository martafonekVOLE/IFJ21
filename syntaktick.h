#ifndef SYNTAKTICK_H_INCLUDED
#define SYNTAKTICK_H_INCLUDED


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "charAppender.h"
#include "scanner.h"
#include "semantika.h"

#include "semantika.h"
#include "zasobnik.h"
#include "codegen.h"

#include "symtable.h"
#include "tabstack.h"
#include "typeZas.h"


#ifdef DEBUGER
extern char velmiMalePoleZnaku[90];
#endif
int unikat = 0;
bool ruleVyraz();
///fc jednotlivych pravidel
void next(token_t* token, bool option);
void back(token_t token);

bool ruleS( htab_t** fc_table, tsStack_t** prom_table);
bool ruleKodG( htab_t** fc_table, tsStack_t** prom_table); //TO DO ?
bool ruleDefFC( htab_t** fc_table, tsStack_t** prom_table);
bool ruleDefFC2( htab_t** fc_table, tsStack_t** prom_table);
bool ruleDefFC3( htab_t** fc_table, tsStack_t** prom_table, char* nameFc);
bool ruleSeznamParam( htab_t** fc_table, tsStack_t** prom_table, char* nameFC);
bool ruleSeznamParam2( htab_t** fc_table, tsStack_t** prom_table, int* pocetZanoreni, char* nameFc);
bool ruleSeznamRet( htab_t** fc_table, tsStack_t** prom_table, char* jmFc);
bool ruleSeznamRet2( htab_t** fc_table, tsStack_t** prom_tablechar, char* jmFc, int* zanoreni);
bool rulePrirazovane( htab_t** fc_table, tsStack_t** prom_table, t_typeZas* typZas, int pocet);
bool rulePrirazovane2(htab_t** fc_table, tsStack_t** prom_table, t_typeZas* typZas, int pocet, int* zanoreni);
bool ruleHodnotaR( htab_t** fc_table, tsStack_t** prom_table, type_t *vysledny);//TO DO
bool rulePrirazeni( htab_t** fc_table, tsStack_t** prom_table);
bool ruleZbPrirazeni(htab_t** fc_table, tsStack_t** prom_table, t_typeZas* typeZas, int pocet);
bool ruleIf_cons( htab_t** fc_table, tsStack_t** prom_table,char *nameFc);
bool ruleWhile(htab_t** fc_table, tsStack_t** prom_table, char* nameFc);
bool dalsiPomocZavorky( htab_t** fc_table, tsStack_t** prom_table);
bool dalsiWrite( htab_t** fc_table, tsStack_t** prom_table);
bool ruleParVolC( htab_t** fc_table, tsStack_t** prom_table);
bool ruleParVol2C( htab_t** fc_table, tsStack_t** prom_table);
bool dalsiTointiger( htab_t** fc_table, tsStack_t** prom_table);
bool dalsiSubstr( htab_t** fc_table, tsStack_t** prom_table);
bool dalsiOrd( htab_t** fc_table, tsStack_t** prom_table);
bool dalsiChr( htab_t** fc_table, tsStack_t** prom_table);
bool ruleVolaniFc( htab_t** fc_table, tsStack_t** prom_table);
bool ruleParVol(htab_t** fc_table, tsStack_t** prom_table, char* nameFc);
bool ruleParVol2( htab_t** fc_table, tsStack_t** prom_table, char* nameFc, int* zanoreni);
bool ruleReturn( htab_t** fc_table, tsStack_t** prom_table, char* nameFc);
bool ruleReturnVal( htab_t** fc_table, tsStack_t** prom_table, char* nameFc);
bool ruleReturnVal2( htab_t** fc_table, tsStack_t** prom_table, char* nameFc, int *zanoreni);
bool ruleSlozenyPrikaz( htab_t** fc_table, tsStack_t** prom_table, char* nameFc);
//nove
bool ruleDecleFC( htab_t** fc_table, tsStack_t** prom_table);
bool ruleDecleFC2( htab_t** fc_table, tsStack_t** prom_table);
bool ruleDecleFC3( htab_t** fc_table, tsStack_t** prom_table, char* nameFC);
bool rulePrirazovaneAB( htab_t** fc_table, tsStack_t** prom_table, type_t vyzadovane, bool* nula, bool* nil);


int syntaktick_main();
void generateReturn(int a);


bool operace2(t_typeZas* zas);
bool operace2noNil(t_typeZas* zas);
bool operace2noStr(t_typeZas* zas);


bool specVyrazMain(htab_t** fc_table, tsStack_t** prom_table, type_t* vysledny);
t_RizeniVyrazu vyberReseni(token_t tokenZ, token_t tokenN);



#endif //SYNTAKTICK_H_INCLUDED







