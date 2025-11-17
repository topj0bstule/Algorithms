#include <iostream>
#include <fstream>

int* hashTable(int nums[], short numsSize, short c, short hashTableSize) {
	int* hashTable = new int[hashTableSize];
	short temp = 0;
	bool exist = false;
	for (size_t i = 0; i < hashTableSize; i++) hashTable[i] = -1;
	for (size_t i = 0; i < numsSize; i++) {
		for (size_t j = 0; j < numsSize; j++) {
			temp = ((nums[i] % hashTableSize) + c * j) % hashTableSize;
			if (hashTable[temp] == nums[i]) {
				exist = true;
				break;
			}
			if (hashTable[temp] == -1) break;
		}
		if (!exist) {
			for (size_t j = 0; j < numsSize; j++) {
				temp = ((nums[i] % hashTableSize) + c * j) % hashTableSize;
				if (hashTable[temp] == -1) {
					hashTable[temp] = nums[i];
					break;
				}
			}
		}
		exist = false;
	}
	return hashTable;
}

int main() {
	short m = 0, c = 0, n = 0;

	std::ifstream in("input.txt");
	if (!in.is_open()) {
		std::cerr << "Failed opening file.\n";
		return -1;
	}
	in >> m >> c >> n;
	int* nums = new int[n];
	for (size_t i = 0; i < n; i++) in >> nums[i];
	in.close();

	int* result = hashTable(nums, n, c, m);

	std::ofstream out("output.txt");
	if (!out.is_open()) {
		std::cerr << "Failed opening file.\n";
		return -1;
	}

	for (size_t i = 0; i < m; i++) out << result[i] << " ";
	out.close();

	delete[] result;

	return 0;
}