//
// Created by Yunis Yilmaz on 2024-07-30.
//

#include <iostream>
#include <fstream>
#include <map>
#include <optional>
#include <sstream>
#include <vector>

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

std::vector<std::string> tokens = {
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

std::map<std::string, TokenType> identifiers = {
    {"Infinity", TokenType::FloatingPoint},
    {"NaN", TokenType::FloatingPoint},
    {"True", TokenType::Boolean},
    {"False", TokenType::Boolean},
    {"as", TokenType::As},
    {"from", TokenType::From},
    {"import", TokenType::Import},
    {"of", TokenType::Of},
};

std::map<char, TokenType> operators = {
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

struct Token {
    TokenType type;
    std::optional<std::string> value;
};

std::vector<Token> scan(const std::string &content) {
    std::vector<Token> tokens;
    for (int i = 0; i < content.length(); i++) {
        std::string buffer;
        char c = content.at(i);

        // ignore whitespace
        if (isspace(c) && !std::string("\r\n").contains(c)) continue;

        // line separator
        if (std::string("\r\n").contains(c)) {
            while (isspace(c) && i + 1 < content.length()) c = content.at(++i);
            tokens.push_back(Token{TokenType::LineSeparator, std::nullopt});
            if (i == content.length() - 1) break;
            i--;
            continue;
        }

        // comment
        if (c == '/' && i + 1 < content.length() && content.at(i + 1) == '/') {
            buffer.push_back(c);
            do{
                c = content.at(++i);
                buffer.push_back(c);
            }while (!std::string("\r\n").contains(c) && i + 1 < content.length()) ;
            if (std::string("\r\n").contains(buffer.back())) buffer.pop_back();
            tokens.push_back(Token{TokenType::Comment, buffer});
            if (i == content.length() - 1) break;
            i--;
            buffer.clear();
            continue;
        }

        // identifier
        if (c == '_' || isalpha(c)) {
            buffer.push_back(c);
            do{
                c = content.at(++i);
                buffer.push_back(c);
            } while ((c == '_' || isalnum(c)) && i + 1 < content.length()) ;
            i--;
            buffer.pop_back();

            if (identifiers.contains(buffer)) tokens.push_back(Token{identifiers[buffer], buffer});
            else tokens.push_back(Token{TokenType::Identifier, buffer});

            buffer.clear();
            continue;
        }

        // numbers
        if (isdigit(c)) {
            buffer.push_back(c);
            int dot_count = 0;
            do {
                c = content.at(++i);
                buffer.push_back(c);


                if (c == '.') dot_count++;
                if (dot_count > 1) {
                    tokens.push_back(Token{TokenType::Illegal, buffer});
                    break;
                }
            }while ((isdigit(c) || c == '_' || c == '.') && i + 1 < content.length());
            i--;
            buffer.pop_back();

            if (buffer.find('.') != std::string::npos) {
                tokens.push_back(Token{TokenType::FloatingPoint, buffer});
            } else tokens.push_back(Token{TokenType::Integer, buffer});

            buffer.clear();
            continue;
        }

        // character
        // unimplemented
        if (c == '\'') {
            tokens.push_back(Token{TokenType::Illegal, "'"});
            break;
        }

        // string
        if (c == '"' && i + 1 < content.length()) {
            do {
                buffer.push_back(c);
                c = content.at(++i);
            } while (c != '"' && i < content.length());
            buffer.push_back(c);

            tokens.push_back(Token{TokenType::String, buffer});

            buffer.clear();
            continue;
        }

        // operators and delimiters
        if (c == ':' && i + 1 < content.length()) {
            c = content.at(++i);
            if (c == '=') tokens.push_back(Token{TokenType::RAssign, ":="});
            else {
                tokens.push_back(Token{TokenType::Colon, ":"});
                i--;
            }
            continue;
        }
        if (c == '=' && i + 1 < content.length()) {
            c = content.at(++i);
            switch (c) {
                case ':':
                    tokens.push_back(Token{TokenType::LAssign, ":="});
                    break;
                case '>':
                    tokens.push_back(Token{TokenType::Implies, "=>"});
                    break;
                default:
                    tokens.push_back(Token{TokenType::Equals, "="});
                    i--;
                    break;
            }
            continue;
        }
        if (c == '!' && i + 1 < content.length()) {
            c = content.at(++i);
            switch (c) {
                case '=':
                    tokens.push_back(Token{TokenType::NEquals, "!="});
                    break;
                case '&':
                    tokens.push_back(Token{TokenType::NAnd, "!&"});
                    break;
                case '|':
                    tokens.push_back(Token{TokenType::NOr, "!|"});
                    break;
                default:
                    tokens.push_back(Token{TokenType::Not, "!"});
                    i--;
                    break;
            }
            continue;
        }
        if (c == '<' && i + 1 < content.length()) {
            c = content.at(++i);
            if (c == '=') tokens.push_back(Token{TokenType::LTEquals, "<="});
            else {
                tokens.push_back(Token{TokenType::LessThan, "<"});
                i--;
            }
            continue;
        }
        if (c == '>' && i + 1 < content.length()) {
            c = content.at(++i);
            if (c == '=')tokens.push_back(Token{TokenType::GTEquals, ">="});
            else {
                tokens.push_back(Token{TokenType::GreaterThan, ">"});
                i--;
            }
            continue;
        }
        if (c == '-' && i + 1 < content.length()) {
            c = content.at(++i);
            if (c == '>') tokens.push_back(Token{TokenType::Maplet, "->"});
            else {
                tokens.push_back(Token{TokenType::Subtract, "-"});
                i--;
            }
            continue;
        }
        if (c == '.' && i + 1 < content.length()) {
            c = content.at(++i);
            if (c == '.' && i + 1 < content.length() && content.at(++i) == '.')
                tokens.push_back(Token{
                    TokenType::Ellipsis, "..."
                });
            else {
                tokens.push_back(Token{TokenType::Illegal, std::nullopt});
                break;
            }
            continue;
        }
        if (operators.contains(c)) {
            tokens.push_back(Token{operators[c], std::string(1, c)});
            continue;
        }

        // illegal
        buffer.push_back(c);
        tokens.push_back(Token{TokenType::Illegal, buffer});
        break;
    }
    tokens.push_back(Token{TokenType::EndOfFile, std::nullopt});
    return tokens;
}


int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
    }

    std::stringstream content_stream; {
        std::fstream input(argv[1], std::ios::in);
        content_stream << input.rdbuf();
    }

    for (const Token &token: scan(content_stream.str())) {
        std::cout << "Token: " << tokens[static_cast<int>(token.type)];
        if (token.value.has_value()) {
            std::cout << "\nValue: " << token.value.value();
        }
        std::cout << "\n" << std::endl;
    }
}
