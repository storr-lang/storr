//
// Created by Yunis Yilmaz on 2024-07-30.
//

#include <iostream>
#include <fstream>
#include <optional>
#include <sstream>
#include <vector>
#include "Lexer.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
    }


    std::stringstream content_stream; {
        std::fstream input(argv[1], std::ios::in);
        content_stream << input.rdbuf();
    }


    for (Lexer lexer(content_stream.str()); const Token &token: lexer.scan()) {
        std::cout << "Token: " << lexer.tokens[static_cast<int>(token.type)];
        if (token.value.has_value()) {
            std::cout << "\nValue: " << token.value.value();
        }
        std::cout << "\n" << std::endl;
    }
}
