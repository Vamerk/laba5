#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <set>
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;

typedef pair<int, int> iPair;

vector<pair<int, int>> findMinimumSpanningTree(vector<pair<int, int>>& edges, const int count) {
    vector<pair<int, int>> mst;

    priority_queue<iPair, vector<iPair>, greater<iPair>> pq;

    for (auto& edge : edges) {
        pq.push({ 0, edge.first });
        pq.push({ 0, edge.second });
    }

    set<int> visited;

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        if (visited.find(u) != visited.end()) continue;

        visited.insert(u);

        if (!mst.empty() || visited.size() < count) {
            int parent = u;
            int child = (mst.empty()) ? u : mst[parent].second;
            mst.push_back({ parent, child });
        }
        for (auto& edge : edges) {
            if (edge.first == u || edge.second == u) {
                int v = (edge.first == u) ? edge.second : edge.first;
                if (visited.find(v) == visited.end()) {
                    pq.push({ 0, v });
                }
            }
        }
    }

    return mst;
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

    vector<pair<int, int>> mst = findMinimumSpanningTree(data, count);

    json result;
    for (const auto& edge : mst) {
        result["edges"].push_back({ edge.first, edge.second });
    }

    cout << result;
}

