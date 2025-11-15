#include <iostream>
#include <cmath>

struct Request {
	std::string action = "";
	int num1 = -1; // либо число, либо индекс: зависит от action
	int num2 = -1;
};

long long int findSum(int num1, int num2, int arr[], int n, long long int blocks[], int sqrtN) {
	if (num2 <= num1) return 0;
	long long int result = 0;
	int posInBlocksNum1 = (int)(num1 / sqrtN) + 1; // у блоков 1-индексация
	int posInBlocksNum2 = (int)(num2 / sqrtN) + 1;
	if (posInBlocksNum2 - posInBlocksNum1 <= 1)
		for (int i = num1; i < num2; i++)
			result += (long long int) arr[i];
	else {
		for (int i = num1; i < posInBlocksNum1 * sqrtN; i++) result += (long long int) arr[i];
		for (int i = posInBlocksNum1 + 1; i < posInBlocksNum2; i++) result += blocks[i];
		for (int i = (posInBlocksNum2 - 1) * sqrtN; i < num2; i++) result += (long long int) arr[i];
	}
	return result;
}




int main() {
	int n;
	std::cin >> n;
	int sqrtN = (int)std::sqrt(n);
	if(std::sqrt(n) > (double)sqrtN) sqrtN++;
	int* arr = new int[n];
	for (int i = 0; i < n; i++) std::cin >> arr[i];
	int q;
	std::cin >> q;
	Request* requests = new Request[q];
	for (int i = 0; i < q; i++) std::cin >> requests[i].action >> requests[i].num1 >> requests[i].num2;
	long long int* blocks = new long long int[sqrtN + 1];
	for (int i = 1; i <= sqrtN; i++) blocks[i] = 0;
	for (int i = 1; i <= sqrtN; i++)
		for (int j = sqrtN * (i - 1); j < std::min(n, sqrtN * i); j++)
			blocks[i] += arr[j];
	for (int i = 0; i < q; i++) {
		if (requests[i].action == "FindSum")
			std::cout << findSum(requests[i].num1, requests[i].num2, arr, n, blocks, sqrtN) << "\n";
		else {
			arr[requests[i].num1] += requests[i].num2;
			blocks[(requests[i].num1 / sqrtN) + 1] += requests[i].num2;
		}
	}
	delete[] arr;
	delete[] blocks;
	delete[] requests;
}