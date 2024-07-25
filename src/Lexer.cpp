//
// Created by Yunis Yilmaz on 2024-07-25.
//

#include "map"
#include "string"
#include "Lexer.h"

namespace Token {
    std::map<std::string, Token::Type> stringLiterals = {
        {"True", Token::Type::TOKEN_BOOL},
        {"False", Token::Type::TOKEN_BOOL},
        {"as", Token::Type::TOKEN_AS},
        {"export", Token::Type::TOKEN_EXPORT},
        {"from", Token::Type::TOKEN_FROM},
        {"import", Token::Type::TOKEN_IMPORT},
        {"match", Token::Type::TOKEN_MATCH},
    };

    std::map<int, Token::Type> operatorChars = {
        {'+', Token::Type::TOKEN_ADD},
        {'-', Token::Type::TOKEN_SUB},
        {'*', Token::Type::TOKEN_MUL},
        {'%', Token::Type::TOKEN_MOD},
        {'^', Token::Type::TOKEN_EXP},
        {'&', Token::Type::TOKEN_LAND},
        {'|', Token::Type::TOKEN_LOR},
        {',', Token::Type::TOKEN_COMMA},
        {'(', Token::Type::TOKEN_LPAREN},
        {')', Token::Type::TOKEN_RPAREN},
        {'[', Token::Type::TOKEN_LSQB},
        {']', Token::Type::TOKEN_RSQB},
        {'{', Token::Type::TOKEN_LCUB},
        {'}', Token::Type::TOKEN_RCUB},
    };

    Token Lexer::getNextToken() {
        int lastChar = ' ';
        while (isspace(lastChar)) {
            lastChar = getchar();
        };

        if (isalpha(lastChar) || lastChar == '_') {
            std::string identifier;
            do {
                identifier += static_cast<char>(lastChar);
                lastChar = getchar();
            } while (isalnum(lastChar) || lastChar == '_');
            ungetc(lastChar, stdin);
            if (stringLiterals.contains(identifier)) {
                return Token{stringLiterals.at(identifier), identifier};
            };
            return Token{Token::Type::TOKEN_IDENTIFIER, identifier};
        };

        if (isdigit(lastChar)) {
            std::string number;
            int dotCount = 0;
            do {
                number += static_cast<char>(lastChar);
                lastChar = getchar();
                if (lastChar == '.') {
                    dotCount++;
                };
            } while (isdigit(lastChar) || lastChar == '.');
            ungetc(lastChar, stdin);
            switch (dotCount) {
                case 0:
                    return Token{Token::Type::TOKEN_INT, number};
                case 1:
                    return Token{Token::Type::TOKEN_FLOAT, number};
                default:
                    return Token{Token::Type::TOKEN_ILLEGAL, number};
            };
        };

        if (lastChar == '/') {
            const int currentChar = getchar();
            if (currentChar == '/') {
                do {
                    lastChar = getchar();
                } while (lastChar != EOF && lastChar != '\n' && lastChar != '\r');
                return Token{Token::Type::TOKEN_COMMENT, ""};
            };
            ungetc(currentChar, stdin);
            return Token{Token::Type::TOKEN_DIV, "/"};
        };

        if (lastChar == '!') {
            switch (const int currentChar = getchar()) {
                case '&':
                    return Token{Token::Type::TOKEN_LNAND, "!&"};
                case '|':
                    return Token{Token::Type::TOKEN_LNOR, "!|"};
                case '=':
                    return Token{Token::Type::TOKEN_LXOR, "!="};
                default:
                    ungetc(currentChar, stdin);
                    return Token{Token::Type::TOKEN_LNOT, "!"};
            };
        };

        if (lastChar == '<') {
            const int currentChar = getchar();
            if (currentChar == '=') {
                return Token{Token::Type::TOKEN_LTEQUALS, "<="};
            };
            ungetc(currentChar, stdin);
            return Token{Token::Type::TOKEN_LT, "<"};
        };

        if (lastChar == '>') {
            const int currentChar = getchar();
            if (currentChar == '=') {
                return Token{Token::Type::TOKEN_GTEQUALS, ">="};
            };
            ungetc(currentChar, stdin);
            return Token{Token::Type::TOKEN_GT, ">"};
        };

        if (lastChar == ':') {
            const int currentChar = getchar();
            if (currentChar == '=') {
                return Token{Token::Type::TOKEN_LASSIGN, ":="};
            };
            ungetc(currentChar, stdin);
            return Token{Token::Type::TOKEN_COLON, ":"};
        };

        if (lastChar == '=') {
            const int currentChar = getchar();
            if (currentChar == ':') {
                return Token{Token::Type::TOKEN_RASSIGN, "=:"};
            };
            ungetc(currentChar, stdin);
            return Token{Token::Type::TOKEN_EQUALS, "="};
        };

        if (lastChar == '.') {
            if (getchar() == '.' && getchar() == '.') {
                return Token{Token::Type::TOKEN_ELIPSIS, "..."};
            };
            return Token{Token::Type::TOKEN_ILLEGAL, "."};
        };

        const std::string str(1, static_cast<char>(lastChar));

        if (operatorChars.contains(lastChar)) {
            return Token{operatorChars.at(lastChar), str};
        };

        if (lastChar == EOF) {
            return Token{Token::Type::TOKEN_EOF, "EOF"};
        };

        return Token{Token::Type::TOKEN_ILLEGAL, str};
    };
}; // Lexer
