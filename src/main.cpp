//
// Created by Yunis Yilmaz on 2024-07-25.
//

#include <string>
#include <map>
#include <iostream>
#include "Lexer.h"
#include "Token.h"

using namespace lexer;

int main() {
    std::string tokens[] = {
        "TOKEN_ILLEGAL",
        "TOKEN_EOF", // -1
        "TOKEN_COMMENT", // //

        "literal_begin",
        "TOKEN_IDENTIFIER", // [\w_][\d\w_]*
        "TOKEN_INT", // \d+
        "TOKEN_FLOAT", // [\d]+\.[\d]+
        "TOKEN_BOOL", // (True|False)
        "literal_end",

        "operator_begin",
        "TOKEN_ADD", // +
        "TOKEN_SUB", // -
        "TOKEN_MUL", // *
        "TOKEN_DIV", // /
        "TOKEN_MOD", // %
        "TOKEN_EXP", // ^

        "TOKEN_LNOT", // !
        "TOKEN_LAND", // &
        "TOKEN_LOR", // |
        "TOKEN_LNAND", // !&
        "TOKEN_LNOR", // !|
        "TOKEN_LXOR", // !=

        "TOKEN_LT", // <
        "TOKEN_LTEQUALS", // <=
        "TOKEN_EQUALS", // =
        "TOKEN_GTEQUALS", // >=
        "TOKEN_GT", // >

        "TOKEN_LASSIGN", // :=
        "TOKEN_RASSIGN", // =:

        "TOKEN_COMMA", // ,
        "TOKEN_COLON", // :
        "TOKEN_ARROW", // ->
        "TOKEN_ELIPSIS", // ...

        "TOKEN_LPAREN", // (
        "TOKEN_RPAREN", // )
        "TOKEN_LSQB", // [
        "TOKEN_RSQB", // ]
        "TOKEN_LCUB", // {
        "TOKEN_RCUB", // }
        "TOKEN_NEWLINE", // \n
        "operator_end",

        "keyword_begin",
        "TOKEN_AS",
        "TOKEN_EXPORT",
        "TOKEN_FROM",
        "TOKEN_IMPORT",
        "TOKEN_MATCH",
        "keyword_end",
    };


    Token token(Token::Type::keyword_begin, "");
    while (token.getType() != Token::Type::TOKEN_EOF) {
        token = Lexer::getNextToken();
        std::string f = token.getValue();
        printf("token: %s\nvalue: %s\n\n", tokens[static_cast<int>(token.getType())].c_str(), f.c_str());
    };

    return 0;
};
