// https://grok.com/c/f18ed0d4-677a-4d0e-918f-c5611f84f692

#include <iostream>    // Для ввода/вывода
#include <fstream>     // Для чтения файла
#include <string>      // Для работы со строками
#include <stack>       // Для стека при построении дерева
#include <sstream>     // Для парсинга строки
#include <cmath>       // Для pow (^)
#include <exception>   // Для std::runtime_error

// Структура узла дерева
struct Node {
    int value;       // Значение: 0-9 для операндов, -1..-6 для операций
    Node* left;      // Левое поддерево
    Node* right;     // Правое поддерево

    // Конструктор
    Node(int val) : value(val), left(nullptr), right(nullptr) {}

    // Деструктор для рекурсивного освобождения памяти
    ~Node() {
        delete left;
        delete right;
    }
};

// Функция для чтения выражения из файла
std::string readExpressionFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Не удалось открыть файл: " + filename);
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string expression = buffer.str();
    if (expression.empty()) {
        throw std::runtime_error("Файл пуст");
    }
    std::cout << "Прочитанное выражение: " << expression << std::endl; // Отладка
    return expression;
}

// Функция для маппинга символа операции в код
int getOperationCode(char op) {
    switch (op) {
        case '+': return -1;
        case '-': return -2;
        case '*': return -3;
        case '/': return -4;
        case '%': return -5;
        case '^': return -6;
        default: throw std::runtime_error("Неизвестная операция: " + std::string(1, op));
    }
}

// Функция для построения дерева из RPN
Node* buildTree(const std::string& expression) {
    std::stack<Node*> stk;
    std::istringstream iss(expression);
    std::string token;

    while (iss >> token) {
        if (token.empty()) continue;

        std::cout << "Обработка токена: " << token << std::endl; // Отладка
        if (token.size() == 1 && std::isdigit(token[0])) {
            // Операнд: создать лист
            int val = token[0] - '0';
            stk.push(new Node(val));
        } else if (token.size() == 1 && (token[0] == '+' || token[0] == '-' || token[0] == '*' ||
                                        token[0] == '/' || token[0] == '%' || token[0] == '^')) {
            // Оператор: попнуть два операнда
            if (stk.size() < 2) {
                throw std::runtime_error("Некорректное выражение: недостаточно операндов для операции " + token);
            }
            Node* right = stk.top(); stk.pop();
            Node* left = stk.top(); stk.pop();
            int opCode = getOperationCode(token[0]);
            Node* opNode = new Node(opCode);
            opNode->left = left;
            opNode->right = right;
            stk.push(opNode);
        } else {
            throw std::runtime_error("Некорректный токен: " + token);
        }
    }

    if (stk.empty()) {
        throw std::runtime_error("Некорректное выражение: стек пуст");
    }
    if (stk.size() != 1) {
        throw std::runtime_error("Некорректное выражение: слишком много операндов (" + std::to_string(stk.size()) + ")");
    }

    return stk.top();
}

// Рекурсивная функция для вычисления значения поддерева
int evaluateSubtree(Node* node) {
    if (!node) {
        throw std::runtime_error("Попытка вычислить nullptr");
    }
    if (node->value >= 0) {  // Лист (операнд)
        return node->value;
    }

    int leftVal = evaluateSubtree(node->left);
    int rightVal = evaluateSubtree(node->right);

    switch (node->value) {
        case -1: return leftVal + rightVal;  // +
        case -2: return leftVal - rightVal;  // -
        case -3: return leftVal * rightVal;  // *
        case -4:  // /
            if (rightVal == 0) throw std::runtime_error("Деление на ноль");
            return leftVal / rightVal;
        case -5:  // %
            if (rightVal == 0) throw std::runtime_error("Остаток от деления на ноль");
            return leftVal % rightVal;
        case -6: return static_cast<int>(std::pow(leftVal, rightVal));  // ^
        default: throw std::runtime_error("Неизвестный код операции: " + std::to_string(node->value));
    }
}

// Рекурсивная функция для преобразования дерева: заменяем / и % на константы
Node* transformTree(Node* node) {
    if (!node) {
        throw std::runtime_error("Попытка преобразовать nullptr");
    }
    if (node->value >= 0) {  // Лист: ничего не меняем
        return node;
    }

    // Рекурсивно преобразовать поддеревья
    node->left = transformTree(node->left);
    node->right = transformTree(node->right);

    // Если операция / или %, вычислить и заменить на лист
    if (node->value == -4 || node->value == -5) {
        int result = evaluateSubtree(node);
        Node* newNode = new Node(result);
        // Устанавливаем указатели на nullptr, чтобы деструктор не удалял лишнее
        node->left = nullptr;
        node->right = nullptr;
        delete node;  // Удаляем текущий узел
        return newNode;
    }

    return node;
}

// Функция для отладочного вывода дерева (inorder traversal)
void printTree(Node* node, int level = 0) {
    if (!node) return;
    printTree(node->left, level + 1);
    for (int i = 0; i < level; ++i) std::cout << "  ";
    std::cout << "Value: " << node->value << std::endl;
    printTree(node->right, level + 1);
}

int main() {
    try {
        std::string filename = "filename.txt";
        std::string expression = readExpressionFromFile(filename);
        Node* root = buildTree(expression);
        std::cout << "Дерево до преобразования:" << std::endl;
        printTree(root);
        root = transformTree(root);
        std::cout << "Дерево после преобразования:" << std::endl;
        printTree(root);
        std::cout << "Указатель на корень дерева: " << root << std::endl;
        delete root;  // Освобождение памяти
    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}