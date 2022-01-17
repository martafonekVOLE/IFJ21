/**
 * Implementace překladače jazyka IFJ21
 *
 * @file scanner.c
 * @brief Lexikální analyzátor
 *
 * @author David Konečný (xkonec83)
 */


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "scanner.h"
#include "structures.h"

// Makro pro ladící výpis
#define DEBUG 0

#define M_PRINT(fmt) \
    do { if (DEBUG){ fprintf(stderr, "%c", fmt); }} while (0)



int get_next_token(token_t *token, bool option) {

    // Proměnná pro znak
    char c;

    enum state_t state = START_ST;


    while (c != EOF) {
        // Načtení z stdin
        c = getchar();
        
        // Konečný automat pro scanner
        switch (state) {
            
            case START_ST:
                if (c >= '0' && c <= '9') {
                    state = NUMBER_ST;
                    
                    if (appCharAdd(&token->attribute, c)) {
                        return 99;
                    }
                }
                else if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_') {
                    state = ID_ST;

                    if (appCharAdd(&token->attribute, c)) {
                        return 99;
                    }
                }
                else if (c == ':') {
                    token->type = VAR_INIT;
                    M_PRINT(c); // Pro debug
                    return 0;
                }
                else if (c == '(') {
                    token->type = LEFT_BRACKET;
                    M_PRINT(c); // Pro debug
                    return 0;
                }
                else if (c == ')') {
                    token->type = RIGHT_BRACKET;
                    M_PRINT(c); // Pro debug
                    return 0;
                }
                else if (c == '"') {
                    state = QUOTATION_ST;
                }
                else if (c == ',') {
                    token->type = COMMA;
                    M_PRINT(c); // Pro debug
                    return 0;
                }
                else if (c == '#') {
                    token->type = HASH;
                    M_PRINT(c); // Pro debug
                    return 0;
                }
                else if (c == '*') {
                    token->type = MULTIPLY;
                    M_PRINT(c); // Pro debug
                    return 0;
                }
                else if (c == '/') {
                    state = SLASH_ST;
                }
                else if (c == '+') {
                    token->type = PLUS;
                    M_PRINT(c); // Pro debug
                    return 0;
                }
                else if (c == '-') {
                    state = DASH_ST;
                }
                else if (c == '.') {
                    state = DOT_ST;
                }
                else if (c == '=') {
                    state = EQUAL_SIGN_ST;
                }
                else if (c == '<') {
                    state = LESS_ST;
                }
                else if (c == '>') {
                    state = GREATER_ST;
                }
                else if (c == '~') {
                    state = TILDA_ST;
                }
                // Detekce bílých znaků
                else if (c == ' ' || c == '\n' || c == '\t' || c == '\v' || c == '\f' || c == '\r') {
                    state = START_ST;
                }
                else if (c == EOF) {
                    token->type = END;
                    return 0;
                }
                else
                {
                    if (appCharAdd(&token->attribute, c)) {
                        return 99;
                    }

                    // Znak není v abecedě
                    token->type = ERROR;
                    return 1;
                }

            break;

            case NUMBER_ST:
                if (c >= '0' && c <= '9') {
                    // Znak je pořád číslo
                    
                    if (appCharAdd(&token->attribute, c)) {
                        return 99;
                    }
                }
                else if (c == '.') {
                    state = DECIMAL_DOT_ST;

                    if (appCharAdd(&token->attribute, c)) {
                        return 99;
                    }
                }
                else if (c == 'e' || c == 'E') {
                    state = EXPONENT_SIGN_ST;

                    if (appCharAdd(&token->attribute, c)) {
                        return 99;
                    }
                }
                else {
                    // Na vstup nepřišel žádný speciální znak, číslo je integer

                    if (appCharAdd(&token->attribute, c)) {
                        return 99;
                    }

                    token->type = INTEGER;
                    return 0;
                }
            break;

            case DECIMAL_DOT_ST:
                if (c >= '0' && c <= '9')
                {
                    state = DECIMAL_ST;

                    if (appCharAdd(&token->attribute, c)) {
                        return 99;
                    }
                }
                else
                {
                    // Za tečkou je prázdné místo, vznikla chyba

                    token->type = ERROR;
                    return 1;
                }
            break;

            case DECIMAL_ST:
                if (c >= '0' && c <= '9') {
                    // Znak je pořád číslo

                    if (appCharAdd(&token->attribute, c)) {
                        return 99;
                    }
                }
                else if (c == 'e' || c == 'E') {
                    state = EXPONENT_SIGN_ST;

                    if (appCharAdd(&token->attribute, c)) {
                        return 99;
                    }
                }
                else {
                    ungetc(c, stdin);
                    token->type = NUMBER;
                    return 0;
                }
            break;

            case EXPONENT_SIGN_ST:
                if (c == '+' || c == '-') {
                    state = EXPONENT_FIRST_ST;

                    if (appCharAdd(&token->attribute, c)) {
                        return 99;
                    }
                }
                else if (c >= '0' && c <= '9') {
                    state = EXPONENT_ST;

                    if (appCharAdd(&token->attribute, c)) {
                        return 99;
                    }
                }
                else {
                    // Za znaménkem exponentu není číslo, vznikla chyba

                    if (appCharAdd(&token->attribute, c)) {
                        return 99;
                    }

                    token->type = ERROR;
                    return 1;
                }
            break;

            case EXPONENT_FIRST_ST:
                if (c >= '0' && c <= '9') {
                    state = EXPONENT_ST;

                    if (appCharAdd(&token->attribute, c)) {
                        return 99;
                    }
                }
                else {
                    // Za 'e' nebo 'E' není číslo, vznikla chyba

                    if (appCharAdd(&token->attribute, c)) {
                        return 99;
                    }

                    token->type = ERROR;
                    return 1;
                }
            break;

            case EXPONENT_ST:
                if (c >= '0' && c <= '9') {
                    // Znak je pořád číslo

                    if (appCharAdd(&token->attribute, c)) {
                        return 99;
                    }
                }
                else {
                    // Exponentová část je u konce

                    ungetc(c, stdin);
                    token->type = NUMBER;
                    return 0;
                }
            break;

            case SLASH_ST:
                if (c == '/') {
                    token->type = DOUBLE_SLASH;
                    M_PRINT(c); // Pro debug
                    return 0;
                }
                else {
                    ungetc(c, stdin);
                    token->type = SLASH;
                    M_PRINT(c); // Pro debug
                    return 0;
                }
            break;

            case DASH_ST:
                if (c == '-') {
                    state = DOUBLE_DASH_ST;
                }
                else {
                    ungetc(c, stdin);
                    token->type = MINUS;
                    M_PRINT(c); // Pro debug
                    return 0;
                }
            break;

            case DOUBLE_DASH_ST:
                if (c == '[') {
                    // --[

                    state = NOT_COMPLETE_MULT_COMMENT_ST;
                }
                else {
                    // Jednořádkový komentář --

                    ungetc(c, stdin);
                    state = LINE_COMMENT_ST;
                }
            break;

            case NOT_COMPLETE_MULT_COMMENT_ST:
                if (c == '[') {
                    // --[[

                    state = MULT_COMMENT_ST;
                }
                else {
                    // Jednořádkový komentář --
                    
                    ungetc(c, stdin);
                    ungetc(c, stdin);
                    state = LINE_COMMENT_ST;
                }
            break;

            case LINE_COMMENT_ST:
                if (c == '\n') {
                    state = START_ST;
                }
            break;

            case MULT_COMMENT_ST:
                if (c == ']') {
                    state = NOT_COMPLETE_MULT_COMMENT_END_ST;
                }
            break;

            case NOT_COMPLETE_MULT_COMMENT_END_ST:
                if (c == ']') {
                    state = START_ST;
                }
                else {
                    state = MULT_COMMENT_ST;
                }
            break;

            case DOT_ST:
                if (c == '.') {
                    token->type = DOUBLE_DOT;
                    M_PRINT(c); // Pro debug
                    return 0;
                }
                else {
                    ungetc(c, stdin);
                    token->type = ERROR;
                    return 1;
                }
            break;

            case EQUAL_SIGN_ST:
                if (c == '=') {
                    token->type = EQUAL;
                    M_PRINT(c); // Pro debug
                    return 0;
                }
                else {
                    ungetc(c, stdin);
                    token->type = ASSIGN;
                    return 0;
                }
            break;

            case LESS_ST:
                if (c == '=') {
                    token->type = LESS_EQ;
                    M_PRINT(c); // Pro debug
                    return 0;
                }
                else {
                    ungetc(c, stdin);
                    token->type = LESS;
                    return 0;
                }
            break;

            case GREATER_ST:
                if (c == '=') {
                    token->type = GREATER_EQ;
                    M_PRINT(c); // Pro debug
                    return 0;
                }
                else {
                    ungetc(c, stdin);
                    token->type = GREATER;
                    return 0;
                }
            break;

            case TILDA_ST:
                if (c == '=') {
                    token->type = NOT_EQUAL;
                    M_PRINT(c); // Pro debug
                    return 0;
                }
                else {
                    ungetc(c, stdin);
                    token->type = ERROR;
                    return 1;
                }
            break;

            case ID_ST:
                if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_') {
                    // Stále se jedná o identifikátor

                    if (appCharAdd(&token->attribute, c)) {
                        return 99;
                    }
                }
                else {
                    ungetc(c, stdin);
                    // Kontrola klíčových slov

                    if (!(appCharCmpStr(token->attribute, "do"))) {
                        token->type = DO_KW;
                    }
                    else if (!(appCharCmpStr(token->attribute, "else"))) {
                        token->type = ELSE_KW;
                    }
                    else if (!(appCharCmpStr(token->attribute, "end"))) {
                        token->type = END_KW;
                    }
                    else if (!(appCharCmpStr(token->attribute, "function"))) {
                        token->type = FUNCTION_KW;
                    }
                    else if (!(appCharCmpStr(token->attribute, "global"))) {
                        token->type = GLOBAL_KW;
                    }
                    else if (!(appCharCmpStr(token->attribute, "if"))) {
                        token->type = IF_KW;
                    }
                    else if (!(appCharCmpStr(token->attribute, "local"))) {
                        token->type = LOCAL_KW;
                    }
                    else if (!(appCharCmpStr(token->attribute, "nil"))) {
                        token->type = NIL_KW;
                    }
                    else if (!(appCharCmpStr(token->attribute, "require"))) {
                        token->type = REQUIRE_KW;
                    }
                    else if (!(appCharCmpStr(token->attribute, "return"))) {
                        token->type = RETURN_KW;
                    }
                    else if (!(appCharCmpStr(token->attribute, "then"))) {
                        token->type = THEN_KW;
                    }
                    else if (!(appCharCmpStr(token->attribute, "while"))) {
                        token->type = WHILE_KW;
                    }
                    else if (!(appCharCmpStr(token->attribute, "integer"))) {
                        token->type = INTEGER_KW;
                    }
                    else if (!(appCharCmpStr(token->attribute, "number"))) {
                        token->type = NUMBER_KW;
                    }
                    else if (!(appCharCmpStr(token->attribute, "string"))) {
                        token->type = STRING_KW;
                    }
                    else if (!(appCharCmpStr(token->attribute, "reads"))) {
                        token->type = READS_KW;
                    }
                    else if (!(appCharCmpStr(token->attribute, "readi"))) {
                        token->type = READI_KW;
                    }
                    else if (!(appCharCmpStr(token->attribute, "readn"))) {
                        token->type = READN_KW;
                    }
                    else if (!(appCharCmpStr(token->attribute, "write"))) {
                        token->type = WRITE_KW;
                    }
                    else if (!(appCharCmpStr(token->attribute, "tointeger"))) {
                        token->type = TOINTEGER_KW;
                    }
                    else if (!(appCharCmpStr(token->attribute, "substr"))) {
                        token->type = SUBSTR_KW;
                    }
                    else if (!(appCharCmpStr(token->attribute, "ord"))) {
                        token->type = ORD_KW;
                    }
                    else if (!(appCharCmpStr(token->attribute, "chr"))) {
                        token->type = CHR_KW;
                    }
                    else {
                        // Atribut není žádné klíčové slovo, jedná se o identífikátor

                        token->type = ID;
                    }
                    
                    return 0;
                }
            break;

            case QUOTATION_ST:
                if (c == '"') {
                    token->type = STRING_IN_QUOTATION;
                    M_PRINT(c); // Pro debug
                    return 0;
                }
                else {
                    // Stále se jedná o text v uvozovkách

                    if (appCharAdd(&token->attribute, c)) {
                        return 99;
                    }
                }
            break;
        }

        M_PRINT(c); // Pro debug
    }

    // Pokud skončila hlavní smyčka, narazili jsme na konec souboru (EOF)

    token->type = END;
    return 0;
}



//TO DO schovat do spravneho souboru
//TO DO napsat do hlavickoveho ze je to destruktor
void destToken (token_t* tok){
    appCharDestructor(&(tok->attribute));
}