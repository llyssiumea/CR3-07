/**
 * @file password_analyzer.cpp  
 * @brief Реализация класса PasswordAnalyzer
 * @version 1.0
 * 
 * Реализация методов анализа и оценки безопасности паролей.
 */

#include "password_analyzer.h"
#include <iostream>
#include <cctype>

PasswordStats::PasswordStats() 
    : length(0), hasLowercase(false), hasUppercase(false), 
      hasDigits(false), hasSymbols(false), strengthScore(0) {}

PasswordStats PasswordAnalyzer::analyze(const std::string& password) {
    PasswordStats stats;
    stats.length = password.length();
    
    for (char c : password) {
        if (std::islower(c)) stats.hasLowercase = true;
        else if (std::isupper(c)) stats.hasUppercase = true;
        else if (std::isdigit(c)) stats.hasDigits = true;
        else stats.hasSymbols = true;
    }
    
    stats.strengthScore = calculateStrengthScore(stats);
    return stats;
}

void PasswordAnalyzer::printDetailedAnalysis(const std::string& password) {
    PasswordStats stats = analyze(password);
    
    std::cout << "\n=== АНАЛИЗ ПАРОЛЯ ===" << std::endl;
    std::cout << "Длина: " << stats.length << " символов" << std::endl;
    std::cout << "Строчные буквы: " << (stats.hasLowercase ? "✓ ПРИСУТСТВУЮТ" : "✗ ОТСУТСТВУЮТ") << std::endl;
    std::cout << "Прописные буквы: " << (stats.hasUppercase ? "✓ ПРИСУТСТВУЮТ" : "✗ ОТСУТСТВУЮТ") << std::endl;
    std::cout << "Цифры: " << (stats.hasDigits ? "✓ ПРИСУТСТВУЮТ" : "✗ ОТСУТСТВУЮТ") << std::endl;
    std::cout << "Спецсимволы: " << (stats.hasSymbols ? "✓ ПРИСУТСТВУЮТ" : "✗ ОТСУТСТВУЮТ") << std::endl;
    std::cout << "Оценка сложности: " << stats.strengthScore << "/100" << std::endl;
    std::cout << "Уровень: " << getStrengthDescription(stats) << std::endl;
}

std::string PasswordAnalyzer::getStrengthDescription(const PasswordStats& stats) {
    if (stats.strengthScore >= 80) return "ОЧЕНЬ ВЫСОКИЙ";
    if (stats.strengthScore >= 60) return "ВЫСОКИЙ";
    if (stats.strengthScore >= 40) return "СРЕДНИЙ";
    if (stats.strengthScore >= 20) return "НИЗКИЙ";
    return "ОЧЕНЬ НИЗКИЙ";
}

int PasswordAnalyzer::calculateStrengthScore(const PasswordStats& stats) {
    int score = 0;
    
    // Баллы за длину
    if (stats.length >= 16) score += 40;
    else if (stats.length >= 12) score += 30;
    else if (stats.length >= 8) score += 20;
    else score += 10;
    
    // Баллы за разнообразие символов
    if (stats.hasLowercase) score += 10;
    if (stats.hasUppercase) score += 15;
    if (stats.hasDigits) score += 15;
    if (stats.hasSymbols) score += 20;
    
    return std::min(score, 100); // Ограничиваем максимум 100 баллами
}