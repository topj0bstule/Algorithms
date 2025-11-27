#include <iostream>
#include <fstream>

int main()
{
    int n, temp1, temp2;

    std::ifstream in("input.txt");
    in >> n;
    if (!in.is_open()) {
        std::cerr << "Failed opening file.\n";
        return -1;
    }
    int* parents = new int[n];
    for (size_t i = 0; i < n; i++) parents[i] = 0;
    while (in >> temp1 >> temp2) {
        parents[temp2 - 1] = temp1;
    }
    in.close();

    std::ofstream out("output.txt");
    if (!out.is_open()) {
        std::cerr << "Failed opening file.\n";
        return -1;
    }
    for (size_t i = 0; i < n; i++) out << parents[i] << " ";
    out.close();
    return 0;
}
