/**
 * @file graph_utils.h
 * @brief Вспомогательные функции и структуры для работы с графами
 * @version 2.0
 * 
 * Определяет типы и функции для работы с матрицами смежности и BFS
 */

#ifndef GRAPH_UTILS_H
#define GRAPH_UTILS_H

#include <vector>
#include <queue>
#include <set>

/**
 * @typedef AdjacencyMatrix
 * @brief Матрица смежности графа
 */
using AdjacencyMatrix = std::vector<std::vector<int>>;

/**
 * @struct BFSResult
 * @brief Результат обхода в ширину
 */
struct BFSResult {
    std::vector<int> distances;  ///< Расстояния от стартовой вершины
    std::set<int> reachable;     ///< Множество достижимых вершин
};

namespace GraphUtils {
    /**
     * @brief Поиск в ширину (BFS) с ограничением по расстоянию
     * @param graph Матрица смежности
     * @param start Стартовая вершина
     * @param maxDistance Максимальное расстояние (количество ребер)
     * @return BFSResult Результат обхода
     */
    BFSResult breadthFirstSearch(const AdjacencyMatrix& graph, int start, int maxDistance);
    
    /**
     * @brief Проверка корректности номера города
     * @param city Номер города
     * @param cityCount Общее количество городов
     * @return true если номер корректен
     */
    bool isValidCity(int city, int cityCount);
    
    /**
     * @brief Проверка корректности параметра L
     * @param L Максимальное количество промежуточных городов
     * @return true если параметр корректен
     */
    bool isValidL(int L);
    
    /**
     * @brief Поиск пересечения двух множеств
     * @param set1 Первое множество
     * @param set2 Второе множество
     * @return std::vector<int> Отсортированный вектор общих элементов
     */
    std::vector<int> findIntersection(const std::set<int>& set1, const std::set<int>& set2);
}

#endif // GRAPH_UTILS_H