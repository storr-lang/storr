//
// Created by Yunis Yilmaz on 2024-07-25.
//

#ifndef LEXER_H
#define LEXER_H

#include "map"
#include "string"
#include "Token.h"

namespace Token {
    class Lexer {
    public:
        static Token getNextToken();
    };
}; // Lexer

#endif //LEXER_H
