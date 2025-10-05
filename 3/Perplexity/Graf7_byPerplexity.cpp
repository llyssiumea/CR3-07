// https://www.perplexity.ai/search/reshit-zadachu-na-iazyke-c-pod-FYSfQs2RR8SiyBDpe7KMww

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <set>

using namespace std;

// Функция для поиска вершин, достижимых из start за <= maxSteps ребер (с учетом промежуточных городов)
set<int> reachableCities(const vector<vector<int>>& matrix, int start, int maxSteps) {
    int n = matrix.size();
    vector<int> dist(n, -1);
    queue<int> q;

    dist[start] = 0;
    q.push(start);

    set<int> reachable;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        // Добавляем в множество достижимых городов, кроме стартового
        if (u != start) reachable.insert(u);

        // Обход соседей
        for (int v = 0; v < n; ++v) {
            if (matrix[u][v] == 1 && dist[v] == -1) {
                dist[v] = dist[u] + 1;
                // Учитываем только города, достижимые в пределах maxSteps
                if (dist[v] <= maxSteps + 1) { 
                    q.push(v);
                }
            }
        }
    }
    return reachable;
}

int main() {
    string filename;
    cout << "Введите имя файла с матрицей смежности: ";
    cin >> filename;

    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Ошибка открытия файла" << endl;
        return 1;
    }

    int n;
    file >> n;

    if (n <= 0 || n > 25) {
        cerr << "Некорректное количество городов" << endl;
        return 1;
    }

    vector<vector<int>> matrix(n, vector<int>(n, 0));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            file >> matrix[i][j];
        }
    }

    file.close();

    int K1, K2, L;
    cout << "Введите номера двух городов (K1 K2) и L: ";
    cin >> K1 >> K2 >> L;

    // Корректируем индексы для массива (нумерация с 0)
    K1--; K2--;

    if (K1 < 0 || K1 >= n || K2 < 0 || K2 >= n || L < 0) {
        cerr << "Некорректные параметры" << endl;
        return 1;
    }

    // Получаем множество достижимых городов из обоих штабов за L промежуточных городов
    set<int> reachableFromK1 = reachableCities(matrix, K1, L);
    set<int> reachableFromK2 = reachableCities(matrix, K2, L);

    // Находим пересечение множеств
    vector<int> commonCities;
    for (int city : reachableFromK1) {
        if (reachableFromK2.count(city)) {
            commonCities.push_back(city + 1); // возвращаем к 1-индексации
        }
    }

    if (commonCities.empty()) {
        cout << -1 << endl;
    } else {
        sort(commonCities.begin(), commonCities.end());
        for (int city : commonCities) {
            cout << city << " ";
        }
        cout << endl;
    }

    return 0;
}
