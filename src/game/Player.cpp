#include "game/Player.h"

Player::Player(const std::string& name) : name(name) {}

void Player::addScore(int points) {
	score += points;
}

const std::string& Player::getName() const {
	return name;
}

const int Player::getScore() const {
	return score;
}