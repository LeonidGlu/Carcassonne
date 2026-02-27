#pragma once
#include <vector>

class UnionFind {
public:
	UnionFind() = default;

	int addElement();
	int find(int x);
	void unit(int a, int b);

	bool connected(int a, int b);
private:
	std::vector<int> parent;
	std::vector<int> rank;
};