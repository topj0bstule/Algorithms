#include <iostream>
#include <fstream>
#include <vector>
#include <set>

int findIndexFirstHigher(std::vector<int>& vec, int numberForFinding) {
    int left = 0;
    int right = vec.size() - 1;
    int mid = left + (right - left) / 2;
    while (left <= right) {
        if (vec[mid] < numberForFinding) left = mid + 1;
        else if (vec[mid] == numberForFinding || vec[mid] > numberForFinding) right = mid - 1;
        mid = left + (right - left) / 2;
    }
    return mid;
}

int LIS(const std::vector<int>& arr) {
    std::vector<int> subArr;
    for (int i = 0; i < arr.size(); ++i) {
        int pos = findIndexFirstHigher(subArr, arr[i]);
        if (pos == subArr.size())
            subArr.push_back(arr[i]);
        else
            subArr[pos] = arr[i];
    }
    return subArr.size();
}

int main() {
    FILE* inFile;
    FILE* outFile;
    if (freopen_s(&inFile, "input.txt", "r", stdin) != 0 ||
        freopen_s(&outFile, "output.txt", "w", stdout) != 0) {
        std::cerr << "Ошибка открытия файлов." << std::endl;
        return 1;
    }
    int n;
    std::cin >> n;
    std::vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> arr[i];
    }
    int result = LIS(arr);
    std::cout << result;
}