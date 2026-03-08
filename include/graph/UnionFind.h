#pragma once
#include <vector>

class UnionFind {
public:
	UnionFind() = default;

	int addElement();
	int find(int x);
	int find(int x) const;
	void unit(int a, int b);

	bool connected(int a, int b);
private:
	mutable std::vector<int> parent;
	mutable std::vector<int> rank;
};