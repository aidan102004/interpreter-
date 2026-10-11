#pragma once

#include <memory>
#include <string>
#include <variant>

using LiteralValue = std::variant<std::monostate, bool, double, std::string>;

struct Literal;

struct ExprVisitor {
    virtual ~ExprVisitor() = default;
    virtual std::string visitLiteral(const Literal& expr) = 0;
};

struct Expr {
    virtual ~Expr() = default;
    virtual std::string accept(ExprVisitor& visitor) const = 0;
};

struct Literal : Expr {
    LiteralValue val;
    explicit Literal(LiteralValue v ) : val(std::move(v)) {}
    std::string accept(ExprVisitor& visitor) const override {
        return visitor.visitLiteral(*this);
    }
};