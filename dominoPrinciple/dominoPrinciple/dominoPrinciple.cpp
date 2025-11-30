#include <iostream>
#include <fstream>
#include <queue>

struct Domino {
	short cardinality = 0;
	bool visited = false;
	std::vector<short> dominoForDestroy;
};

struct Result {
	short time;
	short index;

	Result() {
		this->time = -1;
		this->index = -1;
	}
};

Result destroy(short n, Domino arr[]) {
	Result result;
	Result tempResult;
	Domino temp;
	bool rewrite;
	short dominosQuantity;
	std::queue<short> dominos;

	for (size_t i = 0; i < n; i++) {
		tempResult.index = i;
		tempResult.time = 0;
		while (!dominos.empty()) dominos.pop();
		for (short j = 0; j < n; j++) {
			arr[j].visited = false;
		}
		rewrite = true;

		arr[i].visited = true;
		dominos.push(i);
		while (!dominos.empty()) {
			dominosQuantity = dominos.size();
			for (size_t z = 0; z < dominosQuantity; z++) {
				temp = arr[dominos.front()];
				dominos.pop();
				for (size_t j = 0; j < temp.cardinality; j++) 
					if (!arr[temp.dominoForDestroy[j]].visited) {
						arr[temp.dominoForDestroy[j]].visited = true;
						dominos.push(temp.dominoForDestroy[j]);
					}
			}
			if(!dominos.empty()) tempResult.time++;
		}

		for (size_t j = 0; j < n; j++) if (!arr[j].visited) rewrite = false;
		if (tempResult.time >= result.time && rewrite) {
			result.index = tempResult.index;
			result.time = tempResult.time;
		}
	}
	return result;
}

int main(){
	short n;
	short temp;
	std::ifstream in("in.txt");
	if (!in.is_open()) {
		std::cerr << "Failed opening file.\n";
		return -1;
	}
	in >> n;
	Domino* dominos = new Domino[n];
	for (size_t i = 0; i < n; i++) {
		in >> dominos[i].cardinality;
		for (size_t j = 0; j < dominos[i].cardinality; j++) {
			in >> temp;
			dominos[i].dominoForDestroy.push_back(--temp);
		}
	}
	in.close();

	Result result = destroy(n, dominos);

	std::ofstream out("out.txt");
	if (!out.is_open()) {
		std::cerr << "Failed opening file.\n";
		return -1;
	}
	if (result.index == -1) out << "impossible\n";
	else out << result.time << "\n" << result.index + 1 << "\n";
	out.close();
}