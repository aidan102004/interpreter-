#include <iostream>
#include "../include/lexer.h"

//temp helper dict for debugging lexical analysis
#pragma region 
const std::unordered_map<TokenType, std::string> type_names = {
    {TokenType::LEFT_PAREN, "LEFT_PAREN"},   {TokenType::RIGHT_PAREN, "RIGHT_PAREN"},
    {TokenType::LEFT_BRACE, "LEFT_BRACE"},   {TokenType::RIGHT_BRACE, "RIGHT_BRACE"},
    {TokenType::COMMA, "COMMA"},             {TokenType::DOT, "DOT"},
    {TokenType::MINUS, "MINUS"},             {TokenType::PLUS, "PLUS"},
    {TokenType::SEMICOLON, "SEMICOLON"},     {TokenType::STAR, "STAR"},
    {TokenType::EQUAL, "EQUAL"},             {TokenType::EQUAL_EQUAL, "EQUAL_EQUAL"},
    {TokenType::BANG, "BANG"},               {TokenType::BANG_EQUAL, "BANG_EQUAL"},
    {TokenType::LESS, "LESS"},               {TokenType::LESS_EQUAL, "LESS_EQUAL"},
    {TokenType::GREATER, "GREATER"},         {TokenType::GREATER_EQUAL, "GREATER_EQUAL"},
    {TokenType::SLASH, "SLASH"},             {TokenType::STRING, "STRING"},
    {TokenType::NUMBER, "NUMBER"},           {TokenType::IDENTIFIER, "IDENTIFIER"},
    {TokenType::EOF_TOKEN, "EOF"},           {TokenType::UNKNOWN, "UNKNOWN"},
};
#pragma endregion

int main() {
    Lexer lexer;
    std::vector<Token> tokens = lexer.run_lexer("../src/test.abs");

    //testing output
    for (const auto& t : tokens) {
        std::cout << type_names.at(t.type) << " " << t.lexeme <<  " " << t.literal << std::endl;
    }
    return lexer.had_error() ? 65 : 0;
}