//
// Created by Yunis Yilmaz on 2024-07-31.
//

#include "Lexer.h"
#include <map>

enum class TokenType : uint_fast8_t {
    EndOfFile,
    Illegal,
    LineSeparator, // (\s*(\r\n|\r|\n))+
    Comment, // //.*(?=\r\n|\r|\n)

    Identifier, // [_\w][_\w\d]*
    Integer, // [\d][_\d]*
    FloatingPoint, // ([\d][_\d]*\.[\d][_\d]*|Infinity|NaN)
    Boolean, // (True|False)
    Character, // '.' unimplemented
    String, // ".*"

    Add, // +
    Subtract, // -
    Multiply, // *
    Divide, // /
    Modulo, // %
    Exponent, // ^

    Equals, // =
    LAssign, // :=
    RAssign, // =:
    NEquals, // !=

    LessThan, // <
    GreaterThan, // >
    LTEquals, // <=
    GTEquals, // >=

    Not, // !
    And, // &
    Or, // |
    NAnd, // !&
    NOr, // !|
    Implies, // =>

    Maplet, // ->

    LParenthesis, // (
    RParenthesis, // )
    LBracket, // [
    RBracket, // ]
    LBrace, // {
    RBrace, // }
    Colon, // :
    Comma, // ,
    Ellipsis, // ...

    As, // as
    From, // from
    Import, // import
    Of, // of
};

Lexer::Lexer(const std::string &source) {
    m_source = source;
    m_index = 0;

    tokens = {
        "EndOfFile",
        "Illegal",
        "LineSeparator",
        "Comment",
        "Identifier",
        "Integer",
        "FloatingPoint",
        "Boolean",
        "Character",
        "String",
        "Add",
        "Subtract",
        "Multiply",
        "Divide",
        "Modulo",
        "Exponent",
        "Equals",
        "LAssign",
        "RAssign",
        "NEquals",
        "LessThan",
        "GreaterThan",
        "LTEquals",
        "GTEquals",
        "Not",
        "And",
        "Or",
        "NAnd",
        "NOr",
        "Implies",
        "Maplet",
        "LParenthesis",
        "RParenthesis",
        "LBracket",
        "RBracket",
        "LBrace",
        "RBrace",
        "Colon",
        "Comma",
        "Ellipsis",
        "As",
        "From",
        "Import",
        "Of",
    };

    m_identifiers = {
        {"Infinity", TokenType::FloatingPoint},
        {"NaN", TokenType::FloatingPoint},
        {"True", TokenType::Boolean},
        {"False", TokenType::Boolean},
        {"as", TokenType::As},
        {"from", TokenType::From},
        {"import", TokenType::Import},
        {"of", TokenType::Of},
    };

    m_operators = {
        {'+', TokenType::Add},
        {'-', TokenType::Subtract},
        {'*', TokenType::Multiply},
        {'/', TokenType::Divide},
        {'%', TokenType::Modulo},
        {'^', TokenType::Exponent},
        {'=', TokenType::Equals},
        {'<', TokenType::LessThan},
        {'>', TokenType::GreaterThan},
        {'!', TokenType::Not},
        {'&', TokenType::And},
        {'|', TokenType::Or},
        {'(', TokenType::LParenthesis},
        {')', TokenType::RParenthesis},
        {'[', TokenType::LBracket},
        {']', TokenType::RBracket},
        {'{', TokenType::LBrace},
        {'}', TokenType::RBrace},
        {':', TokenType::Colon},
        {',', TokenType::Comma},
    };
}

std::optional<char> Lexer::peek(const int n = 1) const {
    if (m_index + n <= m_source.length()) return m_source.at(m_index);
    return std::nullopt;
}

char Lexer::dequeue() {
    return m_source.at(m_index++);
}

