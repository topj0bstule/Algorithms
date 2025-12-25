#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

struct Edge {
    short u;
    short v;
    short w;
};

long long int dijkstra(int n, std::vector<std::vector<std::pair<short, short>>>& graph) {
    std::vector<long long> cost(n + 1, LLONG_MAX);
    std::vector<bool> processed(n + 1, false);
    cost[1] = 0;
    using P = std::pair<long long, int>;
    std::priority_queue<P, std::vector<P>, std::greater<P>> pq;
    pq.push({ 0, 1 });
    while (!pq.empty()) {
        int vertex = pq.top().second;
        pq.pop();
        if (processed[vertex]) continue;
        processed[vertex] = true;
        for (size_t k = 0; k < graph[vertex].size(); k++) {
            int neighbourVertex = graph[vertex][k].first;
            int weight = graph[vertex][k].second;
            if (cost[neighbourVertex] > cost[vertex] + weight) {
                cost[neighbourVertex] = cost[vertex] + weight;
                pq.push({ cost[neighbourVertex], neighbourVertex });
            }
        }
    }

    return cost[n];
}

int main() {
    int n, m;
    short u, v, w;

    std::ifstream in("input.txt");
    if (!in.is_open()) {
        std::cerr << "Failed opening file.\n";
        return -1;
    }
    in >> n >> m;
    std::vector<std::vector<std::pair<short, short>>> graph(n + 1);
    for (size_t i = 0; i < m; i++) {
        in >> u >> v >> w;
        graph[u].push_back({ v, w });
        graph[v].push_back({ u, w });
    }
    in.close();

    std::ofstream out("output.txt");
    if (!out.is_open()) {
        std::cerr << "Failed opening file.\n";
        return -1;
    }
    out << dijkstra(n, graph);
    out.close();
    return 0;
}