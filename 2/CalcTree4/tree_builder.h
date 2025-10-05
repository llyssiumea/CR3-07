/**
 * @file tree_builder.h
 * @brief Построение дерева выражения из обратной польской записи
 * @version 2.0
 * 
 * Класс для построения бинарного дерева арифметического выражения
 * из записи в формате обратной польской нотации (RPN).
 */

#ifndef TREE_BUILDER_H
#define TREE_BUILDER_H

#include "tree_utils.h"
#include <vector>
#include <string>

/**
 * @class TreeBuilder
 * @brief Построитель дерева выражения из RPN
 * 
 * Преобразует выражение в обратной польской записи в бинарное дерево,
 * где листья - операнды (0-9), а внутренние узлы - операции (-1..-6).
 */
class TreeBuilder {
public:
    /**
     * @brief Построение дерева из вектора токенов RPN
     * @param tokens Вектор токенов в обратной польской записи
     * @return Указатель на корень построенного дерева
     * @throws std::runtime_error при некорректном выражении
     */
    static TreeNode* buildFromRPN(const std::vector<std::string>& tokens);
    
    /**
     * @brief Построение дерева из строки RPN
     * @param expression Строка с выражением в RPN (токены разделены пробелами)
     * @return Указатель на корень построенного дерева
     * @throws std::runtime_error при некорректном выражении
     */
    static TreeNode* buildFromString(const std::string& expression);
    
    /**
     * @brief Чтение выражения из файла и построение дерева
     * @param filename Имя файла с выражением в RPN
     * @return Указатель на корень построенного дерева
     * @throws std::runtime_error при ошибках чтения файла
     */
    static TreeNode* buildFromFile(const std::string& filename);

private:
    /**
     * @brief Разбор строки на токены
     * @param expression Входная строка
     * @return Вектор токенов
     */
    static std::vector<std::string> tokenize(const std::string& expression);
    
    /**
     * @brief Валидация токена
     * @param token Токен для проверки
     * @return true если токен корректен
     */
    static bool isValidToken(const std::string& token);
};

#endif // TREE_BUILDER_H