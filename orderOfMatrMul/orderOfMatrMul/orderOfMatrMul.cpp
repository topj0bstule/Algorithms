#include <iostream>
#include <fstream>
#include <climits>

struct Matrix {
    short rows;
    short columns;
};

int minMultiplication(short kolvoMatrix, Matrix matrix[]) {
    if (kolvoMatrix == 0 || kolvoMatrix == 1) return 0;
    short* sizes = new short[kolvoMatrix + 1];
    sizes[0] = matrix[0].rows;
    for (size_t i = 1; i < kolvoMatrix + 1; i++) sizes[i] = matrix[i - 1].columns;
    int** matrixOfMultiplications = new int* [kolvoMatrix];
    for (size_t i = 0; i < kolvoMatrix; i++) {
        matrixOfMultiplications[i] = new int[kolvoMatrix];
        for (size_t j = 0; j < kolvoMatrix; j++) matrixOfMultiplications[i][j] = 0;
    }

    for (size_t chainSize = 2; chainSize <= kolvoMatrix; chainSize++) {
        for (size_t i = 0; i < kolvoMatrix - chainSize + 1; i++) {
            int j = i + chainSize - 1;
            matrixOfMultiplications[i][j] = 2147483647;
            for (size_t k = i; k < j; k++) {
                int temp = matrixOfMultiplications[i][k] + matrixOfMultiplications[k + 1][j] + sizes[i] * sizes[k + 1] * sizes[j + 1];
                if (temp < matrixOfMultiplications[i][j]) matrixOfMultiplications[i][j] = temp;
            }
        }
    }

    unsigned long long int result = (long long int)matrixOfMultiplications[0][kolvoMatrix - 1];
    for (size_t i = 0; i < kolvoMatrix; i++) delete[] matrixOfMultiplications[i];
    delete[] matrixOfMultiplications;
    delete[] sizes;
    return result;
}

int main()
{
    std::ifstream in("input.txt");
    short kolvoMatrix = 0;
    in >> kolvoMatrix;
    in.ignore();
    Matrix* matrix = new Matrix[kolvoMatrix];
    for (size_t i = 0; i < kolvoMatrix; i++) {
        in >> matrix[i].rows >> matrix[i].columns;
    }
    std::ofstream out("output.txt");
    out << minMultiplication(kolvoMatrix, matrix);
    delete[] matrix;
    return 0;
}