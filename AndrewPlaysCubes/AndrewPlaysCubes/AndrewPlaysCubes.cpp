#include <iostream>
#include <climits>

struct CubeIndexes {
    unsigned long long int rows;
    unsigned long long int columns;
};

unsigned long long int minAndrewPlays(short kolvoCubes, CubeIndexes cubes[]) {
    if (kolvoCubes == 0 || kolvoCubes == 1) return 0;
    unsigned long long int** matrixOfMultiplications = new unsigned long long int* [kolvoCubes];
    for (size_t i = 0; i < kolvoCubes; i++) {
        matrixOfMultiplications[i] = new unsigned long long int[kolvoCubes];
        for (size_t j = 0; j < kolvoCubes; j++) matrixOfMultiplications[i][j] = 0;
    }

    for (size_t chainSize = 2; chainSize <= kolvoCubes; chainSize++) {
        for (size_t i = 0; i < kolvoCubes - chainSize + 1; i++) {
            size_t j = i + chainSize - 1;
            matrixOfMultiplications[i][j] = ULLONG_MAX;
            for (size_t k = i; k < j; k++) {
                unsigned long long int temp = matrixOfMultiplications[i][k] + matrixOfMultiplications[k + 1][j] + cubes[i].rows * cubes[j].columns;
                if (temp < matrixOfMultiplications[i][j]) matrixOfMultiplications[i][j] = temp;
            }
        }
    }

    unsigned long long int result = matrixOfMultiplications[0][kolvoCubes - 1];
    for (size_t i = 0; i < kolvoCubes; i++) delete[] matrixOfMultiplications[i];
    delete[] matrixOfMultiplications;
    return result;
}

int main()
{
    short kolvoCubes = 0;
    std::cin >> kolvoCubes;
    CubeIndexes* cubes = new CubeIndexes[kolvoCubes];
    for (size_t i = 0; i < kolvoCubes; i++) {
        std::cin >> cubes[i].rows >> cubes[i].columns;
    }
    std::cout << minAndrewPlays(kolvoCubes, cubes);
    delete[] cubes;
    return 0;
}