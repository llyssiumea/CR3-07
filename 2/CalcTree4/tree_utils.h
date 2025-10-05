/**
 * @file tree_utils.h
 * @brief Вспомогательные функции и структуры для работы с деревьями выражений
 * @version 2.0
 * 
 * Определяет структуру узла дерева и вспомогательные функции
 * для работы с арифметическими выражениями.
 */

#ifndef TREE_UTILS_H
#define TREE_UTILS_H

#include <string>

/**
 * @struct TreeNode
 * @brief Узел бинарного дерева арифметического выражения
 * 
 * Хранит либо операнд (0-9), либо код операции (-1..-6)
 */
struct TreeNode {
    int value;          ///< Значение: 0-9 для операндов, -1..-6 для операций
    TreeNode* left;     ///< Левое поддерево
    TreeNode* right;    ///< Правое поддерево
    
    /**
     * @brief Конструктор узла
     * @param val Значение узла
     * @param l Левое поддерево (по умолчанию nullptr)
     * @param r Правое поддерево (по умолчанию nullptr)
     */
    TreeNode(int val, TreeNode* l = nullptr, TreeNode* r = nullptr);
    
    /**
     * @brief Деструктор (рекурсивно удаляет все поддерево)
     */
    ~TreeNode();
};

namespace TreeUtils {
    /**
     * @brief Проверка, является ли токен оператором
     * @param token Токен для проверки
     * @return true если оператор, false если операнд
     */
    bool isOperator(const std::string& token);
    
    /**
     * @brief Преобразование символа оператора в числовой код
     * @param op Символ оператора (+, -, *, /, %, ^)
     * @return Числовой код операции (-1..-6)
     * @throws std::runtime_error для неизвестных операторов
     */
    int operatorToCode(char op);
    
    /**
     * @brief Преобразование числового кода в символ оператора
     * @param code Числовой код операции (-1..-6)
     * @return Символ оператора
     * @throws std::runtime_error для неизвестных кодов
     */
    char codeToOperator(int code);
    
    /**
     * @brief Проверка, является ли операция делением или остатком
     * @param code Код операции
     * @return true для операций / (-4) и % (-5)
     */
    bool isDivisionOperation(int code);
    
    /**
     * @brief Вычисление значения арифметической операции
     * @param opCode Код операции
     * @param left Левый операнд
     * @param right Правый операнд
     * @return Результат операции
     * @throws std::runtime_error при делении на ноль
     */
    int computeOperation(int opCode, int left, int right);
}

#endif // TREE_UTILS_H