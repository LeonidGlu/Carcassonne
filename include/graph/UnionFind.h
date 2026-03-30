#pragma once
#include <vector>
#include <iostream>
#include <iomanip>
#include <unordered_map>

class UnionFind {
public:
	UnionFind() = default;

	int addElement();
	int find(int x);
	int find(int x) const;
	void unit(int a, int b);

	bool connected(int a, int b);

	void debug(const std::string& name = "") const;
private:
	mutable std::vector<int> parent;
	mutable std::vector<int> rank;
};