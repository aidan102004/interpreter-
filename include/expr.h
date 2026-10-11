#pragma once

#include <memory>
#include <string>
#include <variant>

//alias storing all values a literal could be, monostate stores nil
using LiteralValue = std::variant<std::monostate, bool, double, std::string>;

struct Literal; //forward dec

//visitor class for accessing methods and printing ast
struct ExprVisitor {
    virtual ~ExprVisitor() = default;
    virtual std::string visitLiteral(const Literal& expr) = 0;
};

//base class for an expression
struct Expr {
    virtual ~Expr() = default;
    virtual std::string accept(ExprVisitor& visitor) const = 0;
};

//literal class inherits from expression
struct Literal : Expr {
    LiteralValue val;
    explicit Literal(LiteralValue v ) : val(std::move(v)) {} //sets the member directly 
    std::string accept(ExprVisitor& visitor) const override {
        return visitor.visitLiteral(*this); //passes the literal itself to visitor
    }
};