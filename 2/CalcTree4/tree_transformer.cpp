/**
 * @file tree_transformer.cpp
 * @brief Реализация преобразователя дерева выражений
 * @version 2.0
 */

#include "tree_transformer.h"
#include <stdexcept>

TreeNode* TreeTransformer::removeDivisionOperations(TreeNode* root) {
    return transformRecursive(root);
}

int TreeTransformer::evaluateSubtree(TreeNode* root) {
    return evaluateRecursive(root);
}

int TreeTransformer::evaluateRecursive(TreeNode* node) {
    if (node == nullptr) {
        throw std::runtime_error("Попытка вычислить nullptr узел");
    }
    
    // Если узел - операнд, возвращаем его значение
    if (node->value >= 0) {
        return node->value;
    }
    
    // Рекурсивно вычисляем левое и правое поддеревья
    int leftVal = evaluateRecursive(node->left);
    int rightVal = evaluateRecursive(node->right);
    
    // Выполняем операцию
    return TreeUtils::computeOperation(node->value, leftVal, rightVal);
}

TreeNode* TreeTransformer::transformRecursive(TreeNode* node) {
    if (node == nullptr) {
        return nullptr;
    }
    
    // Если узел - операнд, возвращаем без изменений
    if (node->value >= 0) {
        return node;
    }
    
    // Рекурсивно преобразуем поддеревья
    node->left = transformRecursive(node->left);
    node->right = transformRecursive(node->right);
    
    // Если операция деления или остатка, заменяем на вычисленное значение
    if (TreeUtils::isDivisionOperation(node->value)) {
        try {
            int result = evaluateRecursive(node);
            
            // Создаем новый листовой узел
            TreeNode* newNode = new TreeNode(result);
            
            // Удаляем старый узел (но сохраняем его поддеревья для удаления)
            TreeNode* oldLeft = node->left;
            TreeNode* oldRight = node->right;
            
            // Обнуляем указатели, чтобы деструктор не удалил поддеревья
            node->left = nullptr;
            node->right = nullptr;
            delete node;
            
            // Рекурсивно удаляем старые поддеревья
            delete oldLeft;
            delete oldRight;
            
            return newNode;
        } catch (const std::runtime_error& e) {
            // В случае ошибки вычисления (например, деление на ноль)
            // оставляем узел без изменений
            return node;
        }
    }
    
    return node;
}