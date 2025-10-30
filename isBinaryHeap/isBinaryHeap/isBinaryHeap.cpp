#include <iostream>
#include <fstream>

bool isBinaryHeap(int arr[], int size) {
    for (int i = size - 1; i > 0; i--) {
        if (arr[(i - 1) / 2] > arr[i]) return false;
    }
    return true;
}

int main()
{
    int size;
    std::ifstream in("input.txt");
    if (!in.is_open()) {
        std::cerr << "Failed opening file.\n";
        return -1;
    }
    in >> size;
    int* arr = new int[size];
    for (size_t i = 0; i < size; i++) {
        in >> arr[i];
    }
    in.close();

    bool result = isBinaryHeap(arr, size);

    std::ofstream out("output.txt");
    if (!out.is_open()) {
        std::cerr << "Failed opening file.\n";
        return -1;
    }
    if (result) out << "Yes";
    else out << "No";

    delete[] arr;
}