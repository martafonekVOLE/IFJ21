/**
* Project: Implementace překladače jazyka IFJ21
*
* @brief Code generator header
*
* @author Martin Pech <xpechm00@stud.fit.vutbr.cz>
*/

//#ifdef CODEGEN_H
//#define CODEGEN_H

#include <stdio.h>
#include <stdbool.h>

/*=======================================================================*/
//                          Vestavěné funkce
/*=======================================================================*/
/**
* Vestavěná funkce Substr, vypíše vyžadovaný podřetězec
*
*
* 
*/
void BuiltIn_Substr();

/**
* Vestavěná funkce Reads, načte řádek řetězcových literálů
*
*
* 
*/
void BuiltIn_Reads();

/**
* Vestavěná funkce Readi, načte řádek celých čísel
*
*
* 
*/
void BuiltIn_Readi();

/**
* Vestavěná funkce Readn, načte řádek desetinných čísel
*
*
* 
*/
void BuiltIn_Readn();

/**
* Vestavěná funkce Chr, vrátí jednoznakový řetězec se znakem odpovídajícím ASCII hodnotě
*
*
* 
*/
void BuiltIn_Chr();

/**
* Vestavěná funkce Ord, vrátí ordinální hodnotu znaku v řetězci
*
*
* 
*/
void BuiltIn_Ord();

/**
* Vestavěná funkce Float2Int umožňuje konverzi desetinného čísla na celé číslo oseknutím desetinné části
*
*
* 
*/
void BuiltIn_Float2Int();

/**
* Vestavěná funkce WriteBegin, zahajuje vypisování termů
*
*
* 
*/
void BuiltIn_WriteBegin();

/**
* Vestvěná funkce WriteInsert, dochází zde ke vkládání jednotlivých termů do vypisovaného řetězce
*
*
* 
*/
void BuiltIn_WriteInsert();

/**
* Vestavěná funkce WriteEnd, ukončuje vypisování termů
*
*
* 
*/
void BuiltIn_WriteEnd();

/**
* Vestavěná funkce clearStack, kompletně vyčistí zásobník
*
*
* 
*/
void BuiltIn_clearStack();

/**
* Vestavěná funkce decision, provede vyhodnocení podmínky
*
*
* 
*/
void BuiltIn_decision();

/**
* Vestavěná funkce notDecision, provede vyhodnocení podmínky a zneguje výsledek
*
*
* 
*/
void BuiltIn_notDecision();

/**
* Vygeneruje vestavěné funkce
*
*
* 
*/
void generateBuiltIn();

/**
* Na vrchol zásobníku vloží proměnnou libovolného rámce 
*
*
* @param variableName očekává jméno proměnné
* @param type očekává typ proměnné
*/
void addVarOnTop(char *variableName, char *type);

/**
* Na vrchol zásobníku vloží konstantu libovolného typu
*
*
* @param value očekává hodnotu konstanty
* @param type očekává typ konstanty
*/
void addConstOnTop(char *value, char *type);

/**
* Vloží lokální proměnnou na vrchol zásobníku
*
*
* @param variableName očekává jméno proměnné
*/
void addLocalVarOnTop(char *variableName);

/**
* Decisive data type function 
*
*
@param value Value to be decided about
bool isInteger(float value);
*/ //UNUSED 

/**
* Puts value on the stack
*
*
@param value Value to be put on the stack
*
void AddNumOnTop(float value);
*/ //UNUSED

/**
* Na vrchol zásobníku vloží textový řetězec
*
*
* @param value Očekává hodnotu typu string
*/
void AddStringOnTop(char *value);

/**
* Na vrchol zásobníku vloží desetinné číslo
*
*
* @param value Očekává hodnotu typu string
*/
void AddNumberOnTop(char *value);

/**
* Na vrchol zásobníku vloží celočíselnou hodnotu
*
*
* @param value Očekává hodnotu typu string
*/
void AddIntOnTop(char *value);

/**
* Na vrchol zásobníku vloží hodnotu nil
*
*
* 
*/
void AddNilOnTop();

/**
* Pomocná funkce vracející návratovou hodnotu funkce na vrchol zásobníku
*
*
* 
*/
void functionRetval();

/**
* Přečte prvek na vrcholu zásobníku
*
*
*
*/
void ReadTop();

/**
* Přečte prvek na vrcholu zásobníku a uloží do lokální proměnné
*
*
* @param variableName očekává jméno proměnné
*/
void ReadTopTo(char *variableName);

/**
* Pomocná funkce vypisující hodnotu z vrcholu zásobníku (používá se v kombinací s funkcí ReadTop)
*
*
*
*/
void PrintReadTopResult();

