/**
 * @file password_generator.h
 * @brief Заголовочный файл класса PasswordGenerator
 * @version 2.0
 * 
 * Класс для генерации случайных паролей трех уровней сложности.
 * Использует криптографически безопасный генератор случайных чисел.
 */

#ifndef PASSWORD_GENERATOR_H
#define PASSWORD_GENERATOR_H

#include <string>
#include <random>

/**
 * @class PasswordGenerator
 * @brief Генератор паролей с тремя уровнями сложности
 * 
 * Класс предоставляет функциональность для генерации паролей:
 * - Низкая сложность: 8 символов (буквы + цифры)
 * - Средняя сложность: 12 символов (буквы + цифры + символы)
 * - Высокая сложность: 16 символов (буквы + цифры + символы)
 */
class PasswordGenerator {
private:
    // Наборы символов
    const std::string lowercase_ = "abcdefghijklmnopqrstuvwxyz";
    const std::string uppercase_ = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const std::string digits_ = "0123456789";
    const std::string symbols_ = "!@#$%^&*()_+-=[]{}|;:,.<>?";
    
    // Генераторы случайных чисел
    std::random_device rd_;
    std::mt19937 generator_;

public:
    /**
     * @brief Конструктор по умолчанию
     */
    PasswordGenerator();
    
    /**
     * @brief Генерация пароля низкой сложности
     * @return std::string Пароль длиной 8 символов (буквы + цифры)
     */
    std::string generateLowStrength();
    
    /**
     * @brief Генерация пароля средней сложности
     * @return std::string Пароль длиной 12 символов (буквы + цифры + символы)
     */
    std::string generateMediumStrength();
    
    /**
     * @brief Генерация пароля высокой сложности
     * @return std::string Пароль длиной 16 символов (буквы + цифры + символы)
     */
    std::string generateHighStrength();

private:
    /**
     * @brief Получение случайного числа в диапазоне
     * @param min Минимальное значение
     * @param max Максимальное значение
     * @return int Случайное число в диапазоне [min, max]
     */
    int getRandomInt(int min, int max);
    
    /**
     * @brief Выбор случайного символа из набора
     * @param charSet Набор символов
     * @return char Случайный символ из набора
     */
    char getRandomChar(const std::string& charSet);
    
    /**
     * @brief Перемешивание символов в пароле
     * @param password Исходный пароль
     * @return std::string Перемешанный пароль
     */
    std::string shufflePassword(const std::string& password);
    
    /**
     * @brief Создание набора символов для указанного уровня
     * @param includeLower Включить строчные буквы
     * @param includeUpper Включить прописные буквы  
     * @param includeDigits Включить цифры
     * @param includeSymbols Включить символы
     * @return std::string Объединенный набор символов
     */
    std::string createCharset(bool includeLower, bool includeUpper, 
                             bool includeDigits, bool includeSymbols);
};

#endif // PASSWORD_GENERATOR_H