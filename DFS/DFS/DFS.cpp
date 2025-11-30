#include <iostream>
#include <fstream>

void dfs(size_t& index, bool** matr, short n, bool visited[], short order[], short& next_ind) {
    visited[index] = 1;
    order[index] = next_ind++;
    for (size_t i = 0; i < n; i++) if (matr[index][i] && !visited[i]) dfs(i, matr, n, visited, order, next_ind);
}

int main() {
    short n;
    std::ifstream in("input.txt");
    if (!in.is_open()) {
        std::cerr << "Failed opening file.\n";
        return -1;
    }
    in >> n;
    bool** matr = new bool* [n];
    for (size_t i = 0; i < n; i++) matr[i] = new bool[n];
    for (size_t i = 0; i < n; i++) for (size_t j = 0; j < n; j++) in >> matr[i][j];
    short* order = new short[n];
    for (size_t i = 0; i < n; i++) order[i] = -1;
    bool* visited = new bool[n];
    for (size_t i = 0; i < n; i++) visited[i] = 0;
    in.close();

    short next_idx = 0;
    for (size_t i = 0; i < n; i++) if (!visited[i]) dfs(i, matr, n, visited, order, next_idx);

    std::ofstream out("output.txt");
    for (int i = 0; i < n; i++) out << order[i] + 1 << " ";
    out << "\n";
    out.close();
    delete[] order;
    delete[] visited;
    for (int i = 0; i < n; i++) delete[] matr[i];
    delete[] matr;
    return 0;
}
