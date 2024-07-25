//
// Created by Yunis Yilmaz on 2024-07-25.
//

#ifndef TOKEN_H
#define TOKEN_H


enum class Token : int {
    // Special tokens
    ILLEGAL,
    EOF_,
    COMMENT,

    literal_begin,
    // Identifiers and basic type literals
    IDENTIFIER,
    INT,
    FLOAT,
    BOOL,
    literal_end,

    operator_begin,
    // Operators and delimiters
    ADD,
    SUB,
    MUL,
    DIV,
    MOD,
    EXP,

    NOT,
    AND,
    OR,
    NAND,
    NOR,
    XOR,

    LT,
    LTEQUALS,
    EQUALS,
    GTEQUALS,
    GT,

    LASSIGN,

    LPAREN,
    RPAREN,
    LSQB,
    RSQB,
    LCUB,
    RCUB,

    COMMA,
    PERIOD,
    COLON,
    operator_end,

    keyword_begin,
    // Keywords
    IMPORT,
    MATCH,
    keyword_end,
};


#endif //TOKEN_H
