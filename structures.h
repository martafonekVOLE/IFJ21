/**
 * Implementace překladače jazyka IFJ21
 *
 * @file structures.h
 * @brief Datové typy a struktury překladače jazyka IFJ21
 *
 * @author David Konečný (xkonec83)
 */


#ifndef _STRUCTURES_H
#define _STRUCTURES_H

//#include "charAppender.h" Ne


//typ pro charAppender
typedef struct {
    char* text;
    size_t leght;
    size_t used;
} TmString;



/** @enum state_t
 * @brief Výčtový typ pro stavy konečného automatu
 */
enum state_t {
    START_ST,
    NUMBER_ST,
    SLASH_ST,
    DASH_ST,
    DOUBLE_DASH_ST,
    LINE_COMMENT_ST,
    NOT_COMPLETE_MULT_COMMENT_ST,
    MULT_COMMENT_ST,
    NOT_COMPLETE_MULT_COMMENT_END_ST,
    DOT_ST,
    EQUAL_SIGN_ST,
    LESS_ST,
    GREATER_ST,
    TILDA_ST,
    ID_ST,
    QUOTATION_ST,
    DECIMAL_ST,
    DECIMAL_DOT_ST,
    EXPONENT_FIRST_ST,
    EXPONENT_ST,
    EXPONENT_SIGN_ST
};

/** @enum token_type_t
 * @brief Výčtový typ pro typy tokenu
 */
enum token_type_t {
    INTEGER,
    VAR_INIT,               // :
    LEFT_BRACKET,           // (
    RIGHT_BRACKET,          // )
    STRING_IN_QUOTATION,    // " "
    COMMA,                  // ,
    HASH,                   // #
    MULTIPLY,               // *
    SLASH,                  // /
    DOUBLE_SLASH,           // //
    PLUS,                   // +
    MINUS,                  // -
    DOUBLE_DOT,             // ..
    ASSIGN,                 // =
    EQUAL,                  // ==
    LESS,                   // <
    LESS_EQ,                // <=
    GREATER,                // >
    GREATER_EQ,             // >=
    NOT_EQUAL,              // ~=
    ID,
    NUMBER,
    DO_KW,
    ELSE_KW,
    END_KW,
    FUNCTION_KW,
    GLOBAL_KW,
    IF_KW,
    LOCAL_KW,
    NIL_KW,
    REQUIRE_KW,
    RETURN_KW,
    THEN_KW,
    WHILE_KW,
    INTEGER_KW,
    NUMBER_KW,
    STRING_KW,
    READS_KW,
    READI_KW,
    READN_KW,
    WRITE_KW,
    TOINTEGER_KW,
    SUBSTR_KW,
    ORD_KW,
    CHR_KW,

    ERROR, // Speciální typ pro chybné lexémy
    END // Speciální typ pro EOF
};

/** @struct token_t
 * @brief Datová struktura pro token
 * @var token_t::token_type_t
 * Typ tokenu
 * @var token_t::char*
 * Atribut tokenu
 */
typedef struct {
    TmString attribute;
    enum token_type_t type;
} token_t;

//Navratove hodnoty nejen pro charAppender
typedef enum probiha_debug_nevsimejte_si_me{
    OK_CHAR_APP,
    ERROR_ALLOCATION,
    ERROR_SMALL_ARRAY,
    ERROR_PODTECENI,
} RreturnWalues;


//Rizeni chodu vyhodnoceni vyrazu
typedef enum {
    REDUKCE,
    ADD,
    ROVNASE,
    CHYBA,
    KONEC,//Nebude zajisten jinak
} t_RizeniVyrazu;




#endif