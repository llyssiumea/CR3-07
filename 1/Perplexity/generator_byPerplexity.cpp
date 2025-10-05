// https://www.perplexity.ai/search/reshit-zadachu-na-iazyke-c-pod-FYSfQs2RR8SiyBDpe7KMww

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

// Функция генерации пароля заданной длины и из заданного набора символов
std::string generatePassword(int length, const std::string& charset) {
    std::string password;
    int charSetSize = charset.size();
    for (int i = 0; i < length; ++i) {
        int index = rand() % charSetSize; // случайный индекс символа
        password += charset[index];
    }
    return password;
}

int main() {
    // Инициализация генератора случайных чисел
    srand(static_cast<unsigned int>(time(0)));

    // Определяем наборы символов для разных уровней сложности
    const std::string lowerCase = "abcdefghijklmnopqrstuvwxyz";                  // строчные буквы
    const std::string upperCase = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";                  // прописные буквы
    const std::string digits = "0123456789";                                    // цифры
    const std::string specialChars = "!@#$%^&*()-_=+[]{};:,.<>?";               // специальные символы

    int choice;
    std::cout << "Выберите уровень сложности пароля:\n";
    std::cout << "1 - Легкий (только строчные буквы, длина 8)\n";
    std::cout << "2 - Средний (буквы верхнего и нижнего регистра + цифры, длина 12)\n";
    std::cout << "3 - Сложный (буквы разных регистров + цифры + спецсимволы, длина 16)\n";
    std::cout << "Ваш выбор: ";
    std::cin >> choice;

    std::string charset;  // Набор символов для генерации пароля
    int length = 0;

    // В зависимости от выбора пользователя задаем длину и набор символов
    switch (choice) {
        case 1:
            length = 8;
            charset = lowerCase;
            break;
        case 2:
            length = 12;
            charset = lowerCase + upperCase + digits;
            break;
        case 3:
            length = 16;
            charset = lowerCase + upperCase + digits + specialChars;
            break;
        default:
            std::cout << "Неверный выбор уровня сложности.\n";
            return 1; // выход из программы с ошибкой
    }

    // Генерируем и выводим пароль
    std::string password = generatePassword(length, charset);
    std::cout << "Сгенерированный пароль: " << password << std::endl;

    return 0;
}
