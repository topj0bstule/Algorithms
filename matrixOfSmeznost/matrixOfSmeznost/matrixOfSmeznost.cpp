#include <iostream>
#include <fstream>

struct Edge {
    short n;
    short m;
};

int main()
{
    short n, m, temp1, temp2;

    std::ifstream in("input.txt");
    if (!in.is_open()) {
        std::cerr << "Failed opening file.\n";
        return -1;
    }
    in >> n >> m;
    short** matr = new short* [n];
    for (size_t i = 0; i < n; i++)
        matr[i] = new short[n];
    for (size_t i = 0; i < n; i++)
        for (size_t j = 0; j < n; j++)
            matr[i][j] = 0;
    while (in >> temp1 >> temp2) {
        matr[temp1 - 1][temp2 - 1] = 1;
        matr[temp2 - 1][temp1 - 1] = 1;
    }
    in.close();

    std::ofstream out("output.txt");
    if (!out.is_open()) {
        std::cerr << "Failed opening file.\n";
        return -1;
    }
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < n; j++) {
            out << matr[i][j] << " ";
        }
        out << "\n";
    }
    out.close();
    return 0;
}
