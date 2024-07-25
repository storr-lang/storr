cmake_minimum_required(VERSION 3.28)
project(storr)

set(CMAKE_CXX_STANDARD 26)

add_executable(storr src/main.cpp
        src/main.cpp
        src/Token.cpp
        src/Token.h
        src/Lexer.cpp
        src/Lexer.h
)
