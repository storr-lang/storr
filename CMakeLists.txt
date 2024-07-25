cmake_minimum_required(VERSION 3.28)
project(storr)

set(CMAKE_CXX_STANDARD 26)

add_executable(storr src/main.cpp
        src/main.cpp
        src/compiler/frontend/Token.cpp
        src/compiler/frontend/Token.h
        src/compiler/frontend/Lexer.cpp
        src/compiler/frontend/Lexer.h
        src/compiler/frontend/Parser.cpp
        src/compiler/frontend/Parser.h
        src/compiler/frontend/AST.cpp
        src/compiler/frontend/AST.h)
