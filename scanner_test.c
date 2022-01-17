/**
 * Implementace překladače jazyka IFJ21
 *
 * @file scanner_test.c
 * @brief Testování lexikálního analyzátoru
 * @brief Slouží pouze pro testování!
 *
 * @author David Konečný (xkonec83)
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "scanner.h"
#include "structures.h"
#include "charAppender.h"

#define BUFFER_SIZE 50

/* Funkce pro barevný výpis */

void red() {
    printf("\033[1;31m");
}

void green() {
    printf("\033[0;32m");
}

void yellow() {
    fprintf(stderr, "\033[0;33m");
}

void cyan() {
    printf("\033[0;36m");
}

void purple() {
    printf("\033[0;35m");
}

/* Reset na výchozí barvu (bílá) */
void reset() {
    printf("\033[0m");
}


int main() {

    token_t token;

    char buffer[BUFFER_SIZE];

    appCharConstructor(&token.attribute);

    int i = 0;

    while (token.type != END) {  

        int ret_val = get_next_token(&token, 0);
        if (ret_val == 99) {
            fprintf(stderr, "Scanner allocation error!\n");
            return 1;
        }
        else if (ret_val == 1) {
            yellow();
            fprintf(stderr, "Invalid lexem!\n");
            reset();
        }
        /*
        else if (ret_val == 3) {
            yellow();
            fprintf(stderr, "Invalid lexem! (random)\n");
            appCharToStr(buffer, BUFFER_SIZE, token.attribute);
            printf("[%s]\n", buffer);
            reset();
        }
        */

        red(); // color

        printf("[TOKEN #%d, type: ", i);

        switch (token.type) {
            case INTEGER:
                printf("integer");
                appCharToStr(buffer, BUFFER_SIZE, token.attribute);
            break;
            case VAR_INIT:
                printf("var_init");
            break;
            case LEFT_BRACKET:
                printf("left_bracket");
            break;
            case RIGHT_BRACKET:
                printf("right_bracket");
            break;
            case STRING_IN_QUOTATION:
                printf("string_in_quotation");
                appCharToStr(buffer, BUFFER_SIZE, token.attribute);
            break;
            case COMMA:
                printf("comma");
            break;
            case HASH:
                printf("hash");
            break;
            case MULTIPLY:
                printf("multiply");
            break;
            case SLASH:
                printf("slash");
            break;
            case DOUBLE_SLASH:
                printf("double_slash");
            break;
            case PLUS:
                printf("plus");
            break;
            case MINUS:
                printf("minus");
            break;
            case DOUBLE_DOT:
                printf("double_dot");
            break;
            case ASSIGN:
                printf("assign");
            break;
            case EQUAL:
                printf("equal");
            break;
            case LESS:
                printf("less");
            break;
            case LESS_EQ:
                printf("less_eq");
            break;
            case GREATER:
                printf("greater");
            break;
            case GREATER_EQ:
                printf("greater_eq");
            break;
            case NOT_EQUAL:
                printf("not_equal");
            break;
            case ID:
                printf("id");
                appCharToStr(buffer, BUFFER_SIZE, token.attribute);
            break;
            case NUMBER:
                printf("number");
                appCharToStr(buffer, BUFFER_SIZE, token.attribute);
            break;
            case DO_KW:
                printf("do_kw");
                appCharToStr(buffer, BUFFER_SIZE, token.attribute);
            break;
            case ELSE_KW:
                printf("else_kw");
                appCharToStr(buffer, BUFFER_SIZE, token.attribute);
            break;
            case END_KW:
                printf("end_kw");
                appCharToStr(buffer, BUFFER_SIZE, token.attribute);
            break;
            case FUNCTION_KW:
                printf("function_kw");
                appCharToStr(buffer, BUFFER_SIZE, token.attribute);
            break;
            case GLOBAL_KW:
                printf("global_kw");
                appCharToStr(buffer, BUFFER_SIZE, token.attribute);
            break;
            case IF_KW:
                printf("if_kw");
                appCharToStr(buffer, BUFFER_SIZE, token.attribute);
            break;
            case LOCAL_KW:
                printf("local_kw");
                appCharToStr(buffer, BUFFER_SIZE, token.attribute);
            break;
            case NIL_KW:
                printf("nil_kw");
                appCharToStr(buffer, BUFFER_SIZE, token.attribute);
            break;
            case REQUIRE_KW:
                printf("require_kw");
                appCharToStr(buffer, BUFFER_SIZE, token.attribute);
            break;
            case RETURN_KW:
                printf("return_kw");
                appCharToStr(buffer, BUFFER_SIZE, token.attribute);
            break;
            case THEN_KW:
                printf("then_kw");
                appCharToStr(buffer, BUFFER_SIZE, token.attribute);
            break;
            case WHILE_KW:
                printf("while_kw");
                appCharToStr(buffer, BUFFER_SIZE, token.attribute);
            break;
            case INTEGER_KW:
                printf("integer_kw");
                appCharToStr(buffer, BUFFER_SIZE, token.attribute);
            break;
            case NUMBER_KW:
                printf("number_kw");
                appCharToStr(buffer, BUFFER_SIZE, token.attribute);
            break;
            case STRING_KW:
                printf("string_kw");
                appCharToStr(buffer, BUFFER_SIZE, token.attribute);
            break;
            case READS_KW:
                printf("reads_kw");
                appCharToStr(buffer, BUFFER_SIZE, token.attribute);
            break;
            case READI_KW:
                printf("readi_kw");
                appCharToStr(buffer, BUFFER_SIZE, token.attribute);
            break;
            case READN_KW:
                printf("readn_kw");
                appCharToStr(buffer, BUFFER_SIZE, token.attribute);
            break;
            case WRITE_KW:
                printf("write_kw");
                appCharToStr(buffer, BUFFER_SIZE, token.attribute);
            break;
            case TOINTEGER_KW:
                printf("tointeger_kw");
                appCharToStr(buffer, BUFFER_SIZE, token.attribute);
            break;
            case SUBSTR_KW:
                printf("substr_kw");
                appCharToStr(buffer, BUFFER_SIZE, token.attribute);
            break;
            case ORD_KW:
                printf("ord_kw");
                appCharToStr(buffer, BUFFER_SIZE, token.attribute);
            break;
            case CHR_KW:
                printf("chr_kw");
                appCharToStr(buffer, BUFFER_SIZE, token.attribute);
            break;
            case ERROR:
                printf("error");
                appCharToStr(buffer, BUFFER_SIZE, token.attribute);
            break;
            case END:
                printf("end");
            break;
            default:
                printf("unknown");
            break;
        }
        printf(", attribute: %s]\n", buffer);
        appCharFromStr(&token.attribute, "");
        strcpy(buffer, "");
        reset(); // color

        i++;
    }

    appCharDestructor(&token.attribute);

    return 0;
}
