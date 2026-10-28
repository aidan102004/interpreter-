#pragma once
#include <memory>
#include <vector>
#include "token.h"
#include "expr.h"

/*read token list and build an expr*/
class Parser {
public:
    explicit Parser(std::vector<Token> tokens)
        : tokens(std::move(tokens)) {}

    std::unique_ptr<Expr> parse() {
        return expression();
    }

private:
    std::vector<Token> tokens;
    size_t current = 0; //index

    std::unique_ptr<Expr> expression() {
        return primary();  
    }

    std::unique_ptr<Expr> primary() {
        if (match(TokenType::FALSE)) return std::make_unique<Literal>(false);
        if (match(TokenType::TRUE))  return std::make_unique<Literal>(true);
        if (match(TokenType::NIL))   return std::make_unique<Literal>(std::monostate{});
        if (match(TokenType::NUMBER) || match(TokenType::STRING)) return std::make_unique<Literal>(previous().literal);
        return nullptr;    
    }

    bool match(TokenType type) {
        if (check(type)) {
            advance();
            return true;
        }
        return false;
    }

    bool check(TokenType type) const {
        if (isAtEnd()) return false;
        return peek().type == type;
    }

    const Token& advance() {
        if (!isAtEnd()) current++;
        return previous();
    }

    bool isAtEnd() const {
        return peek().type == TokenType::EOF_TOKEN;
    }

    const Token& peek() const {
        return tokens[current];
    }

    const Token& previous() const {
        return tokens[current - 1];
    }
};