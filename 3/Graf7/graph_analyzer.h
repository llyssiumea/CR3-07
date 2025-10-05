/**
 * @file graph_analyzer.h
 * @brief Анализатор графа для поиска общих городов
 * @version 2.0
 * 
 * Класс для поиска городов, достижимых из двух штаб-квартир
 */

#ifndef GRAPH_ANALYZER_H
#define GRAPH_ANALYZER_H

#include "graph_utils.h"
#include <vector>

/**
 * @class GraphAnalyzer
 * @brief Анализатор пересекающихся зон влияния
 * 
 * Находит города, достижимые из двух штаб-квартир
 * с ограничением по количеству промежуточных городов
 */
class GraphAnalyzer {
private:
    AdjacencyMatrix graph_;
    int cityCount_;
    
public:
    /**
     * @brief Конструктор
     * @param graph Матрица смежности
     * @param cityCount Количество городов
     */
    GraphAnalyzer(const AdjacencyMatrix& graph, int cityCount);
    
    /**
     * @brief Поиск общих городов для двух штаб-квартир
     * @param k1 Первая штаб-квартира (1..cityCount)
     * @param k2 Вторая штаб-квартира (1..cityCount)
     * @param L Максимальное количество промежуточных городов
     * @return std::vector<int> Номера общих городов или {-1} если нет общих
     * @throws std::runtime_error при некорректных параметрах
     */
    std::vector<int> findCommonCities(int k1, int k2, int L);
    
    /**
     * @brief Получение количества городов
     * @return int Количество городов
     */
    int getCityCount() const;

private:
    /**
     * @brief Поиск достижимых городов из заданной точки
     * @param startCity Стартовый город (0-based)
     * @param maxIntermediates Максимальное количество промежуточных городов
     * @return std::set<int> Множество достижимых городов (0-based)
     */
    std::set<int> findReachableCities(int startCity, int maxIntermediates);
    
    /**
     * @brief Валидация входных параметров
     * @param k1 Первая штаб-квартира
     * @param k2 Вторая штаб-квартира
     * @param L Максимальное количество промежуточных городов
     */
    void validateInput(int k1, int k2, int L) const;
};

#endif // GRAPH_ANALYZER_H