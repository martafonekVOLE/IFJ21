#include <stdio.h>
#include <stdlib.h>
#include <string.h>



#include "structures.h"
#include "charAppender.h"

RreturnWalues appCharConstructor(TmString *appChar) {
    appChar->text = malloc(appCharING_DEFAULT_SIZE);//*sizeof(char)
    if (appChar->text == NULL) {
        appChar->leght = 0;
        appChar->used = 0;
        return ERROR_ALLOCATION;
    }
    appChar->leght = appCharING_DEFAULT_SIZE;
    appChar->used = 0;
    appChar->text[0] = '\0';
    return OK_CHAR_APP;
}

void appCharDestructor(TmString *appChar) {
    free(appChar->text);
    appChar->text = NULL;
    appChar->leght = 0;
    appChar->used = 0;//without \0
}

RreturnWalues appCharAdd(TmString *appChar, char a) {
    if (appChar->leght < appChar->used + 2) {// addet char and '\0'
        char *neu = realloc(appChar->text, appChar->leght + appCharING_DEFAULT_SIZE);
        if (neu == NULL) {
            return ERROR_ALLOCATION;
        }
        appChar->text = neu;
        appChar->leght += appCharING_DEFAULT_SIZE;
    }
    appChar->text[appChar->used] = a;
    appChar->text[(appChar->used) + 1] = '\0';
    //fprintf(stderr,"\nA %d :%s\n", appChar->used ,appChar->text);
    appChar->used += 1; //Nezapomenou incrementovat pocitadlo!
    return OK_CHAR_APP;
}


RreturnWalues appCharToStr(char *to, const size_t sizeOfArr, const TmString appChar){
    if (appChar.used + 1 > sizeOfArr) {
        to = NULL;
        return ERROR_SMALL_ARRAY;
    }
    strcpy(to, appChar.text);
    return OK_CHAR_APP;
}

RreturnWalues appCharFromStr(TmString *appChar, const char *from) {
    size_t lenPlusOne = strlen(from) + 1;
    if (appChar->leght < lenPlusOne) {
        char *neu = realloc(appChar->text, lenPlusOne);
        if (neu == NULL) {
            return ERROR_ALLOCATION;
        }
        appChar->text = neu;
        appChar->leght = lenPlusOne;
    }
    strcpy(appChar->text, from);
    appChar->used = lenPlusOne - 1;
    return OK_CHAR_APP;
}

RreturnWalues appCharToAppChar(TmString *appChar, const TmString appChar2) {
    size_t lenPlusOne = appChar2.used + 1;
    if (appChar->leght < lenPlusOne) {
        char *neu = realloc(appChar->text, lenPlusOne);
        if(neu == NULL) {
            return ERROR_ALLOCATION;
        }
        appChar->text = neu;
        appChar->leght = lenPlusOne;
    }
    strcpy(appChar->text, appChar2.text);
    appChar->used = lenPlusOne - 1;
    return OK_CHAR_APP;
}

int appCharCmp(const TmString appChar, const TmString appChar2) {
    return strcmp(appChar.text, appChar2.text);
}

int appCharCmpStr(const TmString appChar, const char *str) {
    return strcmp(appChar.text, str);
}

size_t appCharLen(const TmString appChar) {
    return appChar.used;
}

