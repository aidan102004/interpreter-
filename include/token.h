#pragma once

#include <string>

enum class TokenType {
    LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE,
    COMMA, DOT, MINUS, PLUS, SEMICOLON, STAR,
    EQUAL, EQUAL_EQUAL, BANG, BANG_EQUAL,
    LESS, LESS_EQUAL, GREATER, GREATER_EQUAL,
    SLASH, STRING, NUMBER, IDENTIFIER,
    EOF_TOKEN, UNKNOWN
};

struct Token {
    TokenType type;
    std::string lexeme;
    std::string literal;
};