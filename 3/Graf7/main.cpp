/**
 * @file main.cpp
 * @brief Основная программа анализатора графа
 * @version 2.1
 * 
 * Главный модуль программы для поиска общих городов
 * между двумя штаб-квартирами корпораций
 */

#include <iostream>
#include <iomanip>
#include "graph_reader.h"
#include "graph_analyzer.h"

/**
 * @brief Вывод результата
 * @param result Вектор с номерами городов или {-1}
 */
void printResult(const std::vector<int>& result) {
    if (result.size() == 1 && result[0] == -1) {
        std::cout << -1 << std::endl;
    } else {
        for (size_t i = 0; i < result.size(); ++i) {
            std::cout << result[i];
            if (i < result.size() - 1) {
                std::cout << " ";
            }
        }
        std::cout << std::endl;
    }
}

/**
 * @brief Вывод множества достижимых городов (для отладки)
 * @param cities Множество городов (0-based)
 * @param name Название множества
 */
void printReachableCities(const std::set<int>& cities, const std::string& name) {
    std::cout << name << ": ";
    for (int city : cities) {
        std::cout << (city + 1) << " ";
    }
    std::cout << std::endl;
}

/**
 * @brief Вывод информации о графе
 * @param cityCount Количество городов
 * @param matrix Матрица смежности
 */
void printGraphInfo(int cityCount, const AdjacencyMatrix& matrix) {
    std::cout << "=== АНАЛИЗ ГРАФА ГОРОДОВ ===" << std::endl;
    std::cout << "Количество городов: " << cityCount << std::endl;
    std::cout << std::endl;
    
    std::cout << "Матрица смежности:" << std::endl;
    for (int i = 0; i < cityCount; ++i) {
        for (int j = 0; j < cityCount; ++j) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

/**
 * @brief Основная функция программы
 * @return Код завершения программы
 */
int main() {
    try {
        std::string filename = "cities.txt";
        
        // Чтение графа из файла
        int cityCount;
        AdjacencyMatrix graph = GraphReader::readFromFile(filename, cityCount);
        
        // Вывод информации о графе
        printGraphInfo(cityCount, graph);
        
        // Создание анализатора
        GraphAnalyzer analyzer(graph, cityCount);
        
        // Ввод параметров
        int k1, k2, L;
        std::cout << "Введите номера городов для штаб-квартир K1 и K2 (1-" 
                  << cityCount << "): ";
        std::cin >> k1 >> k2;
        
        std::cout << "Введите максимальное количество промежуточных городов L: ";
        std::cin >> L;
        
        // Проверка ввода
        if (std::cin.fail()) {
            throw std::runtime_error("Ошибка ввода данных");
        }
        
        // Поиск общих городов
        std::vector<int> result = analyzer.findCommonCities(k1, k2, L);
        
        // Вывод результата
        std::cout << std::endl;
        std::cout << "РЕЗУЛЬТАТ:" << std::endl;
        std::cout << "Города, достижимые из обоих штаб-квартир ";
        std::cout << "K1=" << k1 << " и K2=" << k2;
        std::cout << " (максимум " << L << " промежуточных городов):" << std::endl;
        
        printResult(result);
        
        std::cout << std::endl;
        std::cout << "Программа завершена успешно." << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "ОШИБКА: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}

// g++ -std=c++11 -o graph_analyzer main.cpp graph_reader.cpp graph_analyzer.cpp graph_utils.cpp
// ./graph_analyzer
