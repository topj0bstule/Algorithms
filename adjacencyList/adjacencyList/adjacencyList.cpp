#include <iostream>
#include <stack>
#include <fstream>

struct AdjacencyList {
    int size = 0;
    std::stack<int> list;
};

int main()
{
    int n, m, u, v;
    std::ifstream in("input.txt");
    if (!in.is_open()) {
        std::cerr << "Failed opening file.\n";
        return -1;
    }
    in >> n >> m;
    AdjacencyList* list = new AdjacencyList[n];
    for (size_t i = 0; i < m; i++) {
        in >> u >> v;
        list[u - 1].list.push(v);
        list[u - 1].size++;
        list[v - 1].list.push(u);
        list[v - 1].size++;
    }
    in.close();
    std::ofstream out("output.txt");
    if (!out.is_open()) {
        std::cerr << "Failed opening file.\n";
        return -1;
    }
    for (size_t i = 0; i < n; i++) {
        out << list[i].size << " ";
        while (!list[i].list.empty()) {
            out << list[i].list.top() << " ";
            list[i].list.pop();
        }
        out << "\n";
    }
    out.close();
}
