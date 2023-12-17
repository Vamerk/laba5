#include <iostream>
#include <fstream>
#include <sstream>
#include <utility>
#include <vector>

const int MAX_VERTICES = 100; 
const int INF = 9999; 

void createWeightedMatrix(int weightedMatrix[MAX_VERTICES][MAX_VERTICES], const std::pair<int, int> edges[], const std::vector<int>& weights, int numEdges) {
    for (int i = 0; i < MAX_VERTICES; ++i) {
        for (int j = 0; j < MAX_VERTICES; ++j) {
            weightedMatrix[i][j] = INF;
        }
    }

    for (int j = 0; j < numEdges; ++j) {
        int vertex1 = edges[j].first;
        int vertex2 = edges[j].second;
        int weight = weights[j];
        weightedMatrix[vertex1][vertex2] = weight;
        weightedMatrix[vertex2][vertex1] = weight; 
    }

    for (int i = 0; i < MAX_VERTICES; ++i) {
        weightedMatrix[i][i] = 0;
    }
}

std::string weightedMatrixToJsonString(int weightedMatrix[MAX_VERTICES][MAX_VERTICES]) {
    std::stringstream ss;
    ss << "{";

    for (int i = 0; i < MAX_VERTICES; ++i) {
        ss << "\"" << i << "\": [";
        for (int j = 0; j < MAX_VERTICES; ++j) {
            if (weightedMatrix[i][j] == INF) {
                ss << "INF";
            }
            else {
                ss << weightedMatrix[i][j];
            }
            if (j < MAX_VERTICES - 1) {
                ss << ", ";
            }
        }
        ss << "]";
        if (i < MAX_VERTICES - 1) {
            ss << ", ";
        }
    }

    ss << "}";
    return ss.str();
}

int main() {
    int weightedMatrix[MAX_VERTICES][MAX_VERTICES];
    std::pair<int, int> edges[] = { {0, 1}, {1, 2}, {2, 3}, {3, 0}, {1, 3} }; 
    std::vector<int> weights = { 2, 3, 1, 4, 5 }; 

    int numEdges = sizeof(edges) / sizeof(edges[0]);

    createWeightedMatrix(weightedMatrix, edges, weights, numEdges);

    std::string jsonString = weightedMatrixToJsonString(weightedMatrix);
    std::ofstream outputFile("output_weights.json");
    if (outputFile.is_open()) {
        outputFile << jsonString;
        outputFile.close();
        std::cout << "JSON-строка весовой матрицы записана в файл 'output_weights.json'" << std::endl;
    }
    else {
        std::cerr << "Ошибка при открытии файла" << std::endl;
        return 1;
    }

    return 0;
}