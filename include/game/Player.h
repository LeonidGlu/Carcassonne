#pragma once
#include <string>

class Player {
public:
	Player(const std::string& name);

	void addScore(int points);

	const std::string& getName() const;
	const int getScore() const;

	bool hasMeeple() const;
	int getMeepleCount() const;
	void placeMeeple();
	void returnMeeple();

private:
	std::string name;
	int score = 0;
	int meeples = 7;
};