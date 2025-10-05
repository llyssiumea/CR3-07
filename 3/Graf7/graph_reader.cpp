/**
 * @file graph_reader.cpp
 * @brief Реализация чтения графа из файла
 * @version 2.0
 */

#include "graph_reader.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>  // Добавлен этот заголовок

AdjacencyMatrix GraphReader::readFromFile(const std::string& filename, int& cityCount) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Не удалось открыть файл: " + filename);
    }
    
    // Чтение количества городов
    file >> cityCount;
    
    if (!isValidCityCount(cityCount)) {
        throw std::runtime_error("Некорректное количество городов: " + std::to_string(cityCount));
    }
    
    // Чтение матрицы смежности
    AdjacencyMatrix matrix(cityCount, std::vector<int>(cityCount));
    
    for (int i = 0; i < cityCount; ++i) {
        for (int j = 0; j < cityCount; ++j) {
            if (!(file >> matrix[i][j])) {
                throw std::runtime_error("Ошибка чтения матрицы смежности");
            }
            
            if (!isValidMatrixValue(matrix[i][j])) {
                throw std::runtime_error("Некорректное значение в матрице: " + 
                                       std::to_string(matrix[i][j]));
            }
        }
    }
    
    // Дополнительная валидация
    if (!validateMatrix(matrix, cityCount)) {
        throw std::runtime_error("Матрица смежности не прошла валидацию");
    }
    
    return matrix;
}

bool GraphReader::validateMatrix(const AdjacencyMatrix& matrix, int cityCount) {
    // Проверка размеров матрицы
    if (matrix.size() != static_cast<size_t>(cityCount)) {
        return false;
    }
    
    for (const auto& row : matrix) {
        if (row.size() != static_cast<size_t>(cityCount)) {
            return false;
        }
    }
    
    // Проверка симметричности (для неориентированного графа)
    for (int i = 0; i < cityCount; ++i) {
        for (int j = 0; j < cityCount; ++j) {
            if (matrix[i][j] != matrix[j][i]) {
                return false;
            }
        }
    }
    
    return true;
}

bool GraphReader::isValidCityCount(int count) {
    return count >= 1 && count <= 25;
}

bool GraphReader::isValidMatrixValue(int value) {
    return value == 0 || value == 1;
}