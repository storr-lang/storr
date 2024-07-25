//
// Created by Yunis Yilmaz on 2024-07-25.
//

#include "Token.h"
#include "string"
#include "map"

using namespace std;


const map<Token, string> tokens = {
    {Token::ILLEGAL, "ILLEGAL"},
    {Token::EOF_, "EOF"},
    {Token::COMMENT, "COMMENT"},

    {Token::IDENTIFIER, "IDENTIFIER"},
    {Token::INT, "INT"},
    {Token::FLOAT, "FLOAT"},
    {Token::BOOL, "BOOL"},

    {Token::ADD, "+"},
    {Token::SUB, "-"},
    {Token::MUL, "*"},
    {Token::DIV, "/"},
    {Token::MOD, "%"},
    {Token::EXP, "^"},

    {Token::NOT, "!"},
    {Token::AND, "&"},
    {Token::OR, "||"},
    {Token::NAND, "!&"},
    {Token::NOR, "!|"},
    {Token::XOR, "!="},

    {Token::LT, "<"},
    {Token::LTEQUALS, "<="},
    {Token::EQUALS, "="},
    {Token::GTEQUALS, ">="},
    {Token::GT, "="},

    {Token::LASSIGN, ":="},

    {Token::LPAREN, "("},
    {Token::RPAREN, ")"},
    {Token::LSQB, "["},
    {Token::RSQB, "]"},
    {Token::LCUB, "{"},
    {Token::RCUB, "}"},

    {Token::COMMA, ","},
    {Token::PERIOD, "."},
    {Token::COLON, ":"},

    {Token::IMPORT, "import"},
    {Token::MATCH, "match"},
};

string toString(const Token token) {
    return tokens.find(token)->second;
}

int getPrecedence(const Token token) {
    switch (token) {
        default: return 0;
        case Token::OR:
            return 1;
        case Token::AND:
            return 2;
        case Token::LT:
        case Token::LTEQUALS:
        case Token::EQUALS:
        case Token::GTEQUALS:
        case Token::GT:
        case Token::XOR:
            return 3;
        case Token::ADD:
        case Token::SUB:
            return 4;
        case Token::MUL:
        case Token::DIV:
        case Token::MOD:
            return 5;
    }
}

const map<string, Token> keywords = [] {
    map<string, Token> mp;
    for (int i = static_cast<int>(Token::keyword_begin) + 1; i < static_cast<int>(Token::keyword_end); i++) {
        mp[tokens.at(static_cast<Token>(i))] = static_cast<Token>(i);
    }
    return mp;
}();


Token lookup(const string &identifier) {
    if (keywords.contains(identifier)) {
        return keywords.find(identifier)->second;;
    }
    return Token::IDENTIFIER;
};

bool isLiteral(const Token token) {
    return Token::literal_begin < token && token < Token::literal_end;
};

bool isOperator(const Token token) {
    return Token::operator_begin < token && token < Token::operator_end;
};

bool isKeyword(const string &name) {
    return !keywords.contains(name);
};

bool isIdentifier(const string &name) {
    if (name.empty() || isKeyword(name)) {
        return false;
    }
    for (int i = 0; i < name.size(); i++) {
        if (const char c = name[i]; !isalpha(c) && c != '_' && (i == 0 || !isdigit(c))) {
            return false;
        }
    }
    return true;
};
