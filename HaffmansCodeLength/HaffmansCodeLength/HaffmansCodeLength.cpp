#include <iostream>
#include <fstream>
#include <limits>

long long clear_min(long long* arr, int& arr_index, int& arr_size,
    long long* res, int& res_index, int& res_size) {
    if (arr_index < arr_size && (res_index >= res_size || arr[arr_index] <= res[res_index])) {
        return arr[arr_index++];
    }
    else {
        return res[res_index++];
    }
}

long long int codeLength(long long int* arr, int n) {
    long long int* res = new long long int[n];
    int arr_index = 0;
    int res_index = 0;
    int res_size = 0;
    int arr_size = n;
    long long int result = 0;

    for (int i = 0; i < n - 1; ++i) {
        long long int temp1 = clear_min(arr, arr_index, arr_size, res, res_index, res_size);
        long long int temp2 = clear_min(arr, arr_index, arr_size, res, res_index, res_size);
        long long int temp = temp1 + temp2;
        res[res_size++] = temp;
        result += temp;
    }

    delete[] res;
    return result;
}

int main()
{
    std::ifstream in("huffman.in");
	if (!in.is_open()) {
		std::cerr << "Failed opening file.\n";
		return -1;
	}
    int n;
	in >> n;
    long long int* arr = new long long int [n];
	for (int i = 0; i < n; i++) {
        in >> arr[i];
	}
	in.close();

    std::ofstream out("huffman.out");
	if (!out.is_open()) {
		std::cerr << "Failed opening file.\n";
		return -1;
	}
    out << codeLength(arr, n);
	out.close();
}