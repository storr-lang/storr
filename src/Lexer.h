//
// Created by Yunis Yilmaz on 2024-07-31.
//

#ifndef LEXER_H
#define LEXER_H
#include <map>
#include <optional>
#include <vector>

enum class TokenType : uint_fast8_t;

struct Token {
    TokenType type;
    std::optional<std::string> value;
};

class Lexer {
public:
    explicit Lexer(const std::string &source);
    std::vector<std::string> tokens;
    [[nodiscard]] std::vector<Token> scan();

private:
    [[nodiscard]] std::optional<char> peek(int n) const;
    [[nodiscard]] char dequeue();

    std::string m_source;
    int m_index;
    std::map<std::string, TokenType> m_identifiers;
    std::map<char, TokenType> m_operators;
};


#endif //LEXER_H
