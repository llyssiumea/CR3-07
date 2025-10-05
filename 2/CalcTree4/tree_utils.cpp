/**
 * @file tree_utils.cpp
 * @brief Реализация вспомогательных функций для работы с деревьями выражений
 * @version 2.0
 */

#include "tree_utils.h"
#include <stdexcept>
#include <cmath>

TreeNode::TreeNode(int val, TreeNode* l, TreeNode* r) 
    : value(val), left(l), right(r) {}

TreeNode::~TreeNode() {
    delete left;
    delete right;
}

bool TreeUtils::isOperator(const std::string& token) {
    return token == "+" || token == "-" || token == "*" || 
           token == "/" || token == "%" || token == "^";
}

int TreeUtils::operatorToCode(char op) {
    switch (op) {
        case '+': return -1;
        case '-': return -2;
        case '*': return -3;
        case '/': return -4;
        case '%': return -5;
        case '^': return -6;
        default: 
            throw std::runtime_error("Неизвестный оператор: " + std::string(1, op));
    }
}

char TreeUtils::codeToOperator(int code) {
    switch (code) {
        case -1: return '+';
        case -2: return '-';
        case -3: return '*';
        case -4: return '/';
        case -5: return '%';
        case -6: return '^';
        default: 
            throw std::runtime_error("Неизвестный код операции: " + std::to_string(code));
    }
}

bool TreeUtils::isDivisionOperation(int code) {
    return code == -4 || code == -5; // / или %
}

int TreeUtils::computeOperation(int opCode, int left, int right) {
    switch (opCode) {
        case -1: return left + right;      // +
        case -2: return left - right;      // -
        case -3: return left * right;      // *
        case -4:                          // /
            if (right == 0) throw std::runtime_error("Деление на ноль");
            return left / right;
        case -5:                          // %
            if (right == 0) throw std::runtime_error("Остаток от деления на ноль");
            return left % right;
        case -6: return static_cast<int>(std::pow(left, right)); // ^
        default: 
            throw std::runtime_error("Неизвестная операция: " + std::to_string(opCode));
    }
}