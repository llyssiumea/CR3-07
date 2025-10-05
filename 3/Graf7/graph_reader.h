/**
 * @file graph_reader.h
 * @brief Чтение графа из файла
 * @version 2.0
 * 
 * Класс для чтения матрицы смежности из текстового файла
 */

#ifndef GRAPH_READER_H
#define GRAPH_READER_H

#include "graph_utils.h"
#include <string>

/**
 * @class GraphReader
 * @brief Читатель графа из файла
 * 
 * Обеспечивает чтение и валидацию матрицы смежности из файла
 */
class GraphReader {
public:
    /**
     * @brief Чтение графа из файла
     * @param filename Имя файла
     * @param[out] cityCount Количество городов
     * @return AdjacencyMatrix Матрица смежности
     * @throws std::runtime_error при ошибках чтения или валидации
     */
    static AdjacencyMatrix readFromFile(const std::string& filename, int& cityCount);
    
    /**
     * @brief Валидация матрицы смежности
     * @param matrix Матрица для проверки
     * @param cityCount Количество городов
     * @return true если матрица корректна
     */
    static bool validateMatrix(const AdjacencyMatrix& matrix, int cityCount);

private:
    /**
     * @brief Проверка корректности количества городов
     * @param count Количество городов
     * @return true если количество корректно
     */
    static bool isValidCityCount(int count);
    
    /**
     * @brief Проверка корректности значения в матрице
     * @param value Значение для проверки
     * @return true если значение 0 или 1
     */
    static bool isValidMatrixValue(int value);
};

#endif // GRAPH_READER_H