/*=======================================================================*/
//                      Aritmetické operace
/*=======================================================================*/
/**
* Funkce provede sečtení dvou čísel na zásobníku voláním funkce ADDS z jazyka ifjcode21
*
*
*
*/
void StackAdds();

/**
* Funkce provede sečtení dvou čísel v proměnných voláním funkce ADD z jazyka ifjcode21
*
*
* @param type očekává specifikování rámce, na kterým se operace provede
* @param retval očekává jméno proměnné, do které je uložen výsledek
* @param firstArg první argument operace
* @param secondArg druhý argument operace
*/
void Add(char *type, char *retval, char* firstArg, char* secondArg);

/**
* Funkce provede rozdíl dvou čísel na zásobníku voláním funkce SUBS z jazyka ifjcode21
*
*
*
*/
void StackSubs();

/**
* Funkce provede rozdíl dvou čísel v proměnných voláním funkce SUB z jazyka ifjcode21
*
*
* @param type očekává specifikování rámce, na kterým se operace provede
* @param retval očekává jméno proměnné, do které je uložen výsledek
* @param firstArg první argument operace
* @param secondArg druhý argument operace
*/
void Sub(char *type, char *retval, char* firstArg, char* secondArg);

/**
* Funkce provede součin dvou čísel na zásobníku voláním funkce MULS z jazyka ifjcode21
*
*
*
*/
void StackMuls();

/**
* Funkce provede součin dvou čísel v proměnných voláním funkce MUL z jazyka ifjcode21
*
*
* @param type očekává specifikování rámce, na kterým se operace provede
* @param retval očekává jméno proměnné, do které je uložen výsledek
* @param firstArg první argument operace
* @param secondArg druhý argument operace
*/
void Mul(char *type, char *retval, char* firstArg, char* secondArg);

/**
* Funkce provede podíl dvou desetinných čísel na zásobníku voláním funkce DIVS z jazyka ifjcode21
*
*
*
*/
void StackDivs();

/**
* Funkce provede podíl dvou desetinných čísel v proměnných voláním funkce DIV z jazyka ifjcode21
*
*
* @param type očekává specifikování rámce, na kterým se operace provede
* @param retval očekává jméno proměnné, do které je uložen výsledek
* @param firstArg první argument operace (dělenec)
* @param secondArg druhý argument operace (dělitel)
*/
void Div(char *type, char *retval, char* firstArg, char* secondArg);

/**
* Funkce provede podíl dvou celých čísel na zásobníku voláním funkce IDIVS z jazyka ifjcode21
*
*
*
*/
void StackIdivs();

/**
* Funkce provede podíl dvou celých čísel v proměnných voláním funkce IDIV z jazyka ifjcode21
*
*
* @param type očekává specifikování rámce, na kterým se operace provede
* @param retval očekává jméno proměnné, do které je uložen výsledek
* @param firstArg první argument operace (dělenec)
* @param secondArg druhý argument operace (dělitel)
*/
void Idiv(char *type, char *retval, char* firstArg, char* secondArg);

/**
* Funkce provede konverzi desetinného čísla na zásobníku na celé číslo voláním funkce INT2FLOATS z jazyka ifjcode21
*
*
*
*/
void int2floats();

/**
* Funkce provede konverzi druhého desetinného čísla na zásobníku na celé číslo voláním funkce INT2FLOATS z jazyka ifjcode21
*
*
*
*/
void int2floats2();

/*=======================================================================*/
//                      Porovnávání hodnot
/*=======================================================================*/
/**
* Za použití vestavěné funkce $$decision vyhodnotí, zdali jsou dvě čísla na zásobníku stejná
*
*
*
*/
void stackTopEqualToNext();

/**
* Za použití vestavěné funkce $$notDecision vyhodnotí, zdali jsou dvě čísla na zásobníku odlišná
*
*
*
*/
void stackTopNotEqualToNext();

/**
* Za použití vestavěné funkce $$decision vyhodnotí, zdali je starší číslo na zásobníku větší než novější
*
*
*
*/
void bigger();

/**
* Za použití vestavěné funkce $$notDecision vyhodnotí, zdali je starší číslo na zásobníku větší, nebo rovno novějšímu
*
*
*
*/
void biggerEqual();

/**
* Za použití vestavěné funkce $$decision vyhodnotí, zdali je starší číslo na zásobníku menší než novější
*
*
*
*/
void smaller();

/**
* Za použití vestavěné funkce $$notDecision vyhodnotí, zdali je starší číslo na zásobníku menší, nebo rovno novějšímu
*
*
*
*/
void smallerEqual();

