// https://chat.deepseek.com/a/chat/s/12c2f814-8c73-4033-89fd-c65128519de3

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

class GraphAnalyzer {
private:
    int n;
    vector<vector<int>> adjMatrix;
    vector<vector<int>> adjList;

    void buildAdjList() {
        adjList.resize(n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (adjMatrix[i][j] == 1) {
                    adjList[i].push_back(j);
                }
            }
        }
    }

    vector<int> findReachableCitiesWithDistance(int startCity, int L) {
        vector<int> distance(n, -1);
        queue<int> q;

        q.push(startCity);
        distance[startCity] = 0;

        while (!q.empty()) {
            int currentCity = q.front();
            q.pop();

            if (distance[currentCity] >= L + 1) {
                continue;
            }

            for (int neighbor : adjList[currentCity]) {
                if (distance[neighbor] == -1) {
                    distance[neighbor] = distance[currentCity] + 1;
                    q.push(neighbor);
                }
            }
        }

        return distance;
    }

public:
    GraphAnalyzer() : n(0) {}
    
    int getCityCount() { return n; }

    bool readGraphFromFile(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "Ошибка: не удалось открыть файл " << filename << endl;
            return false;
        }

        file >> n;
        if (n > 25 || n <= 0) {
            cerr << "Ошибка: некорректное количество городов " << n << endl;
            return false;
        }

        adjMatrix.resize(n, vector<int>(n));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                file >> adjMatrix[i][j];
            }
        }

        file.close();
        buildAdjList();
        return true;
    }

    vector<int> findCommonCities(int k1, int k2, int L) {
        if (k1 < 1 || k1 > n || k2 < 1 || k2 > n) {
            return {-1};
        }

        if (L < 0) {
            return {-1};
        }

        int start1 = k1 - 1;
        int start2 = k2 - 1;

        vector<int> distanceFromK1 = findReachableCitiesWithDistance(start1, L);
        vector<int> distanceFromK2 = findReachableCitiesWithDistance(start2, L);

        vector<int> commonCities;
        for (int i = 0; i < n; i++) {
            if (distanceFromK1[i] != -1 && distanceFromK2[i] != -1) {
                commonCities.push_back(i + 1);
            }
        }

        sort(commonCities.begin(), commonCities.end());

        if (commonCities.empty()) {
            return {-1};
        }

        return commonCities;
    }
};

int main() {
    GraphAnalyzer analyzer;
    string filename = "cities.txt";

    if (!analyzer.readGraphFromFile(filename)) {
        return 1;
    }

    int k1, k2, L;
    cout << "Введите K1, K2, L: ";
    cin >> k1 >> k2 >> L;

    if (cin.fail()) {
        cerr << "Ошибка ввода" << endl;
        return 1;
    }

    vector<int> result = analyzer.findCommonCities(k1, k2, L);

    if (result.size() == 1 && result[0] == -1) {
        cout << -1 << endl;
    } else {
        for (size_t i = 0; i < result.size(); i++) {
            cout << result[i];
            if (i < result.size() - 1) {
                cout << " ";
            }
        }
        cout << endl;
    }

    return 0;
}