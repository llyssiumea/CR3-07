/**
 * @file tree_builder.cpp
 * @brief Реализация построителя дерева выражения
 * @version 2.0
 */

#include "tree_builder.h"
#include <fstream>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <cctype>

TreeNode* TreeBuilder::buildFromRPN(const std::vector<std::string>& tokens) {
    std::stack<TreeNode*> nodeStack;
    
    for (const std::string& token : tokens) {
        if (!isValidToken(token)) {
            throw std::runtime_error("Некорректный токен: " + token);
        }
        
        if (TreeUtils::isOperator(token)) {
            // Обработка оператора
            if (nodeStack.size() < 2) {
                throw std::runtime_error("Недостаточно операндов для оператора: " + token);
            }
            
            TreeNode* right = nodeStack.top();
            nodeStack.pop();
            TreeNode* left = nodeStack.top();
            nodeStack.pop();
            
            int opCode = TreeUtils::operatorToCode(token[0]);
            TreeNode* opNode = new TreeNode(opCode, left, right);
            nodeStack.push(opNode);
        } else {
            // Обработка операнда
            int value = std::stoi(token);
            if (value < 0 || value > 9) {
                throw std::runtime_error("Операнд вне диапазона 0-9: " + token);
            }
            nodeStack.push(new TreeNode(value));
        }
    }
    
    if (nodeStack.empty()) {
        throw std::runtime_error("Пустое выражение");
    }
    
    if (nodeStack.size() != 1) {
        throw std::runtime_error("Некорректное выражение: остались неиспользованные операнды");
    }
    
    return nodeStack.top();
}

TreeNode* TreeBuilder::buildFromString(const std::string& expression) {
    std::vector<std::string> tokens = tokenize(expression);
    return buildFromRPN(tokens);
}

TreeNode* TreeBuilder::buildFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Не удалось открыть файл: " + filename);
    }
    
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string expression = buffer.str();
    
    if (expression.empty()) {
        throw std::runtime_error("Файл пуст: " + filename);
    }
    
    return buildFromString(expression);
}

std::vector<std::string> TreeBuilder::tokenize(const std::string& expression) {
    std::vector<std::string> tokens;
    std::istringstream iss(expression);
    std::string token;
    
    while (iss >> token) {
        if (!token.empty()) {
            tokens.push_back(token);
        }
    }
    
    return tokens;
}

bool TreeBuilder::isValidToken(const std::string& token) {
    if (token.empty()) return false;
    
    // Проверка оператора
    if (TreeUtils::isOperator(token)) {
        return token.length() == 1;
    }
    
    // Проверка операнда
    if (token.length() == 1 && std::isdigit(token[0])) {
        return true;
    }
    
    return false;
}