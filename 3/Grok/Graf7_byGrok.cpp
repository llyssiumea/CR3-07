// https://grok.com/c/f18ed0d4-677a-4d0e-918f-c5611f84f692

#include <iostream>    // Для ввода/вывода
#include <fstream>     // Для чтения файла
#include <vector>      // Для матрицы и списков
#include <queue>       // Для BFS
#include <algorithm>   // Для сортировки
#include <string>      // Для имени файла

// Функция для чтения матрицы смежности из файла
std::vector<std::vector<int>> readGraphFromFile(const std::string& filename, int& n) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Не удалось открыть файл: " + filename);
    }
    file >> n;
    if (n < 1 || n > 25) {
        throw std::runtime_error("Некорректное количество городов: " + std::to_string(n));
    }
    std::vector<std::vector<int>> adj(n, std::vector<int>(n, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            file >> adj[i][j];
            if (adj[i][j] != 0 && adj[i][j] != 1) {
                throw std::runtime_error("Некорректное значение в матрице: " + std::to_string(adj[i][j]));
            }
        }
    }
    file.close();
    return adj;
}

// Функция для поиска достижимых городов в пределах max_dist ребер (BFS)
std::vector<bool> getReachableCities(int start, int max_dist, const std::vector<std::vector<int>>& adj, int n) {
    std::vector<bool> reachable(n, false);
    std::vector<int> dist(n, -1);
    std::queue<int> q;

    q.push(start);
    dist[start] = 0;
    reachable[start] = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        if (dist[u] >= max_dist) continue;

        for (int v = 0; v < n; ++v) {
            if (adj[u][v] == 1 && dist[v] == -1) {  // Есть ребро и не посещено
                dist[v] = dist[u] + 1;
                if (dist[v] <= max_dist) {
                    reachable[v] = true;
                    q.push(v);
                }
            }
        }
    }
    return reachable;
}

int main() {
    try {
        std::string filename = "cities.txt";  // Фиксированное имя файла как в задаче
        int n;
        auto adj = readGraphFromFile(filename, n);

        int K1, K2, L;
        std::cout << "Введите номера городов K1 и K2 (1.." << n << ") и L: ";
        std::cin >> K1 >> K2 >> L;

        // Исправленное условие проверки
        if (K1 < 1 || K1 > n || K2 < 1 || K2 > n || L < 0) {
            throw std::runtime_error("Некорректные значения K1, K2 или L");
        }

        // Максимальная дистанция в ребрах: L+1
        int max_dist = L + 1;

        // Достижимые от K1
        auto reachable_from_K1 = getReachableCities(K1 - 1, max_dist, adj, n);

        // Достижимые от K2
        auto reachable_from_K2 = getReachableCities(K2 - 1, max_dist, adj, n);

        // Пересечение: города, достижимые из обоих
        std::vector<int> intersection;
        for (int i = 0; i < n; ++i) {
            if (reachable_from_K1[i] && reachable_from_K2[i]) {
                intersection.push_back(i + 1);
            }
        }

        // Сортировка
        std::sort(intersection.begin(), intersection.end());

        // Вывод
        if (intersection.empty()) {
            std::cout << -1 << std::endl;
        } else {
            for (size_t i = 0; i < intersection.size(); ++i) {
                std::cout << intersection[i];
                if (i < intersection.size() - 1) std::cout << " ";
            }
            std::cout << std::endl;
        }

    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}