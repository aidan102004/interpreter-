#pragma once
#include <string>
#include <variant>
#include "expr.h"

//turn expression into text
struct AstPrinter : ExprVisitor {
    std::string print(const Expr& expr) {
        return expr.accept(*this);
    }

    std::string visitLiteral(const Literal& expr) override {
        if (std::holds_alternative<std::monostate>(expr.val)) {
            return "nil";
        }
        if (auto b = std::get_if<bool>(&expr.val)) {
            return *b ? "true" : "false";
        }
        return "";
    }
};