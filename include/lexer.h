#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include "token.h"

class Lexer {
private:
    bool error = false;
    int line_count = 0;
    const std::unordered_map<std::string, TokenType> type_register = {
        {"(", TokenType::LEFT_PAREN}, {")", TokenType::RIGHT_PAREN},
        {"{", TokenType::LEFT_BRACE}, {"}", TokenType::RIGHT_BRACE},
        {",", TokenType::COMMA},      {".", TokenType::DOT},
        {"-", TokenType::MINUS},      {"+", TokenType::PLUS},
        {";", TokenType::SEMICOLON},  {"*", TokenType::STAR},
        {"=", TokenType::EQUAL},      {"==", TokenType::EQUAL_EQUAL},
        {"!", TokenType::BANG},       {"!=", TokenType::BANG_EQUAL},
        {"<", TokenType::LESS},       {"<=", TokenType::LESS_EQUAL},
        {">", TokenType::GREATER},    {">=", TokenType::GREATER_EQUAL},
        {"/", TokenType::SLASH}, {"//", TokenType::COMMENT}
    };
    const std::unordered_map<std::string, TokenType> keywords = {
        {"and",    TokenType::AND},    {"class", TokenType::CLASS},
        {"else",   TokenType::ELSE},   {"false", TokenType::FALSE},
        {"for",    TokenType::FOR},    {"fun",   TokenType::FUN},
        {"if",     TokenType::IF},     {"nil",   TokenType::NIL},
        {"or",     TokenType::OR},     {"print", TokenType::PRINT},
        {"return", TokenType::RETURN}, {"super", TokenType::SUPER},
        {"this",   TokenType::THIS},   {"true",  TokenType::TRUE},
        {"var",    TokenType::VAR},    {"while", TokenType::WHILE},
    };
    std::string read_file(const std::string& file_name);
public:
    inline bool had_error() {return error;};
    std::vector<Token> run_lexer(const std::string& file_name);
    std::pair<int, Token> deduce_type(const std::string& contents, size_t i);

};