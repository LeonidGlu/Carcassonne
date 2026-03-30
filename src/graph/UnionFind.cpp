#include "graph/UnionFind.h"

int UnionFind::addElement() {
	int id = parent.size();
	parent.push_back(id);
	rank.push_back(0);
	return id;
}

int UnionFind::find(int x) {
	if (parent[x] != x) {
		parent[x] = find(parent[x]);
	}
	return parent[x];
}

int UnionFind::find(int x) const {
	if (parent[x] != x) {
		parent[x] = find(parent[x]);
	}
	return parent[x];
}

void UnionFind::unit(int a, int b) {
	int rootA = find(a);
	int rootB = find(b);

	if (rootA == rootB) return;

	if (rank[rootA] < rank[rootB]) {
		parent[rootA] = rootB;
	}
	else {
		parent[rootB] = rootA;
		if (rank[rootA] == rank[rootB]) {
			rank[rootA]++;
		}
	}
}

bool UnionFind::connected(int a, int b) {
	return find(a) == find(b);
}

void UnionFind::debug(const std::string& name) const {
    std::cout << "  UnionFind";
    if (!name.empty()) std::cout << " [" << name << "]";
    std::cout << "\n";

    if (parent.empty()) {
        std::cout << "  (empty)\n";
        return;
    }

    std::cout << "  id:     ";
    for (size_t i = 0; i < parent.size(); ++i) {
        std::cout << std::setw(3) << i;
    }
    std::cout << "\n";

    std::cout << "  parent: ";
    for (size_t i = 0; i < parent.size(); ++i) {
        std::cout << std::setw(3) << parent[i];
    }
    std::cout << "\n";

    std::cout << "  rank:   ";
    for (size_t i = 0; i < rank.size(); ++i) {
        std::cout << std::setw(3) << rank[i];
    }
    std::cout << "\n";

    std::unordered_map<int, std::vector<int>> components;
    for (size_t i = 0; i < parent.size(); ++i) {
        int root = find(static_cast<int>(i));
        components[root].push_back(static_cast<int>(i));
    }

    std::cout << "  Components:\n";
    for (auto& i : components) {
        std::cout << "    root=" << i.first << ": [";
        for (size_t j = 0; j < i.second.size(); ++j) {
            if (j > 0) std::cout << ", ";
            std::cout << i.second[j];
        }
        std::cout << "]\n";
    }
}