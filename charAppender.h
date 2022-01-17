#ifndef CHARAPPENDER_H_INCLUDED
#define CHARAPPENDER_H_INCLUDED


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"

#define appCharING_DEFAULT_SIZE 10

/**
  * @brief Inicializuje TmString
  * @param appChar Ukazatel na neinicializovanou promenou, kterou ma inicializovat
  * @return OK_CHAR_APP      : Inicializace probehla v poradku
  * @return ERROR_ALLOCATION : Nepodarilo se alokovat pamet, inicializace neprobehla
  */
RreturnWalues appCharConstructor(TmString *appChar);

/**
  * @brief Rusi promenou, kazda inicializovana promena TmString musi byt timto zpusobem zrusena
  * @param appChar Ukazatel na inicializovanou promenou, kterou ma zrusit
  */
void appCharDestructor(TmString *appChar);

/**
  * @brief Prida znak na konec textu
  * @param appChar Ukazatel na inicializovanou promenou
  * @param a znak ktery prida na konec textoveho retezce, ktery obsahuje appChar
  * @return OK_CHAR_APP     : Pridavani probehlo v poradku
  * @return ERROR_ALLOCATION: Pri allocaci pameti pri pridavani znaku doslo k chybe
  */
RreturnWalues appCharAdd(TmString *appChar, char a);

/**
  * @brief Prekopiruje obsah textu v appCharingu do pole charu
  * @param to Ukazatel na prvni prvek pole charu o delce sizeOfArr
  * @param sizeOfArr Velikost pole sizeOfArr
  * @param appChar Ukazatel inicializovanou promenou typu appCharing ze ktere bude text prekopirovan
  * @return OK_CHAR_APP      : Kopirovani probehlo v poradku
  * @return ERROR_SMALL_ARRAY: Pole do ktereho se mnel text kopirovat je priliz male
  */
RreturnWalues appCharToStr(char* to, const size_t sizeOfArr, const TmString appChar);

/**
  * @brief Prekopiruje obsah textoveho retezce zakonceneho \0 do appChar, ktere musi byt inicializovane
  * @param appChar Ukazatel na inicializovana promena appCharing, do ktere se kopiruje
  * @param from Ukazatel na prvni znak pole obsahujici tetovy retezec
  * @return OK_CHAR_APP     : Prekopirovani probehlo v poradku
  * @return ERROR_ALLOCATION: Pri allocaci pameti pri pridavani znaku doslo k chybe
  */
RreturnWalues appCharFromStr(TmString *appChar, const char *from);

/**
  * @brief Prekopiruje obsah appCharFrom do appCharTo, Obe promene musi byt inicializovane
  * @param appCharTo ukazatel na inicializovanou promenou do ktere se kopiruje
  * @param appCharFrom Inicializovana promena ze ktere se kopiruje.
  * @return OK_CHAR_APP     : Prekopirovani probehlo v poradku
  * @return ERROR_ALLOCATION: Pri allocaci pameti pri pridavani znaku doslo k chybe
  */
RreturnWalues appCharToAppChar(TmString *appCharTo, const TmString appCharFrom);

/**
  * @brief Porovna textove retezce v appCharingech
  * @param appChar1 inicializovana promena appCharing
  * @param appChar2 inicializovana promena appCharing
  * @return > 0 appChar1 is after  appChar2 (appChar1 > appChar2)
            = 0 appChar1 is equal  appChar2 (appChar1 = appChar2)
            < 0 appChar1 is before appChar1 (appChar1 < appChar2)
  */
int appCharCmp(const TmString appChar1, const TmString appChar2);

/**
  * @brief Porovna textove retezec v appCharingu s textovym retezcem
  * @param appChar inicializovana promena appCharing
  * @param str ukazatel na prvni prvek pole obsahujiciho textovy retezec
  * @return > 0 appChar is after  str (appChar > str)
            = 0 appChar is equal  str (appChar = str)
            < 0 appChar is before str (appChar < str)
  */
int appCharCmpStr(const TmString appChar, const char *str);

/**
  * @brief Vrati delku textoveho retezce v appCharingu (bez \0)
  * @param appChar inicializovana promena appCharing
  * @return delku textoveho retezce v appCharingu
  */
size_t appCharLen(const TmString appChar);

#endif // CHARAPPENDER_H_INCLUDED