std::vector<Token> Lexer::scan() {
    std::vector<Token> tokens;
    std::string buffer;
    while (peek().has_value()) {
        char c = dequeue();

        // ignore whitespace
        if (isspace(c) && !std::string("\r\n").contains(c)) continue;

        // comment
        if (c == '/' && peek().has_value() && peek().value() == '/') {
            buffer.push_back(c);
            while (peek().has_value() && !std::string("\r\n").contains(c)) {
                c = dequeue();
                buffer.push_back(c);
            }
            if (std::string("\r\n").contains(buffer.back())) {
                buffer.pop_back();
                m_index--;
            }
            tokens.push_back(Token{TokenType::Comment, buffer});
            buffer.clear();
            continue;
        }

        // line separator
        if (std::string("\r\n").contains(c)) {
            while (peek().has_value() && isspace(peek().value())) m_index++;
            tokens.push_back(Token{TokenType::LineSeparator, std::nullopt});
            continue;
        }

        // text
        if (c == '_' || isalpha(c)) {
            buffer.push_back(c);
            while (peek().has_value() && (peek().value() == '_' || isalnum(peek().value()))) {
                buffer.push_back(dequeue());
            }
            if (m_identifiers.contains(buffer)) {
                tokens.push_back(Token{m_identifiers[buffer], buffer});
            } else {
                tokens.push_back(Token{TokenType::Identifier, buffer});
            }
            buffer.clear();
            continue;
        }

        // numbers
        if (isdigit(c)) {
            buffer.push_back(c);
            while (peek().has_value() && (peek().value() == '_' || isdigit(peek().value()))) {
                buffer.push_back(dequeue());
            }
            if (peek().has_value() && peek().value() == '.') {
                buffer.push_back(dequeue());
                while (peek().has_value() && (peek().value() == '_' || isdigit(peek().value()))) {
                    buffer.push_back(dequeue());
                }
                tokens.push_back(Token{TokenType::FloatingPoint, buffer});
            } else {
                tokens.push_back(Token{TokenType::Integer, buffer});
            }
            buffer.clear();
            continue;
        }

        // character
        // unimplemented
        if (c == '\'') {
            tokens.push_back(Token{TokenType::Illegal, "'"});
            continue;
        }

        // string
        if (c == '"') {
            buffer.push_back(c);
            while (peek().has_value() && peek().value() != '"' && !std::string("\r\n").contains(peek().value())) {
                buffer.push_back(dequeue());
            }
            if (peek().has_value()) {
                buffer.push_back(dequeue());
                tokens.push_back(Token{TokenType::String, buffer});
            } else {
                tokens.push_back(Token{TokenType::Illegal, buffer});
            }
            buffer.clear();
            continue;
        }

        // operators
        if (c == ':' && peek().has_value() && peek().value() == '=') {
            m_index++;
            tokens.push_back(Token{TokenType::LAssign, ":="});
            continue;
        }
        if (c == '=' && peek().has_value()) {
            switch (peek().value()) {
                case ':':
                    m_index++;
                    tokens.push_back(Token{TokenType::RAssign, "=:"});
                    break;
                case '>':
                    m_index++;
                    tokens.push_back(Token{TokenType::Maplet, "=>"});
                    break;
                default:
                    tokens.push_back(Token{TokenType::Equals, "="});
            }
            continue;
        }
        if (c == '!' && peek().has_value()) {
            switch (peek().value()) {
                case '=':
                    m_index++;
                    tokens.push_back(Token{TokenType::NEquals, "!="});
                    break;
                case '&':
                    m_index++;
                    tokens.push_back(Token{TokenType::NAnd, "!&"});
                    break;
                case '|':
                    m_index++;
                    tokens.push_back(Token{TokenType::NOr, "!|"});
                    break;
                default:
                    tokens.push_back(Token{TokenType::Illegal, "!"});
            }
            continue;
        }
        if (c == '<' && peek().has_value() && peek().value() == '=') {
            m_index++;
            tokens.push_back(Token{TokenType::LTEquals, "<="});
            continue;
        }
        if (c == '>' && peek().has_value() && peek().value() == '=') {
            m_index++;
            tokens.push_back(Token{TokenType::GTEquals, ">="});
            continue;
        }
        if (c == '-' && peek().has_value() && peek().value() == '>') {
            m_index++;
            tokens.push_back(Token{TokenType::Implies, "->"});
            continue;
        }
        if (c == '.' && peek(2).has_value() && peek().value() == '.' && peek(2).value() == '.') {
            m_index += 2;
            tokens.push_back(Token{TokenType::Ellipsis, "..."});
            continue;
        }
        if (m_operators.contains(c)) {
            tokens.push_back(Token{m_operators[c], std::string(1, c)});
            continue;
        }

        // illegal
        buffer.push_back(c);
        tokens.push_back(Token{TokenType::Illegal, buffer});
        buffer.clear();
    }
    tokens.push_back(Token{TokenType::EndOfFile, std::nullopt});
    return tokens;
}
