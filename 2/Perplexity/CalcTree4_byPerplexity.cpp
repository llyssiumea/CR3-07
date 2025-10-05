// https://www.perplexity.ai/search/reshit-zadachu-na-iazyke-c-pod-FYSfQs2RR8SiyBDpe7KMww

#include <iostream>
#include <stack>
#include <string>
#include <fstream>
#include <cmath>

struct Node {
    int value;  // >=0: число, <0: код операции
    Node* left;
    Node* right;
    Node(int v) : value(v), left(nullptr), right(nullptr) {}
    Node(int v, Node* l, Node* r) : value(v), left(l), right(r) {}
};

// Функция вычисления значения дерева
int evaluate(Node* root) {
    if (!root) return 0;
    if (root->value >= 0) return root->value;

    int leftVal = evaluate(root->left);
    int rightVal = evaluate(root->right);

    switch (root->value) {
        case -1: return leftVal + rightVal;           // +
        case -2: return leftVal - rightVal;           // -
        case -3: return leftVal * rightVal;           // *
        case -4: return rightVal == 0 ? 0 : leftVal / rightVal;  // /, защита от деления на 0
        case -5: return rightVal == 0 ? 0 : leftVal % rightVal;  // %
        case -6: return (int)pow(leftVal, rightVal);            // ^
        default: return 0;
    }
}

// Рекурсивное преобразование дерева — вычисление и замена поддеревьев с / или %
Node* transformTree(Node* root) {
    if (!root) return nullptr;
    if (root->value >= 0) return root;  // лист — возвращаем как есть

    // Рекурсивно преобразуем потомков
    root->left = transformTree(root->left);
    root->right = transformTree(root->right);

    // Если операция деления или остатка — вычисляем и создаём лист
    if (root->value == -4 || root->value == -5) {
        int val = evaluate(root);
        delete root->left;
        delete root->right;
        root->left = nullptr;
        root->right = nullptr;
        root->value = val;
    }
    return root;
}

// Функция для построения дерева из postfix-строки
// Символы разделены пробелами для удобства
Node* buildTreeFromPostfix(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Не удалось открыть файл " << filename << std::endl;
        return nullptr;
    }
    std::stack<Node*> st;
    std::string token;
    while (file >> token) {
        if (token.length() == 1 && isdigit(token[0])) {
            // Операнд
            int val = token[0] - '0';
            st.push(new Node(val));
        } else {
            // Оператор
            int opCode = 0;
            if (token == "+") opCode = -1;
            else if (token == "-") opCode = -2;
            else if (token == "*") opCode = -3;
            else if (token == "/") opCode = -4;
            else if (token == "%") opCode = -5;
            else if (token == "^") opCode = -6;
            else {
                std::cerr << "Неизвестная операция: " << token << std::endl;
                return nullptr;
            }

            if (st.size() < 2) {
                std::cerr << "Ошибка формата выражения" << std::endl;
                return nullptr;
            }
            Node* right = st.top(); st.pop();
            Node* left = st.top(); st.pop();
            st.push(new Node(opCode, left, right));
        }
    }
    if (st.size() != 1) {
        std::cerr << "Ошибка: в файле не корректное выражение" << std::endl;
        return nullptr;
    }
    return st.top();
}

// Для проверки: вывод инфиксного выражения
void printInfix(Node* root) {
    if (!root) return;
    bool isOp = root->value < 0;
    if (isOp) std::cout << "(";
    printInfix(root->left);
    if (root->value >= 0) std::cout << root->value;
    else {
        switch(root->value) {
            case -1: std::cout << "+"; break;
            case -2: std::cout << "-"; break;
            case -3: std::cout << "*"; break;
            case -4: std::cout << "/"; break;
            case -5: std::cout << "%"; break;
            case -6: std::cout << "^"; break;
        }
    }
    printInfix(root->right);
    if (isOp) std::cout << ")";
}

int main() {
    std::string filename = "filename.txt"; // имя файла с выражением в postfix
    Node* root = buildTreeFromPostfix(filename);
    if (!root) return 1;

    std::cout << "Исходное выражение в инфиксной форме: ";
    printInfix(root);
    std::cout << std::endl;

    root = transformTree(root); // заменяем / и % вычисленными значениями

    std::cout << "Преобразованное выражение без деления и остатка: ";
    printInfix(root);
    std::cout << std::endl;

    std::cout << "Указатель на корень дерева: " << root << std::endl;

    // Освобождение памяти: рекурсивно удалить дерево (не показано для краткости)

    return 0;
}
