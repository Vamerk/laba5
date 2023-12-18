#include <iostream>
#include <vector>
#include <nlohmann/json.hpp>
#include <queue>
#include <unordered_set>

using namespace std;
using json = nlohmann::json;

struct Edge {
    int src, dest, weight;
};

vector<Edge> createEdges(const vector<pair<int, int>>& edges) {
    vector<Edge> result;
    for (const auto& edge : edges) {
        result.push_back({ edge.first, edge.second, 1 }); 
        result.push_back({ edge.second, edge.first, 1 }); 
    }
    return result;
}

struct CompareEdges {
    bool operator()(const Edge& e1, const Edge& e2) const {
        return e1.weight > e2.weight;
    }
};

vector<Edge> minimumSpanningTree(const vector<Edge>& edges, int count) {
    vector<Edge> mst;
    vector<unordered_set<int>> sets(count);

    priority_queue<Edge, vector<Edge>, CompareEdges> pq;
    for (const auto& edge : edges) {
        pq.push(edge);
    }

    while (!pq.empty() && mst.size() < count - 1) {
        Edge e = pq.top();
        pq.pop();

        if (sets[e.src].find(e.dest) == sets[e.src].end()) {
            mst.push_back(e);
            sets[e.src].insert(e.dest);
            sets[e.dest].insert(e.src);
        }
    }

    return mst;
}

int main() {
    string inputJsonString;
    getline(cin, inputJsonString);

    vector<pair<int, int>> data = parseDataFromJSON(inputJsonString);
    int count = parseCountFromJSON(inputJsonString);

    vector<Edge> edges = createEdges(data);
    vector<Edge> mst = minimumSpanningTree(edges, count);

    json result;
    for (const auto& edge : mst) {
        result.push_back({ edge.src, edge.dest });
    }

    cout << result;
}