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

bool Player::hasMeeple() const {
	return meeples > 0;
}

int Player::getMeepleCount() const {
	return meeples;
}

void Player::placeMeeple() {
	if (meeples > 0) {
		meeples--;
	}
}

void Player::returnMeeple() {
	meeples++;
}