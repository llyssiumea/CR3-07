/**
 * @file graph_utils.cpp
 * @brief Реализация вспомогательных функций для работы с графами
 * @version 2.3
 */

#include "graph_utils.h"
#include <algorithm>

BFSResult GraphUtils::breadthFirstSearch(const AdjacencyMatrix& graph, int start, int maxDistance) {
    int n = graph.size();
    BFSResult result;
    result.distances.resize(n, -1);
    
    std::queue<int> q;
    q.push(start);
    result.distances[start] = 0;
    
    // НЕ добавляем стартовый город в достижимые
    // result.reachable.insert(start); // ЗАКОММЕНТИРОВАНО!
    
    while (!q.empty()) {
        int current = q.front();
        q.pop();
        
        // Если достигли максимального расстояния, не идем дальше
        if (result.distances[current] >= maxDistance) {
            continue;
        }
        
        // Обход соседей
        for (int neighbor = 0; neighbor < n; ++neighbor) {
            if (graph[current][neighbor] == 1 && result.distances[neighbor] == -1) {
                result.distances[neighbor] = result.distances[current] + 1;
                // Добавляем только соседей (не стартовый город)
                result.reachable.insert(neighbor);
                q.push(neighbor);
            }
        }
    }
    
    return result;
}

bool GraphUtils::isValidCity(int city, int cityCount) {
    return city >= 1 && city <= cityCount;
}

bool GraphUtils::isValidL(int L) {
    return L >= 0;
}

std::vector<int> GraphUtils::findIntersection(const std::set<int>& set1, const std::set<int>& set2) {
    std::vector<int> intersection;
    
    for (int city : set1) {
        if (set2.find(city) != set2.end()) {
            intersection.push_back(city);
        }
    }
    
    std::sort(intersection.begin(), intersection.end());
    return intersection;
}