/*=======================================================================*/
//                          Obecné ovládání
/*=======================================================================*/
/**
* Generuje hlavičku
*
*
* 
*/
void generateHeader();

/**
* Generuje počátek funkce main
*
*
*
*/
void generateMain();

/**
* Generuje konec funkce main
*
*
* 
*/
void generateMainEnd();

/**
* Vytvoří dočasný rámec
*
*
*
*/
void createFrame();

/**
* Posune dočasný rámec na zásobník lokálních rámců
*
*
*
*/
void pushFrame();

/**
* Odstraní rámec ze zásobníků lokálních rámců
*
*
*
*/
void popFrame();

/**
* Zahodí jednu hodnotu z vrcholu zásobníku
*
*
*
*/
void trashStack();

/**
* Vytvoří návěští
*
*
*
* @param labelName očekává unikátní pojmenování návěští
*/
void makeLabel(char *labelName);

/**
* Vytvoří novou lokální proměnnou
*
*
* @param varName očekává unikátní jméno proměnné
*/
void createLocalVar(char *varName);

/**
* Přečte vrchol zásobníku a místo něj uloží délku tohoto řetězce
*
*
*
*/
void strlenFunction();

/**
* Zavolá uživatelskou funkci
*
*
* @param functionName očekává jméno existujícího návěští
*/
void functionCall(char *functionName);

/**
* Zavolá programovou funkci
*
*
* @param functionName očekává jméno existujícího návěští
*/
void programFunctionCall(char *functionName);

/**
* Inicializuje prázdný zásobník tak, že na dno uloží hodnotu bool@true (vhodné pro potřeby funkce clearStack)
*
*
*
*/
void stackInitBool();

/**
* Zavolá vestavěnou funkci na vyčištění zásobníku
*
*
*
*/
void clearStack();

/**
* Provede konkatenaci dvou řetězců, výsledek uloží na zásobník
*
*
*
*/
void concatVars();

/*=======================================================================*/
//                Funkce pro generování uživatelské funkce
/*=======================================================================*/
/**
* Vytvoří počáteční návěští funkce a nový rámec
*
*
*
* @param functionName očekává unikátní jméno funkce
*/
void functionStart(char *functionName);

/**
* Zahodí použitý rámec a navrátí program tam, kde byla funkce volána
*
*
*
*/
void functionEnd();

/**
* Vytvoří návěští za funkcí (aby mohla být funkce přeskočena)
*   
*
* @param functionName očekává jméno funkce (stejné jako funkce functionStart)
*/
void functionEndLabel(char *functionName);

/*=======================================================================*/
//                     Funkce pro generování cyklu
/*=======================================================================*/
/**
* Vytvoří počáteční návěští cyklu
*   
*
* @param nthWhile očekává unikátní číslo cyklu (kolikátý cyklus v programu to je)
*/
void generateWhileLabel(int nthWhile);

/** Generuje počátek smyčky while, přenáší proměnné z nižšího rámce (kvůli zanořování)
*   
*
* @param nthWhile očekává unikátní číslo cyklu (kolikátý cyklus v programu to je)
* @param toNumber očekává číslo identifikující proměnnou, která má být přenešena
*/
void generateWhile(int nthWhile, int toNumber);

/** Generuje konec smyčky while, přenáší proměnné z vyššího rámce (kvůli vynoření)
*   
*
* @param nthWhile očekává unikátní číslo cyklu (kolikátý cyklus v programu to je)
* @param toNumber očekává číslo identifikující proměnnou, která má být přenesena
*/
void generateWhileEnd(int nthWhile, int toNumber);

/*=======================================================================*/
//                  Funkce pro generování podmmínky
/*=======================================================================*/
/** Generuje počátek podmínky, přenáší proměnné z nižšího rámce (kvůli zanořování)
*   
*
* @param nthIf očekává unikátní číslo podmínky (kolikátá podmínka v programu to je)
* @param toNumber očekává číslo identifikující proměnnou, která má být přenešena
*/
void generateIf(int nthWhile, int toNumber);

/** Generuje else větev podmínky, přenáší proměnné z nižšího rámce (kvůli zanořování)
*   
*
* @param nthIf očekává unikátní číslo podmínky (kolikátá podmínka v programu to je)
* @param toNumber očekává číslo identifikující proměnnou, která má být přenešena
*/
void generateElse(int nthIf, int toNumber);

/** Generuje konec podmínky, přenáší proměnné z vyššího rámce (kvůli vynořování)
*   
*
* @param nthIf očekává unikátní číslo podmínky (kolikátá podmínka v programu to je)
* @param toNumber očekává číslo identifikující proměnnou, která má být přenešena
*/
void generateIfEnd(int nthWhile, int toNumber);
//#endif