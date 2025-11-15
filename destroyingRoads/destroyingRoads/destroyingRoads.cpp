#include <iostream>
#include <fstream>
#include <vector>
#include <string>

struct Road {
	int u = -1;
	int v = -1;
	bool destroy = 0;
};

struct Setik {
	int parent = -1;
	int subTreeSize = 0;
};

int findParent(int u, std::vector<Setik>& sets) {
	if (sets[u].parent == -1) return u;
	return findParent(sets[u].parent, sets);
}


bool isConnected(Road& road, std::vector<Setik>& sets, int& result) {
	if (sets.size() == 0) return 1;
	else if (sets.size() == 1) return 1;

	int parent1 = findParent(road.u, sets);
	int parent2 = findParent(road.v, sets);

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
	if (result > 1) return 1;
	return 0;
}

int main() {
	int n, m, q; //кол-во городов, дорог, землетрясений

	std::ifstream in("input.txt");
	if (!in.is_open()) {
		std::cerr << "Failed opening file.\n";
		return -1;
	}
	in >> n >> m >> q;
	std::vector<Road> roads(m);
	std::vector<Setik> sets(n);
	std::vector<int> roadsNumbersForDestroy(q);
	for (size_t i = 0; i < m; i++) {
		in >> roads[i].u;
		in >> roads[i].v;
		roads[i].u--;
		roads[i].v--;
	}
	for (size_t i = 0; i < q; i++) {
		in >> roadsNumbersForDestroy[i];
		roads[roadsNumbersForDestroy[i] - 1].destroy = 1;
	}
	in.close();

	int result = n;

	for (int i = 0; i < m; i++) {
		if (!roads[i].destroy)
			isConnected(roads[i], sets, result);
	}

	std::ofstream out("output.txt");
	if (!out.is_open()) {
		std::cerr << "Failed opening file.\n";
		return -1;
	}

	bool connected;
	std::vector<bool> answer(q);
	for (int i = q - 1; i >= 0; i--) {
		if (result == 1) {
			for (int j = i; j >= 0; j--)
				answer[j] = 1;
			break;
		}
		else answer[i] = 0;
		isConnected(roads[roadsNumbersForDestroy[i] - 1], sets, result);
	}
	for (int i = 0; i < q; i++)
		out << answer[i];

	out.close();
}