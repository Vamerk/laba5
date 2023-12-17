#include <iostream>
#include <fstream>
#include <sstream>
#include <utility>
#include <vector>

const int MAX_VERTICES = 100; 

void createIncidenceMatrix(int incidenceMatrix[MAX_VERTICES][MAX_VERTICES], const std::pair<int, int> edges[], int numEdges) {
    for (int i = 0; i < MAX_VERTICES; ++i) {
        for (int j = 0; j < numEdges; ++j) {
            incidenceMatrix[i][j] = 0;
        }
    }

    for (int j = 0; j < numEdges; ++j) {
        int vertex1 = edges[j].first;
        int vertex2 = edges[j].second;
        incidenceMatrix[vertex1][j] = 1;
        incidenceMatrix[vertex2][j] = 1;
    }
}

std::string incidenceMatrixToJsonString(int incidenceMatrix[MAX_VERTICES][MAX_VERTICES], int numEdges) {
    std::stringstream ss;
    ss << "{";

    for (int i = 0; i < MAX_VERTICES; ++i) {
        ss << "\"" << i << "\": [";
        for (int j = 0; j < numEdges; ++j) {
            ss << incidenceMatrix[i][j];
            if (j < numEdges - 1) {
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
    int incidenceMatrix[MAX_VERTICES][MAX_VERTICES];
    std::pair<int, int> edges[] = { {0, 1}, {1, 2}, {2, 3}, {3, 0}, {1, 3} }; 

    int numEdges = sizeof(edges) / sizeof(edges[0]);

    createIncidenceMatrix(incidenceMatrix, edges, numEdges);

    std::string jsonString = incidenceMatrixToJsonString(incidenceMatrix, numEdges);
    std::ofstream outputFile("output.json");
    if (outputFile.is_open()) {
        outputFile << jsonString;
        outputFile.close();
        std::cout << "JSON-строка записана в файл 'output.json'" << std::endl;
    }
    else {
        std::cerr << "Ошибка при открытии файла" << std::endl;
        return 1;
    }

    return 0;
}