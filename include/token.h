#pragma once

#include <string>

enum TokenType {
    VAR,
    IDENTIFIER,
    STRING,
    LEFT_PAREN,
    RIGHT_PAREN
};

struct Token {
    TokenType type;
    std::string lexeme;
    std::string literal;
};