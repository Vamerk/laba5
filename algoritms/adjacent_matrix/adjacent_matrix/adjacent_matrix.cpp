#include <iostream>
#include <fstream>
#include <sstream>
#include <utility>
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;

vector<vector<int>> createAdjacencyMatrix(vector<pair<int, int>> edges, const int count) {
    vector<vector<int>> matrix;

    for (int i = 0; i < count; i++) {
        vector<int> row;
        for (int j = 0; j < count; j++) {
            row.push_back(0);
        }

        matrix.push_back(row);
    }

    for (int i = 0; i < edges.size(); ++i) {
        int vertex1 = edges[i].first;
        int vertex2 = edges[i].second;
        matrix[vertex1][vertex2] = 1;
        matrix[vertex2][vertex1] = 1;
    }

    return matrix;
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

    // std::vector<std::pair<int, int>> data = parseDataFromJSON("{ \"data\": [[0, 1], [1, 0], [1, 2]], \"count\": 3 }");
    // int count = parseCountFromJSON("{ \"data\": [[0, 1], [1, 0], [1, 2]], \"count\": 3 }");

    std::vector<std::pair<int, int>> data = parseDataFromJSON(inputJsonString);
    int count = parseCountFromJSON(inputJsonString);

    vector<vector<int>> matrix = createAdjacencyMatrix(data, count);
    json result = matrix;
    cout << result;
}