#pragma once
#include <string>

class Player {
public:
	Player(const std::string& name);

	void addScore(int points);

	const std::string& getName() const;
	const int getScore() const;

private:
	std::string name;
	int score = 0;
};