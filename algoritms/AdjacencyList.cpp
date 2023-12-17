#include <iostream>
#include <vector>
#include <utility>
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;

vector<vector<int>> createAdjacencyList(vector<pair<int, int>> edges, const int count) {
    vector<vector<int>> adjacencyList(count);

    for (int i = 0; i < edges.size(); ++i) {
        int vertex1 = edges[i].first;
        int vertex2 = edges[i].second;
        adjacencyList[vertex1].push_back(vertex2);
        adjacencyList[vertex2].push_back(vertex1);
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

    vector<vector<int>> adjacencyList = createAdjacencyList(data, count);
    json result = adjacencyList;

    cout << result;
}