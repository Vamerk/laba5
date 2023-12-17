
#include <iostream>
#include <fstream>
#include <sstream>
#include <utility>
#include <vector>
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;

const int MAX_VERTICES = 100;

vector<vector<int>> createWeightedMatrix(vector<pair<int, int>>edges, const std::vector<int>& weights, const int count) {
    vector<vector<int>> matrix;

    for (int i = 0; i < count; ++i) {
        vector<int> row;
        for (int j = 0; j < count; ++j) {
            row.push_back(0);
        }
        matrix.push_back(row);
    }

    for (int j = 0; j < edges.size(); ++j) {
        int vertex1 = edges[j].first;
        int vertex2 = edges[j].second;
        int weight = weights[j];
        matrix[vertex1][vertex2] = weight;
        matrix[vertex2][vertex1] = weight;
    }

    for (int i = 0; i < count; ++i) {
        matrix[i][i] = 0;
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

std::vector<int> parseWeightFromJSON(string jsonString) {
    json jsonData = json::parse(jsonString);

    std::vector<int> weight;
    for (const auto& row : jsonData["weights"]) {
        weight.push_back(row);
    }

    return weight;
}

int main() {
    /* 
    { "data": [[0, 1], [1, 0], [1, 2]],  "weights" : [10, 20, 40], "count" : 3 } 
    */ 
    string inputJsonString;
    getline(cin, inputJsonString);

    std::vector<std::pair<int, int>> data = parseDataFromJSON(inputJsonString);
    int count = parseCountFromJSON(inputJsonString);
    std::vector<int> weights = parseWeightFromJSON(inputJsonString);


    vector<vector<int>> matrix = createWeightedMatrix(data, weights, count);
    json result = matrix;
    cout << result;
}