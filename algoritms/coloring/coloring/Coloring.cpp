#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <cstdlib>
#include <ctime>
#include <algorithm>

#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;

// Граф представлен в виде списка смежности
typedef map<int, set<int>> Graph;

// Индивидуальное решение (раскраска графа)
typedef map<int, int> Coloring;

// Создание случайной раскраски графа
Coloring createIndividual(const Graph& graph) {
    Coloring individual;
    for (const auto& node : graph) {
        individual[node.first] = rand() % graph.size();
    }
    return individual;
}

// Оценка приспособленности раскраски (чем меньше конфликтов, тем лучше)
int fitness(const Coloring& individual, const Graph& graph) {
    int conflicts = 0;
    for (const auto& node : graph) {
        for (int neighbor : node.second) {
            if (individual.at(node.first) == individual.at(neighbor)) {
                conflicts++;
            }
        }
    }
    return conflicts;
}

// Скрещивание двух раскрасок
Coloring crossover(const Coloring& parent1, const Coloring& parent2) {
    Coloring child;
    int crossoverPoint = rand() % parent1.size();
    auto iter1 = parent1.begin();
    auto iter2 = parent2.begin();
    for (int i = 0; i < crossoverPoint; ++i) {
        child[iter1->first] = iter1->second;
        ++iter1;
    }
    for (; iter2 != parent2.end(); ++iter2) {
        child[iter2->first] = iter2->second;
    }
    return child;
}

// Мутация раскраски
void mutate(Coloring& individual, double mutationRate) {
    for (auto& node : individual) {
        if ((rand() % 100) < (mutationRate * 100)) {
            node.second = rand() % individual.size();
        }
    }
}

// Генетический алгоритм
Coloring geneticAlgorithm(const Graph& graph, int populationSize, int generations, double mutationRate) {
    vector<Coloring> population;
    srand(static_cast<unsigned>(time(nullptr)));

    // Инициализация начальной популяции
    for (int i = 0; i < populationSize; ++i) {
        population.push_back(createIndividual(graph));
    }

    for (int generation = 0; generation < generations; ++generation) {
        // Оценка приспособленности
        vector<pair<int, int>> fitnessValues;  // Пары (приспособленность, индекс в популяции)
        for (int i = 0; i < populationSize; ++i) {
            int fit = fitness(population[i], graph);
            fitnessValues.push_back({ fit, i });
        }
        sort(fitnessValues.begin(), fitnessValues.end());

        // Выбор родителей
        vector<Coloring> parents;
        for (int i = 0; i < populationSize / 2; ++i) {
            parents.push_back(population[fitnessValues[i].second]);
        }

        // Создание нового поколения
        vector<Coloring> newPopulation;
        for (int i = 0; i < populationSize; ++i) {
            const Coloring& parent1 = parents[rand() % (populationSize / 2)];
            const Coloring& parent2 = parents[rand() % (populationSize / 2)];
            Coloring child = crossover(parent1, parent2);
            mutate(child, mutationRate);
            newPopulation.push_back(child);
        }

        population = newPopulation;
    }

    // Возвращение лучшего индивида
    return population[0];
}

map<int, set<int>> edgesToAdjacencyList(const vector<pair<int, int>>& edges) {
    map<int, set<int>> adjacencyList;
    for (const auto& edge : edges) {
        int node1 = edge.first;
        int node2 = edge.second;
        adjacencyList[node1].insert(node2);
        adjacencyList[node2].insert(node1);
    }
    return adjacencyList;
}

std::vector<std::pair<int, int>> parseDataFromJSON(std::string jsonString) {
    json jsonData = json::parse(jsonString);

    std::vector<std::pair<int, int>> data;
    for (const auto& row : jsonData["data"]) {
        data.push_back({ row[0], row[1] });
    }

    return data;
}

int parseCountFromJSON(string jsonString) {
    json jsonData = json::parse(jsonString);
    int result = jsonData["count"];

    return result;
}


int main() {
    string inputJsonString;
    getline(cin, inputJsonString);

    std::vector<std::pair<int, int>> data = parseDataFromJSON(inputJsonString);
    int count = parseCountFromJSON(inputJsonString);
    /*
    { "data": [[0, 1], [1, 0], [1, 2], [2, 5], [3, 1], [3, 5], [2, 4]], "count": 6 }
    */

    map<int, set<int>> graph = edgesToAdjacencyList(data);

    int populationSize = 10;
    int generations = 100;
    double mutationRate = 0.1;

    Coloring bestSolution = geneticAlgorithm(graph, populationSize, generations, mutationRate);

    json res = bestSolution;
    cout << res << endl;

    return 0;
}
