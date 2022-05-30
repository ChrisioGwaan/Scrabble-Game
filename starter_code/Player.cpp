#include "Player.h"

Player::Player(std::string player_name) {
    this->player_name = player_name;
    this->countPass = 0;
    this->player_score = 0;
    this->player_hand = new LinkedList();
}

Player::Player(Player &other) {
    this->player_name = other.getName();
    this->player_score = other.getScores();
}

Player::~Player() {
    delete this->player_hand;
}

std::string Player::getName() {
    return this->player_name;
}

int Player::getScores() {
    return this->player_score;
}

void Player::sumUpScores(int point) {
    this->player_score += point;
}

void Player::setScores(int score) {
    this->player_score = score;
}