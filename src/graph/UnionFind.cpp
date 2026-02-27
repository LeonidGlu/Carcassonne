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