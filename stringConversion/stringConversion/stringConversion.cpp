#include <iostream>
#include <vector>
#include <string>

long long int min3(long long int a, long long int b, long long int c) {
    if (a <= b && a <= c) return a;
    else if (b <= a && b <= c) return b;
    return c;
}

long long int min2(long long int a, long long int b) {
    if (a <= b) return a;
    return b;
}

long long int levenstein(std::string str1, std::string str2, int x, int y, int z) {
    long long int** resultsMatrix = new long long int* [str1.size() + 1];
    for (size_t i = 0; i <= str1.size(); ++i)
        resultsMatrix[i] = new long long int[str2.size() + 1];
    for (size_t i = 0; i <= str1.size(); ++i) resultsMatrix[i][0] = i * x;
    for (size_t j = 0; j <= str2.size(); ++j) resultsMatrix[0][j] = j * y;
    for (size_t i = 1; i <= str1.size(); ++i) {
        for (size_t j = 1; j <= str2.size(); ++j) {
            resultsMatrix[i][j] = min3(resultsMatrix[i - 1][j] + x, 
                resultsMatrix[i][j - 1] + y, 
                resultsMatrix[i - 1][j - 1] + (str1[i - 1] == str2[j - 1] ? 0 : 1) * min2(z, x + y));
        }
    }

    long long int result = resultsMatrix[str1.size()][str2.size()];
    for (size_t i = 0; i <= str1.size(); ++i) {
        delete[] resultsMatrix[i];
    }
    delete[] resultsMatrix;
    return result;
}


int main()
{
    FILE* inFile;
    FILE* outFile;
    if (freopen_s(&inFile, "in.txt", "r", stdin) != 0 || freopen_s(&outFile, "out.txt", "w", stdout) != 0) {
        std::cerr << "Failed opening file";
        return 1;
    }

    int x, y, z;
    std::cin >> x >> y >> z;
    std::cin.ignore();
    std::string str1, str2;
    std::getline(std::cin, str1);
    std::getline(std::cin, str2);
    long long int result = levenstein(str1, str2, x, y, z);
    std::cout << result;
    return 0;
}