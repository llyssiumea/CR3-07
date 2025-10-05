/**
 * @file graph_analyzer.cpp
 * @brief Реализация анализатора графа
 * @version 2.3
 */

#include "graph_analyzer.h"
#include "graph_utils.h"
#include <stdexcept>
#include <string>
#include <iostream>

GraphAnalyzer::GraphAnalyzer(const AdjacencyMatrix& graph, int cityCount) 
    : graph_(graph), cityCount_(cityCount) {}

std::vector<int> GraphAnalyzer::findCommonCities(int k1, int k2, int L) {
    validateInput(k1, k2, L);
    
    // Преобразование в 0-based индексы
    int start1 = k1 - 1;
    int start2 = k2 - 1;
    
    // Максимальное расстояние в ребрах = L + 1
    int maxDistance = L + 1;
    
    std::cout << std::endl;
    std::cout << "=== ОТЛАДОЧНАЯ ИНФОРМАЦИЯ ===" << std::endl;
    std::cout << "K1=" << k1 << " (0-based: " << start1 << "), ";
    std::cout << "K2=" << k2 << " (0-based: " << start2 << "), ";
    std::cout << "L=" << L << " (maxDistance=" << maxDistance << ")" << std::endl;
    
    // Поиск достижимых городов из обеих штаб-квартир
    std::set<int> reachableFromK1 = findReachableCities(start1, maxDistance);
    std::set<int> reachableFromK2 = findReachableCities(start2, maxDistance);
    
    // Отладочный вывод ДО удаления штаб-квартир
    std::cout << "[ОТЛАДКА] Достижимые из K1 (включая саму K1): ";
    for (int city : reachableFromK1) {
        std::cout << (city + 1) << " ";
    }
    std::cout << std::endl;
    
    std::cout << "[ОТЛАДКА] Достижимые из K2 (включая саму K2): ";
    for (int city : reachableFromK2) {
        std::cout << (city + 1) << " ";
    }
    std::cout << std::endl;
    
    // УДАЛЯЕМ штаб-квартиры из множеств достижимых городов
    reachableFromK1.erase(start1);
    reachableFromK2.erase(start2);
    
    // Отладочный вывод ПОСЛЕ удаления штаб-квартир
    std::cout << "[ОТЛАДКА] Достижимые из K1 (исключая саму K1): ";
    for (int city : reachableFromK1) {
        std::cout << (city + 1) << " ";
    }
    std::cout << std::endl;
    
    std::cout << "[ОТЛАДКА] Достижимые из K2 (исключая саму K2): ";
    for (int city : reachableFromK2) {
        std::cout << (city + 1) << " ";
    }
    std::cout << std::endl;
    
    // Поиск пересечения (только общие города, исключая штаб-квартиры)
    std::vector<int> commonCities = GraphUtils::findIntersection(reachableFromK1, reachableFromK2);
    
    // Преобразование обратно в 1-based индексы
    for (int& city : commonCities) {
        city += 1;
    }
    
    std::cout << "[ОТЛАДКА] Общие города (1-based): ";
    if (commonCities.empty()) {
        std::cout << "нет";
    } else {
        for (int city : commonCities) {
            std::cout << city << " ";
        }
    }
    std::cout << std::endl;
    std::cout << "========================" << std::endl;
    std::cout << std::endl;
    
    if (commonCities.empty()) {
        return {-1};
    }
    
    return commonCities;
}

int GraphAnalyzer::getCityCount() const {
    return cityCount_;
}

std::set<int> GraphAnalyzer::findReachableCities(int startCity, int maxDistance) {
    BFSResult result = GraphUtils::breadthFirstSearch(graph_, startCity, maxDistance);
    return result.reachable;
}

void GraphAnalyzer::validateInput(int k1, int k2, int L) const {
    if (!GraphUtils::isValidCity(k1, cityCount_)) {
        throw std::runtime_error("Некорректный номер города K1: " + std::to_string(k1));
    }
    
    if (!GraphUtils::isValidCity(k2, cityCount_)) {
        throw std::runtime_error("Некорректный номер города K2: " + std::to_string(k2));
    }
    
    if (!GraphUtils::isValidL(L)) {
        throw std::runtime_error("Некорректное значение L: " + std::to_string(L));
    }
    
    if (k1 == k2) {
        throw std::runtime_error("K1 и K2 не могут быть одинаковыми");
    }
}