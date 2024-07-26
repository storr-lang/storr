//
// Created by Yunis Yilmaz on 2024-07-25.
//

#include "Token.h"

namespace lexer {
    Token::Token(const Type type, const std::string &value) {
        this->type = type;
        this->value = value;
    }

    int Token::getPrecedence() const {
        switch (this->type) {
            default:
                return 0;
            case Type::TOKEN_LOR:
                return 1;
            case Type::TOKEN_LAND:
                return 2;
            case Type::TOKEN_LXOR:
            case Type::TOKEN_LT:
            case Type::TOKEN_LTEQUALS:
            case Type::TOKEN_EQUALS:
            case Type::TOKEN_GTEQUALS:
            case Type::TOKEN_GT:
                return 3;
            case Type::TOKEN_ADD:
            case Type::TOKEN_SUB:
                return 4;
            case Type::TOKEN_MUL:
            case Type::TOKEN_DIV:
            case Type::TOKEN_MOD:
                return 5;
            case Type::TOKEN_EXP:
                return 6;
            case Type::TOKEN_LNOT:
                return 7;
        };
    };

    Token::Type Token::getType() const {
        return this->type;
    }

    std::string Token::getValue() const {
        return this->value;
    }

    bool Token::isLiteral() const {
        return Type::literal_begin < this->type && this->type < Type::literal_end;
    }

    bool Token::isKeyword() const {
        return Type::keyword_begin < this->type && this->type < Type::keyword_end;
    }

    bool Token::isOperator() const {
        return Type::operator_begin < this->type && this->type < Type::operator_end;
    }
}; // Token
