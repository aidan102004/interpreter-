#include "../include/lexer.h"
#include <fstream>
#include <sstream>
#include <iostream>

std::string Lexer::read_file(const std::string& file_name) {
    std::ifstream file(file_name);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << file_name << std::endl;
        return "";
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

std::vector<Token> Lexer::run_lexer(const std::string& file_name) {
    std::vector<Token> tokens;
    int line_count = 0;
    std::string contents = read_file(file_name);

    size_t i = 0;
    while (i < contents.size()) {
        auto [increment, token] = deduce_type(contents, i);
        if (token.type == TokenType::UNKNOWN) {   
            char c = token.lexeme[0];
            if (c == '\n') {
                line_count++;
            } else if (c == '\t' || c == ' ' || c == '\r') {
                //skip silently
            } else {
                std::cerr << "[line " << line_count << "] Error: Unexpected character: " << c << "\n";
                error = true;
            }
        }
        tokens.push_back(token);
        i += increment;
    }
    tokens.push_back({TokenType::EOF_TOKEN, "", "null"});
    return tokens;
}

std::pair<int, Token> Lexer::deduce_type(const std::string& contents, size_t i) {
    auto it = type_register.find(contents[i]);
    if (it != type_register.end()) {
        return {1, {it->second, std::string(1, contents[i]), "null"}};
    }
    return {1, {TokenType::UNKNOWN, std::string(1, contents[i]), "null"}};
}