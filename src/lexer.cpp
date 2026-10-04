#include "../include/lexer.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cctype>

//helper methods 
static bool is_alpha(char c) {
    return std::isalpha(static_cast<unsigned char>(c)) || c == '_';
}
static bool is_alnum(char c) {
    return std::isalnum(static_cast<unsigned char>(c)) || c == '_';
}

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
    std::string contents = read_file(file_name); //read file to a string

    size_t i = 0;
    while (i < contents.size()) {
        auto [increment, token] = deduce_type(contents, i); //return increment and token
        //handle unknown tokens
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
        if (token.type != TokenType::COMMENT && token.type != TokenType::UNKNOWN) tokens.push_back(token); //add token, skip if unknown or comment
        i += increment; //increment index 
    }
    tokens.push_back({TokenType::EOF_TOKEN, "", "null"}); //end of file
    return tokens;
}

std::pair<int, Token> Lexer::deduce_type(const std::string& contents, size_t i) {
    //handle set token types
    for (size_t len : {2,1}) { //loop through twice in reverse to search for 2 letter words first and 1 letter words in register
        if (len + 1 > contents.size()) continue;
        std::string candidate = contents.substr(i, len);
        auto it = type_register.find(candidate);
        if (it != type_register.end()) { //we find the token in the register
            if (it->second == TokenType::COMMENT) { //if we find a comment, ignore everything after until \n 
                size_t end = contents.find('\n', i);
                if (end == std::string::npos) end = contents.size();
                return {(int)(end - i), {TokenType::COMMENT, "", "null"}};
            }
            return {(int)len, {it->second, candidate, "null"}};
        }
        //iterate down to 1, search for single char tokens
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
    //handle identifiers and reserved keywords
    if (is_alpha(contents[i])) {
        size_t j = i;
        while (j < contents.size() && is_alnum(contents[j])) j++;
        std::string identifier = contents.substr(i, j - i);
        auto kw = keywords.find(identifier); //check if this word is reserved
        TokenType type = (kw == keywords.end()) ? TokenType::IDENTIFIER : kw->second; //set type
        return {(int)(j - i), {type, identifier, "null"}};
    }

    return {1, {TokenType::UNKNOWN, std::string(1, contents[i]), "null"}};
}