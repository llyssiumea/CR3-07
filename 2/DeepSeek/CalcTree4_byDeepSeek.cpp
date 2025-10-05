// https://chat.deepseek.com/a/chat/s/12c2f814-8c73-4033-89fd-c65128519de3

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>
#include <cmath>

using namespace std;

// Структура узла бинарного дерева
struct TreeNode {
    int value;
    TreeNode* left;
    TreeNode* right;
    
    TreeNode(int val) : value(val), left(nullptr), right(nullptr) {}
};

class ExpressionTree {
private:
    // Проверка, является ли токен оператором
    bool isOperator(const string& token) {
        return token == "+" || token == "-" || token == "*" || 
               token == "/" || token == "%" || token == "^";
    }
    
    // Преобразование оператора в числовой код
    int operatorToCode(const string& op) {
        if (op == "+") return -1;
        if (op == "-") return -2;
        if (op == "*") return -3;
        if (op == "/") return -4;
        if (op == "%") return -5;
        if (op == "^") return -6;
        return 0;
    }
    
    // Получение символа оператора по коду
    string codeToOperator(int code) {
        switch (code) {
            case -1: return "+";
            case -2: return "-";
            case -3: return "*";
            case -4: return "/";
            case -5: return "%";
            case -6: return "^";
            default: return to_string(code);
        }
    }
    
    // Вычисление значения поддерева
    int evaluateSubtree(TreeNode* node) {
        if (node == nullptr) return 0;
        
        // Если узел - операнд, возвращаем его значение
        if (node->value >= 0) {
            return node->value;
        }
        
        // Рекурсивно вычисляем значения левого и правого поддеревьев
        int leftVal = evaluateSubtree(node->left);
        int rightVal = evaluateSubtree(node->right);
        
        // Выполняем операцию
        switch (node->value) {
            case -1: return leftVal + rightVal;  // +
            case -2: return leftVal - rightVal;  // -
            case -3: return leftVal * rightVal;  // *
            case -4: return (rightVal != 0) ? leftVal / rightVal : 0;  // /
            case -5: return (rightVal != 0) ? leftVal % rightVal : 0;  // %
            case -6: return (int)pow(leftVal, rightVal);  // ^
            default: return 0;
        }
    }
    
    // Удаление поддерева и замена на узел-значение
    void replaceWithValue(TreeNode*& node) {
        if (node == nullptr) return;
        
        int result = evaluateSubtree(node);
        
        // Удаляем старое поддерево
        deleteTree(node);
        
        // Создаем новый узел с вычисленным значением
        node = new TreeNode(result);
    }
    
