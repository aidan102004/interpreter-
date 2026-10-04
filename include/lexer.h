#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include "token.h"

class Lexer {
private:
    std::unordered_map<std::string, TokenType> type_register;
    std::string read_file(const std::string& file_name);
public:
    std::vector<Token> run_lexer(const std::string& file_name);
};