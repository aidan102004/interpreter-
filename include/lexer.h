#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include "token.h"

class Lexer {
private:
    bool error = false;
    const std::unordered_map<char, TokenType> type_register = {
        {'(', TokenType::LEFT_PAREN},
        {')', TokenType::RIGHT_PAREN},
        {'{', TokenType::LEFT_BRACE},
        {'}', TokenType::RIGHT_BRACE},
        {',', TokenType::COMMA},
        {'.', TokenType::DOT},
        {'-', TokenType::MINUS},
        {'+', TokenType::PLUS},
        {';', TokenType::SEMICOLON},
        {'*', TokenType::STAR},
        {'=', TokenType::EQUAL},
        {'!', TokenType::BANG},
        {'<', TokenType::LESS},
        {'>', TokenType::GREATER},
        {'/', TokenType::SLASH},
    };
    std::string read_file(const std::string& file_name);
public:
    inline bool had_error() {return error;};
    std::vector<Token> run_lexer(const std::string& file_name);
    std::pair<int, Token> deduce_type(const std::string& contents, size_t i);

};