#include <iostream>
#include <fstream>
#include <vector>

struct Road {
	int u = -1;
	int v = -1;
};

struct Setik {
	int parent = -1;
	int subTreeSize = 0;
};

int findParent(int u, std::vector<Setik>& sets) {
	if (sets[u].parent == -1) return u;
	return findParent(sets[u].parent, sets);
}


int calcRoads(Road& road, std::vector<Setik>& sets, int& result) {
	if (sets.size() == 0) return 0;
	else if (sets.size() == 1) return 1;

	int parent1 = findParent(road.u - 1, sets);
	int parent2 = findParent(road.v - 1, sets);

	if (parent1 != parent2) {
		if (sets[parent1].subTreeSize >= sets[parent2].subTreeSize) {
			sets[parent2].parent = parent1;
			sets[parent1].subTreeSize += sets[parent2].subTreeSize + 1;
		}
		else {
			sets[parent1].parent = parent2;
			sets[parent2].subTreeSize += sets[parent1].subTreeSize + 1;
		}
		result--;
	}
	return result;
}

int main() {
	int n, q, u, v; //кол-во дорог и запросов, город 1 и город 2 соответственно

	std::ifstream in("input.txt");
	if (!in.is_open()) {
		std::cerr << "Failed opening file.\n";
		return -1;
	}
	in >> n >> q;
	std::vector<Road> roads(q);
	std::vector<Setik> sets(n);
	for (size_t i = 0; i < q; i++) {
		in >> roads[i].u;
		in >> roads[i].v;
	}
	in.close();

	std::ofstream out("output.txt");
	if (!out.is_open()) {
		std::cerr << "Failed opening file.\n";
		return -1;
	}
	int result = n;
	for (size_t i = 0; i < q; i++) out << calcRoads(roads[i], sets, result) << "\n";
	out.close();
}