    // Рекурсивное удаление дерева
    void deleteTree(TreeNode* node) {
        if (node == nullptr) return;
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
    
    // Рекурсивное построение инфиксной записи
    string toInfixNotation(TreeNode* node) {
        if (node == nullptr) return "";
        
        // Если узел - операнд
        if (node->value >= 0) {
            return to_string(node->value);
        }
        
        // Если узел - оператор
        string left = toInfixNotation(node->left);
        string right = toInfixNotation(node->right);
        
        return "(" + left + " " + codeToOperator(node->value) + " " + right + ")";
    }
    
    // Рекурсивное построение обычной математической записи
    string toNormalNotation(TreeNode* node) {
        if (node == nullptr) return "";
        
        // Если узел - операнд
        if (node->value >= 0) {
            return to_string(node->value);
        }
        
        // Если узел - оператор
        string left = toNormalNotation(node->left);
        string right = toNormalNotation(node->right);
        
        return left + " " + codeToOperator(node->value) + " " + right;
    }

public:
    // Построение дерева из выражения в обратной польской записи
    TreeNode* buildTreeFromRPN(const vector<string>& tokens) {
        stack<TreeNode*> nodeStack;
        
        for (const string& token : tokens) {
            if (isOperator(token)) {
                // Для оператора извлекаем два операнда из стека
                if (nodeStack.size() < 2) {
                    throw runtime_error("Недостаточно операндов для оператора: " + token);
                }
                
                TreeNode* right = nodeStack.top();
                nodeStack.pop();
                TreeNode* left = nodeStack.top();
                nodeStack.pop();
                
                // Создаем узел оператора
                TreeNode* opNode = new TreeNode(operatorToCode(token));
                opNode->left = left;
                opNode->right = right;
                
                nodeStack.push(opNode);
            } else {
                // Для операнда создаем листовой узел
                int value = stoi(token);
                nodeStack.push(new TreeNode(value));
            }
        }
        
        if (nodeStack.size() != 1) {
            throw runtime_error("Некорректное выражение");
        }
        
        return nodeStack.top();
    }
    
    // Преобразование дерева: удаление операций деления и остатка
    void removeDivisionOperations(TreeNode*& node) {
        if (node == nullptr) return;
        
        // Рекурсивно обрабатываем левое и правое поддеревья
        removeDivisionOperations(node->left);
        removeDivisionOperations(node->right);
        
        // Если текущий узел - операция деления или остатка, заменяем поддерево на значение
        if (node->value == -4 || node->value == -5) {  // / или %
            replaceWithValue(node);
        }
    }
    
    // Получение инфиксной записи
    string getInfixNotation(TreeNode* root) {
        return toInfixNotation(root);
    }
    
    // Получение обычной математической записи
    string getNormalNotation(TreeNode* root) {
        return toNormalNotation(root);
    }
    
    // Вывод дерева (для отладки)
    void printTree(TreeNode* root, int depth = 0) {
        if (root == nullptr) return;
        
        printTree(root->right, depth + 1);
        
        for (int i = 0; i < depth; i++) {
            cout << "   ";
        }
        
        if (root->value >= 0) {
            cout << root->value << endl;
        } else {
            cout << codeToOperator(root->value) << endl;
        }
        
        printTree(root->left, depth + 1);
    }
    
    // Вычисление значения выражения
    int evaluate(TreeNode* root) {
        return evaluateSubtree(root);
    }
    
    // Освобождение памяти
    void cleanup(TreeNode* root) {
        deleteTree(root);
    }
};

// Функция для чтения выражения из файла
vector<string> readExpressionFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Не удалось открыть файл: " + filename);
    }
    
    vector<string> tokens;
    string token;
    
    while (file >> token) {
        tokens.push_back(token);
    }
    
    return tokens;
}

int main() {
    try {
        string filename = "filename.txt";
        
        // Читаем выражение из файла
        vector<string> tokens = readExpressionFromFile(filename);
        
        cout << "=== АНАЛИЗ АРИФМЕТИЧЕСКОГО ВЫРАЖЕНИЯ ===" << endl;
        cout << endl;
        
        cout << "Обратная польская запись: ";
        for (const string& token : tokens) {
            cout << token << " ";
        }
        cout << endl;
        
        // Создаем дерево выражения
        ExpressionTree exprTree;
        TreeNode* root = exprTree.buildTreeFromRPN(tokens);
        
        cout << "Инфиксная запись: " << exprTree.getInfixNotation(root) << endl;
        cout << "Обычная запись: " << exprTree.getNormalNotation(root) << endl;
        cout << "Вычисленное значение: " << exprTree.evaluate(root) << endl;
        
        cout << endl;
        cout << "--- Структура исходного дерева ---" << endl;
        exprTree.printTree(root);
        
        // Преобразуем дерево: удаляем операции деления и остатка
        exprTree.removeDivisionOperations(root);
        
        cout << endl;
        cout << "=== ПОСЛЕ ПРЕОБРАЗОВАНИЯ ===" << endl;
        cout << endl;
        
        cout << "Инфиксная запись: " << exprTree.getInfixNotation(root) << endl;
        cout << "Обычная запись: " << exprTree.getNormalNotation(root) << endl;
        cout << "Вычисленное значение: " << exprTree.evaluate(root) << endl;
        
        cout << endl;
        cout << "--- Структура преобразованного дерева ---" << endl;
        exprTree.printTree(root);
        
        // Выводим указатель на корень (требование задачи)
        cout << endl;
        cout << "Указатель на корень дерева: " << root << endl;
        
        // Освобождаем память
        exprTree.cleanup(root);
        
    } catch (const exception& e) {
        cerr << "Ошибка: " << e.what() << endl;
        return 1;
    }
    
    return 0;
}