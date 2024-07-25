//
// Created by Yunis Yilmaz on 2024-07-25.
//

#ifndef TOKEN_H
#define TOKEN_H

#include <string>

namespace Token {
    class Token {
    public:
        enum class Type : size_t {
            TOKEN_ILLEGAL,
            TOKEN_EOF, // -1
            TOKEN_COMMENT, // //

            literal_begin,
            TOKEN_IDENTIFIER, // [\w_][\d\w_]*
            TOKEN_INT, // \d+
            TOKEN_FLOAT, // [\d]+\.[\d]+
            TOKEN_BOOL, // (True|False)
            literal_end,

            operator_begin,
            TOKEN_ADD, // +
            TOKEN_SUB, // -
            TOKEN_MUL, // *
            TOKEN_DIV, // /
            TOKEN_MOD, // %
            TOKEN_EXP, // ^

            TOKEN_LNOT, // !
            TOKEN_LAND, // &
            TOKEN_LOR, // |
            TOKEN_LNAND, // !&
            TOKEN_LNOR, // !|
            TOKEN_LXOR, // !=

            TOKEN_LT, // <
            TOKEN_LTEQUALS, // <=
            TOKEN_EQUALS, // =
            TOKEN_GTEQUALS, // >=
            TOKEN_GT, // >

            TOKEN_LASSIGN, // :=
            TOKEN_RASSIGN, // =:

            TOKEN_COMMA, // ,
            TOKEN_COLON, // :
            // TOKEN_ARROW,   // ->
            TOKEN_ELIPSIS, // ...

            TOKEN_LPAREN, // (
            TOKEN_RPAREN, // )
            TOKEN_LSQB, // [
            TOKEN_RSQB, // ]
            TOKEN_LCUB, // {
            TOKEN_RCUB, // }
            operator_end,

            keyword_begin,
            TOKEN_AS,
            TOKEN_EXPORT,
            TOKEN_FROM,
            TOKEN_IMPORT,
            TOKEN_MATCH,
            keyword_end,
        };

        Token(Type type, const std::string &value);

        [[nodiscard]] Type getType() const;

        [[nodiscard]] std::string getValue() const;

        [[nodiscard]] int getPrecedence() const;

        [[nodiscard]] bool isLiteral() const;

        [[nodiscard]] bool isOperator() const;

        [[nodiscard]] bool isKeyword() const;

    private:
        Type type;
        std::string value;
    };
}; // Token

#endif //TOKEN_H
