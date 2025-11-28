#include <iostream>
#include <fstream>

int main()
{
    short n, temp1, temp2;

    std::ifstream in("input.txt");
    if (!in.is_open()) {
        std::cerr << "Failed opening file.\n";
        return -1;
    }
    in >> n;
    bool** matr = new bool* [n];
    for (size_t i = 0; i < n; i++)
        matr[i] = new bool[n];
    short* parents = new short[n];
    for (size_t i = 0; i < n; i++) parents[i] = 0;
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < n; j++) {
            in >> matr[i][j];
            if (matr[i][j] == 1) parents[j] = i + 1;
        }
    }
    in.close();

    std::ofstream out("output.txt");
    if (!out.is_open()) {
        std::cerr << "Failed opening file.\n";
        return -1;
    }
    for (size_t i = 0; i < n; i++) out << parents[i] << " ";
    out << "\n";
    out.close();
    return 0;
}