/**
 * @file password_generator.cpp
 * @brief Реализация класса PasswordGenerator
 * @version 2.0
 * 
 * Реализация методов генерации паролей с гарантированным наличием
 * символов разных типов и криптографически безопасным перемешиванием.
 */

#include "password_generator.h"
#include <algorithm>

PasswordGenerator::PasswordGenerator() : generator_(rd_()) {}

std::string PasswordGenerator::generateLowStrength() {
    const int length = 8;
    std::string password;
    std::string charSet = createCharset(true, true, true, false);
    
    // Гарантируем наличие разных типов символов
    password += getRandomChar(lowercase_);
    password += getRandomChar(uppercase_);
    password += getRandomChar(digits_);
    
    // Заполняем оставшуюся длину
    for (int i = 3; i < length; i++) {
        password += getRandomChar(charSet);
    }
    
    return shufflePassword(password);
}

std::string PasswordGenerator::generateMediumStrength() {
    const int length = 12;
    std::string password;
    std::string charSet = createCharset(true, true, true, true);
    
    // Гарантируем наличие всех типов символов
    password += getRandomChar(lowercase_);
    password += getRandomChar(uppercase_);
    password += getRandomChar(digits_);
    password += getRandomChar(symbols_);
    
    // Заполняем оставшуюся длину
    for (int i = 4; i < length; i++) {
        password += getRandomChar(charSet);
    }
    
    return shufflePassword(password);
}

std::string PasswordGenerator::generateHighStrength() {
    const int length = 16;
    std::string password;
    std::string charSet = createCharset(true, true, true, true);
    
    // Гарантируем множественное наличие всех типов символов
    password += getRandomChar(lowercase_);
    password += getRandomChar(lowercase_);
    password += getRandomChar(uppercase_);
    password += getRandomChar(uppercase_);
    password += getRandomChar(digits_);
    password += getRandomChar(digits_);
    password += getRandomChar(symbols_);
    password += getRandomChar(symbols_);
    
    // Заполняем оставшуюся длину
    for (int i = 8; i < length; i++) {
        password += getRandomChar(charSet);
    }
    
    return shufflePassword(password);
}

int PasswordGenerator::getRandomInt(int min, int max) {
    std::uniform_int_distribution<int> dist(min, max);
    return dist(generator_);
}

char PasswordGenerator::getRandomChar(const std::string& charSet) {
    int index = getRandomInt(0, charSet.length() - 1);
    return charSet[index];
}

std::string PasswordGenerator::shufflePassword(const std::string& password) {
    std::string shuffled = password;
    
    // Алгоритм Фишера-Йетса для равномерного перемешивания
    for (int i = shuffled.length() - 1; i > 0; i--) {
        int j = getRandomInt(0, i);
        std::swap(shuffled[i], shuffled[j]);
    }
    
    return shuffled;
}

std::string PasswordGenerator::createCharset(bool includeLower, bool includeUpper, 
                                           bool includeDigits, bool includeSymbols) {
    std::string charSet;
    if (includeLower) charSet += lowercase_;
    if (includeUpper) charSet += uppercase_;
    if (includeDigits) charSet += digits_;
    if (includeSymbols) charSet += symbols_;
    return charSet;
}