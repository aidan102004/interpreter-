#include "../include/lexer.h"
#include <fstream>
#include <sstream>
#include <iostream>

std::string Lexer::read_file(const std::string& file_name) {
    std::ifstream file(file_name);
    if (!file.is_open()) {
        std::cerr << "Error opening file" << std::endl;
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}
std::vector<Token> Lexer::run_lexer(const std::string& file_name) {
    std::vector<Token> tokens;
    std::string contents = read_file(file_name);
    if (contents.empty()) {
        std::cout << "EOF  null" << std::endl;
    }
    int i = 0;
    while (i < contents.size()) {
        auto it = type_register.find(std::string(1, file_name[i]));
        if (it != type_register.end())
            
    }
}