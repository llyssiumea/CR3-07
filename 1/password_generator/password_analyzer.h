/**
 * @file password_analyzer.h
 * @brief Заголовочный файл класса PasswordAnalyzer
 * @version 1.0
 * 
 * Класс для анализа сложности и безопасности паролей.
 * Оценивает пароли по различным критериям безопасности.
 */

#ifndef PASSWORD_ANALYZER_H
#define PASSWORD_ANALYZER_H

#include <string>

/**
 * @struct PasswordStats
 * @brief Статистика пароля
 * 
 * Содержит информацию о составе и характеристиках пароля
 */
struct PasswordStats {
    int length;             ///< Длина пароля
    bool hasLowercase;      ///< Наличие строчных букв
    bool hasUppercase;      ///< Наличие прописных букв  
    bool hasDigits;         ///< Наличие цифр
    bool hasSymbols;        ///< Наличие специальных символов
    int strengthScore;      ///< Оценка силы пароля (0-100)
    
    /**
     * @brief Конструктор по умолчанию
     */
    PasswordStats();
};

/**
 * @class PasswordAnalyzer
 * @brief Анализатор сложности паролей
 * 
 * Предоставляет методы для анализа паролей и оценки их безопасности
 * по различным критериям.
 */
class PasswordAnalyzer {
public:
    /**
     * @brief Анализ пароля и получение статистики
     * @param password Пароль для анализа
     * @return PasswordStats Статистика пароля
     */
    static PasswordStats analyze(const std::string& password);
    
    /**
     * @brief Вывод подробного анализа пароля
     * @param password Пароль для анализа
     */
    static void printDetailedAnalysis(const std::string& password);
    
    /**
     * @brief Получение текстовой оценки сложности
     * @param stats Статистика пароля
     * @return std::string Текстовая оценка
     */
    static std::string getStrengthDescription(const PasswordStats& stats);

private:
    /**
     * @brief Расчет оценки силы пароля
     * @param stats Статистика пароля
     * @return int Оценка от 0 до 100
     */
    static int calculateStrengthScore(const PasswordStats& stats);
};

#endif // PASSWORD_ANALYZER_H