#include <iostream>
#include <fstream>
#include <sstream>
#include <utility>

const int MAX_VERTICES = 100; // Максимальное количество вершин в графе

void createAdjacencyMatrix(int adjacencyMatrix[MAX_VERTICES][MAX_VERTICES], const std::pair<int, int> edges[], int numEdges) {
    // Инициализируем матрицу смежности нулями
    for (int i = 0; i < MAX_VERTICES; ++i) {
        for (int j = 0; j < MAX_VERTICES; ++j) {
            adjacencyMatrix[i][j] = 0;
        }
    }

    // Заполняем матрицу смежности на основе массива смежных пар вершин
    for (int i = 0; i < numEdges; ++i) {
        int vertex1 = edges[i].first;
        int vertex2 = edges[i].second;
        adjacencyMatrix[vertex1][vertex2] = 1;
        adjacencyMatrix[vertex2][vertex1] = 1; // для неориентированного графа
    }
}

std::string adjacencyMatrixToJsonString(int adjacencyMatrix[MAX_VERTICES][MAX_VERTICES]) {
    std::stringstream ss;
    ss << "{";

    for (int i = 0; i < MAX_VERTICES; ++i) {
        ss << "\"" << i << "\": [";
        for (int j = 0; j < MAX_VERTICES; ++j) {
            ss << adjacencyMatrix[i][j];
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
    int adjacencyMatrix[MAX_VERTICES][MAX_VERTICES];
    std::pair<int, int> edges[] = { {0, 1}, {1, 2}, {2, 3}, {3, 0}, {1, 3} }; // Пример массива смежных пар

    int numEdges = sizeof(edges) / sizeof(edges[0]);

    createAdjacencyMatrix(adjacencyMatrix, edges, numEdges);

    // Выводим JSON-строку в файл
    std::string jsonString = adjacencyMatrixToJsonString(adjacencyMatrix);

    std::ofstream outputFile("output.json");
    if (outputFile.is_open()) {
        outputFile << jsonString;
        outputFile.close();
    }
    else {

        return 1;
    }

    return 0;
}
