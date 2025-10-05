/**
 * @file main.cpp
 * @brief Основная программа для работы с деревьями выражений
 * @version 2.0
 * 
 * Главный модуль программы, содержащий пользовательский интерфейс
 * и демонстрацию работы с деревьями арифметических выражений.
 */

#include <iostream>
#include <iomanip>
#include "tree_builder.h"
#include "tree_transformer.h"
#include "tree_utils.h"

/**
 * @brief Вывод дерева в виде инфиксного выражения
 * @param root Корень дерева
 */
void printInfixExpression(TreeNode* root) {
    if (root == nullptr) return;
    
    bool isOperator = (root->value < 0);
    
    if (isOperator) {
        std::cout << "(";
    }
    
    printInfixExpression(root->left);
    
    if (root->value >= 0) {
        std::cout << root->value;
    } else {
        std::cout << " " << TreeUtils::codeToOperator(root->value) << " ";
    }
    
    printInfixExpression(root->right);
    
    if (isOperator) {
        std::cout << ")";
    }
}

/**
 * @brief Вывод дерева в структурном виде
 * @param root Корень дерева
 * @param level Текущий уровень вложенности
 * @param prefix Префикс для отображения
 */
void printTreeStructure(TreeNode* root, int level = 0, const std::string& prefix = "") {
    if (root == nullptr) return;
    
    // Вывод правого поддерева
    printTreeStructure(root->right, level + 1, "┌──");
    
    // Вывод текущего узла
    std::cout << std::string(level * 3, ' ') << prefix;
    if (root->value >= 0) {
        std::cout << root->value;
    } else {
        std::cout << TreeUtils::codeToOperator(root->value);
    }
    std::cout << std::endl;
    
    // Вывод левого поддерева
    printTreeStructure(root->left, level + 1, "└──");
}

/**
 * @brief Основная функция программы
 * @return Код завершения программы
 */
int main() {
    try {
        std::string filename = "filename.txt";
        
        std::cout << "=== ДЕРЕВО АРИФМЕТИЧЕСКОГО ВЫРАЖЕНИЯ ===" << std::endl;
        std::cout << "Файл с выражением: " << filename << std::endl;
        std::cout << std::endl;
        
        // Построение дерева из файла
        TreeNode* root = TreeBuilder::buildFromFile(filename);
        
        std::cout << "ИСХОДНОЕ ДЕРЕВО:" << std::endl;
        std::cout << "Инфиксная запись: ";
        printInfixExpression(root);
        std::cout << std::endl;
        
        std::cout << "Структура дерева:" << std::endl;
        printTreeStructure(root);
        std::cout << std::endl;
        
        std::cout << "Вычисленное значение: " << TreeTransformer::evaluateSubtree(root) << std::endl;
        std::cout << std::endl;
        
        // Преобразование дерева
        TreeNode* transformedRoot = TreeTransformer::removeDivisionOperations(root);
        
        std::cout << "ПРЕОБРАЗОВАННОЕ ДЕРЕВО:" << std::endl;
        std::cout << "Инфиксная запись: ";
        printInfixExpression(transformedRoot);
        std::cout << std::endl;
        
        std::cout << "Структура дерева:" << std::endl;
        printTreeStructure(transformedRoot);
        std::cout << std::endl;
        
        std::cout << "Вычисленное значение: " << TreeTransformer::evaluateSubtree(transformedRoot) << std::endl;
        std::cout << std::endl;
        
        // Вывод указателя на корень (требование задачи)
        std::cout << "УКАЗАТЕЛЬ НА КОРЕНЬ ДЕРЕВА: " << transformedRoot << std::endl;
        std::cout << std::endl;
        
        // Освобождение памяти
        delete transformedRoot;
        
        std::cout << "Программа завершена успешно." << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "ОШИБКА: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}

// cd /Users/alyssa/CR3-07/2/CalcTree4
// g++ -std=c++11 -o expression_tree main.cpp tree_builder.cpp tree_transformer.cpp tree_utils.cpp
// ./expression_tree