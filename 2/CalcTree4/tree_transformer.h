/**
 * @file tree_transformer.h
 * @brief Преобразование дерева выражений
 * @version 2.0
 * 
 * Класс для преобразования дерева арифметического выражения
 * с заменой операций деления и остатка на вычисленные значения.
 */

#ifndef TREE_TRANSFORMER_H
#define TREE_TRANSFORMER_H

#include "tree_utils.h"

/**
 * @class TreeTransformer
 * @brief Преобразователь дерева выражений
 * 
 * Выполняет преобразование дерева, заменяя все поддеревья
 * с операциями деления (/) и остатка (%) на листовые узлы
 * с вычисленными значениями.
 */
class TreeTransformer {
public:
    /**
     * @brief Преобразование дерева (удаление операций деления и остатка)
     * @param root Корень дерева для преобразования
     * @return Указатель на корень преобразованного дерева
     * 
     * Рекурсивно обходит дерево и заменяет все узлы с операциями
     * деления и остатка на листовые узлы с вычисленными значениями.
     */
    static TreeNode* removeDivisionOperations(TreeNode* root);
    
    /**
     * @brief Вычисление значения поддерева
     * @param root Корень поддерева
     * @return Вычисленное значение
     * @throws std::runtime_error при ошибках вычисления
     */
    static int evaluateSubtree(TreeNode* root);

private:
    /**
     * @brief Рекурсивное вычисление поддерева
     * @param node Текущий узел
     * @return Вычисленное значение
     */
    static int evaluateRecursive(TreeNode* node);
    
    /**
     * @brief Рекурсивное преобразование поддерева
     * @param node Текущий узел
     * @return Преобразованный узел
     */
    static TreeNode* transformRecursive(TreeNode* node);
};

#endif // TREE_TRANSFORMER_H