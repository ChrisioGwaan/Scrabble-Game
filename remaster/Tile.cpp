#include "Tile.h"

Tile::Tile(Letter letter, Score score) {
    this->letter = letter;
    this->score = score;
}

Tile::Tile(Tile &other) {
    this->letter = other.getLetter();
    this->score = other.getScore();
}

Letter Tile::getLetter() {
    return this->letter;
}

Score Tile::getScore() {
    return this->score;
}

