// https://chat.deepseek.com/a/chat/s/12c2f814-8c73-4033-89fd-c65128519de3

#include <iostream>
#include <string>
#include <random>
#include <ctime>

// Класс для генерации паролей
class PasswordGenerator {
private:
    // Наборы символов для разных уровней сложности
    const std::string lowercase = "abcdefghijklmnopqrstuvwxyz";
    const std::string uppercase = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const std::string digits = "0123456789";
    const std::string symbols = "!@#$%^&*()_+-=[]{}|;:,.<>?";
    
    // Генератор случайных чисел
    std::mt19937 rng;
    
public:
    // Конструктор - инициализируем генератор случайных чисел
    PasswordGenerator() {
        rng.seed(std::time(nullptr));
    }
    
    // Функция для получения случайного числа в диапазоне [min, max]
    int getRandomInt(int min, int max) {
        std::uniform_int_distribution<int> dist(min, max);
        return dist(rng);
    }
    
    // Функция для выбора случайного символа из строки
    char getRandomChar(const std::string& charSet) {
        int index = getRandomInt(0, charSet.length() - 1);
        return charSet[index];
    }
    
    // Генерация пароля низкой сложности
    std::string generateLowStrength() {
        const int length = 8;
        std::string password;
        std::string charSet = lowercase + uppercase + digits;
        
        for (int i = 0; i < length; i++) {
            password += getRandomChar(charSet);
        }
        
        return password;
    }
    
    // Генерация пароля средней сложности
    std::string generateMediumStrength() {
        const int length = 12;
        std::string password;
        std::string charSet = lowercase + uppercase + digits + symbols;
        
        // Гарантируем наличие хотя бы одного символа каждого типа
        password += getRandomChar(lowercase);
        password += getRandomChar(uppercase);
        password += getRandomChar(digits);
        password += getRandomChar(symbols);
        
        // Заполняем оставшуюся длину случайными символами
        for (int i = 4; i < length; i++) {
            password += getRandomChar(charSet);
        }
        
        // Перемешиваем пароль для случайного порядка символов
        return shufflePassword(password);
    }
    
    // Генерация пароля высокой сложности
    std::string generateHighStrength() {
        const int length = 16;
        std::string password;
        std::string charSet = lowercase + uppercase + digits + symbols;
        
        // Гарантируем наличие нескольких символов каждого типа
        password += getRandomChar(lowercase);
        password += getRandomChar(lowercase);
        password += getRandomChar(uppercase);
        password += getRandomChar(uppercase);
        password += getRandomChar(digits);
        password += getRandomChar(digits);
        password += getRandomChar(symbols);
        password += getRandomChar(symbols);
        
        // Заполняем оставшуюся длину случайными символами
        for (int i = 8; i < length; i++) {
            password += getRandomChar(charSet);
        }
        
        // Перемешиваем пароль для случайного порядка символов
        return shufflePassword(password);
    }
    
private:
    // Функция для перемешивания символов в пароле
    std::string shufflePassword(const std::string& password) {
        std::string shuffled = password;
        
        // Используем алгоритм Фишера-Йетса для перемешивания
        for (int i = shuffled.length() - 1; i > 0; i--) {
            int j = getRandomInt(0, i);
            std::swap(shuffled[i], shuffled[j]);
        }
        
        return shuffled;
    }
};

// Функция для отображения меню выбора сложности
int displayMenu() {
    std::cout << "=== ГЕНЕРАТОР ПАРОЛЕЙ ===" << std::endl;
    std::cout << "Выберите уровень сложности пароля:" << std::endl;
    std::cout << "1. Низкая сложность (8 символов: буквы и цифры)" << std::endl;
    std::cout << "2. Средняя сложность (12 символов: буквы, цифры, символы)" << std::endl;
    std::cout << "3. Высокая сложность (16 символов: буквы, цифры, символы)" << std::endl;
    std::cout << "4. Выход" << std::endl;
    std::cout << "Ваш выбор: ";
    
    int choice;
    std::cin >> choice;
    
    // Проверка корректности ввода
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        return -1;
    }
    
    return choice;
}

// Функция для оценки сложности пароля
void evaluatePasswordStrength(const std::string& password) {
    bool hasLower = false, hasUpper = false, hasDigit = false, hasSymbol = false;
    
    for (char c : password) {
        if (islower(c)) hasLower = true;
        else if (isupper(c)) hasUpper = true;
        else if (isdigit(c)) hasDigit = true;
        else hasSymbol = true;
    }
    
    std::cout << "Анализ пароля:" << std::endl;
    std::cout << "- Длина: " << password.length() << " символов" << std::endl;
    std::cout << "- Строчные буквы: " << (hasLower ? "✓" : "✗") << std::endl;
    std::cout << "- Прописные буквы: " << (hasUpper ? "✓" : "✗") << std::endl;
    std::cout << "- Цифры: " << (hasDigit ? "✓" : "✗") << std::endl;
    std::cout << "- Символы: " << (hasSymbol ? "✓" : "✗") << std::endl;
}

int main() {
    // Устанавливаем локаль для корректного отображения русских символов
    setlocale(LC_ALL, "ru_RU.UTF-8");
    
    PasswordGenerator generator;
    int choice;
    
    std::cout << "Добро пожаловать в генератор паролей!" << std::endl;
    
    do {
        choice = displayMenu();
        std::string password;
        
        switch (choice) {
            case 1:
                password = generator.generateLowStrength();
                std::cout << "\nСгенерированный пароль (низкая сложность): " 
                         << password << std::endl;
                evaluatePasswordStrength(password);
                break;
                
            case 2:
                password = generator.generateMediumStrength();
                std::cout << "\nСгенерированный пароль (средняя сложность): " 
                         << password << std::endl;
                evaluatePasswordStrength(password);
                break;
                
            case 3:
                password = generator.generateHighStrength();
                std::cout << "\nСгенерированный пароль (высокая сложность): " 
                         << password << std::endl;
                evaluatePasswordStrength(password);
                break;
                
            case 4:
                std::cout << "Выход из программы. Хорошего дня!" << std::endl;
                break;
                
            default:
                std::cout << "Неверный выбор! Пожалуйста, выберите от 1 до 4." << std::endl;
                break;
        }
        
        if (choice >= 1 && choice <= 3) {
            std::cout << "\n" << std::string(50, '=') << "\n" << std::endl;
        }
        
    } while (choice != 4);
    
    return 0;
}