// pch.cpp: файл исходного кода, соответствующий предварительно скомпилированному заголовочному файлу

#include "pch.h"

// При использовании предварительно скомпилированных заголовочных файлов необходим следующий файл исходного кода для выполнения сборки.

#include <iostream>

IncidenceMatrix::IncidenceMatrix() {
    // Инициализация при необходимости
}

void IncidenceMatrix::addVertex() {
    for (auto& row : matrix) {
        row.push_back(0);
    }
    matrix.push_back(std::vector<int>(matrix.size(), 0));
}

void IncidenceMatrix::removeVertex(int vertex) {
    if (vertex < matrix.size()) {
        matrix.erase(matrix.begin() + vertex);
        for (auto& row : matrix) {
            row.erase(row.begin() + vertex);
        }
    }
}

void IncidenceMatrix::addEdge(int fromVertex, int toVertex) {
    if (fromVertex < matrix.size() && toVertex < matrix.size()) {
        matrix[fromVertex].push_back(1);
        matrix[toVertex].push_back(-1);
    }
}

void IncidenceMatrix::removeEdge(int fromVertex, int toVertex) {
    if (fromVertex < matrix.size() && toVertex < matrix.size()) {
        for (size_t i = 0; i < matrix[fromVertex].size(); ++i) {
            if (matrix[fromVertex][i] == 1 && matrix[toVertex][i] == -1) {
                matrix[fromVertex].erase(matrix[fromVertex].begin() + i);
                matrix[toVertex].erase(matrix[toVertex].begin() + i);
                break;
            }
        }
    }
}

void IncidenceMatrix::printMatrix() {
    for (const auto& row : matrix) {
        for (int val : row) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }
}