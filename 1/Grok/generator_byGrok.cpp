// https://grok.com/c/f18ed0d4-677a-4d0e-918f-c5611f84f692

#include <iostream>    // Для ввода/вывода
#include <string>      // Для работы со строками
#include <random>      // Для генерации случайных чисел
#include <ctime>       // Для fallback-сида, если random_device не работает

// Функция для генерации пароля на основе уровня сложности
std::string generatePassword(int level) {
    std::string password;  // Результирующий пароль
    std::string charset;   // Набор символов для уровня
    int length;            // Длина пароля

    // Определение параметров в зависимости от уровня
    switch (level) {
        case 1:  // Easy: Только буквы, длина 8
            charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
            length = 8;
            break;
        case 2:  // Medium: Буквы + цифры, длина 12
            charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
            length = 12;
            break;
        case 3:  // Hard: Буквы + цифры + символы, длина 16
            charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()_+-=[]{}|;:'\",.<>?/";
            length = 16;
            break;
        default:
            return "";  // В случае ошибки (не должно происходить)
    }

    // Инициализация генератора случайных чисел
    std::random_device rd;  // Источник истинной случайности (аппаратный, если доступен)
    std::mt19937 gen(rd()); // Mersenne Twister как PRNG
    std::uniform_int_distribution<> dis(0, charset.size() - 1);  // Равномерное распределение

    // Генерация пароля: Выбор случайных символов из charset
    for (int i = 0; i < length; ++i) {
        password += charset[dis(gen)];
    }

    return password;
}

int main() {
    char choice;  // Для выбора продолжения
    do {
        int level;  // Уровень сложности

        // Вывод меню уровней
        std::cout << "Генератор паролей\n";
        std::cout << "Выберите уровень сложности:\n";
        std::cout << "1 - Простой (длина 8, только буквы)\n";
        std::cout << "2 - Средний (длина 12, буквы + цифры)\n";
        std::cout << "3 - Сложный (длина 16, буквы + цифры + символы)\n";
        std::cout << "Ваш выбор: ";

        // Ввод уровня с проверкой
        std::cin >> level;
        while (level < 1 || level > 3) {
            std::cout << "Неверный выбор. Пожалуйста, выберите 1, 2 или 3: ";
            std::cin >> level;
        }

        // Генерация и вывод пароля
        std::string password = generatePassword(level);
        std::cout << "Сгенерированный пароль: " << password << "\n";

        // Запрос на продолжение
        std::cout << "Хотите сгенерировать новый пароль? (y/n): ";
        std::cin >> choice;
    } while (choice == 'y' || choice == 'Y');

    std::cout << "Программа завершена.\n";
    return 0;
}