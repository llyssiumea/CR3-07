/**
 * @file main.cpp
 * @brief Основная программа генератора паролей
 * @version 2.0
 * 
 * Главный модуль программы, содержащий пользовательский интерфейс
 * и основную логику работы генератора паролей.
 */

#include <iostream>
#include <limits>
#include "password_generator.h"
#include "password_analyzer.h"

/**
 * @brief Отображение главного меню программы
 * @return int Выбор пользователя
 */
int displayMainMenu() {
    std::cout << "\n=== ГЕНЕРАТОР ПАРОЛЕЙ ===" << std::endl;
    std::cout << "Выберите уровень сложности пароля:" << std::endl;
    std::cout << "1. Низкая сложность (8 символов: буквы + цифры)" << std::endl;
    std::cout << "2. Средняя сложность (12 символов: буквы + цифры + символы)" << std::endl;
    std::cout << "3. Высокая сложность (16 символов: буквы + цифры + символы)" << std::endl;
    std::cout << "4. Анализ существующего пароля" << std::endl;
    std::cout << "5. Выход" << std::endl;
    std::cout << "Ваш выбор: ";
    
    int choice;
    std::cin >> choice;
    
    // Обработка некорректного ввода
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return -1;
    }
    
    return choice;
}

/**
 * @brief Функция анализа существующего пароля
 */
void analyzeExistingPassword() {
    std::string password;
    std::cout << "\nВведите пароль для анализа: ";
    std::cin >> password;
    
    PasswordAnalyzer::printDetailedAnalysis(password);
}

/**
 * @brief Главная функция программы
 * @return int Код завершения программы
 */
int main() {
    // Настройка локали для корректного отображения русских символов
    setlocale(LC_ALL, "ru_RU.UTF-8");
    
    PasswordGenerator generator;
    int choice;
    
    std::cout << "Добро пожаловать в генератор паролей!" << std::endl;
    std::cout << "=====================================" << std::endl;
    
    do {
        choice = displayMainMenu();
        std::string password;
        
        switch (choice) {
            case 1:
                password = generator.generateLowStrength();
                std::cout << "\nСгенерированный пароль (низкая сложность): " 
                         << password << std::endl;
                PasswordAnalyzer::printDetailedAnalysis(password);
                break;
                
            case 2:
                password = generator.generateMediumStrength();
                std::cout << "\nСгенерированный пароль (средняя сложность): " 
                         << password << std::endl;
                PasswordAnalyzer::printDetailedAnalysis(password);
                break;
                
            case 3:
                password = generator.generateHighStrength();
                std::cout << "\nСгенерированный пароль (высокая сложность): " 
                         << password << std::endl;
                PasswordAnalyzer::printDetailedAnalysis(password);
                break;
                
            case 4:
                analyzeExistingPassword();
                break;
                
            case 5:
                std::cout << "\nВыход из программы. Хорошего дня!" << std::endl;
                break;
                
            default:
                std::cout << "Неверный выбор! Пожалуйста, выберите от 1 до 5." << std::endl;
                break;
        }
        
        if (choice >= 1 && choice <= 4) {
            std::cout << "\n" << std::string(50, '=') << std::endl;
        }
        
    } while (choice != 5);
    
    return 0;
}

// cd "/Users/alyssa/CR3-07/1/password_generator/" && g++ -std=c++14 main.cpp password_generator.cpp password_analyzer.cpp -o main && "/Users/alyssa/CR3-07/1/password_generator/"main
// ./generator