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
        if (token.type != TokenType::COMMENT && token.type != TokenType::UNKNOWN) tokens.push_back(token);
        i += increment;
    }
    tokens.push_back({TokenType::EOF_TOKEN, "", "null"});
    return tokens;
}

std::pair<int, Token> Lexer::deduce_type(const std::string& contents, size_t i) {
    //handle set token types
    for (size_t len : {2,1}) {
        if (len + 1 > contents.size()) continue;
        std::string candidate = contents.substr(i, len);
        auto it = type_register.find(candidate);
        if (it != type_register.end()) {
            if (it->second == TokenType::COMMENT) {
                size_t end = contents.find('\n', i);
                if (end == std::string::npos) end = contents.size();
                return {(int)(end - i), {TokenType::COMMENT, "", "null"}};
            }
            return {(int)len, {it->second, candidate, "null"}};
        }
    }
    //handle string literals
    if (contents[i] == '\"') {
        size_t end = contents.find('\"', i+1);
        if (end == std::string::npos) {
            std::cerr << "[line " << line_count << "] Error: Unterminated String: \n";
            return {1, {TokenType::UNKNOWN, std::string(1, contents[i]), "null"}};
        }
        std::string word = contents.substr(i+1, end - 1 -i);
        return {(int)(end-i+1), {TokenType::STRING, word, word}};
    }
    //handle number literals
    if (std::isdigit(static_cast<unsigned char>(contents[i]))) {
        std::string num = "";
        size_t start = i;
        while (std::isdigit(contents[i]) || contents[i] == '.') {
            num += contents[i];
            i++;
        }
        return {(int)(i - start), {TokenType::NUMBER, num, num}};
    }
    return {1, {TokenType::UNKNOWN, std::string(1, contents[i]), "null"}};
}