
#include "Tile.h"

Tile::Tile(Letter letter, Value value) {
    this->letter = letter;
    this->value = value;
}

Tile::Tile(Tile &other) {
    this->letter= other.getLetter();
    this->value = other.getValue();
}

Letter Tile::getLetter() {
    return this->letter;
}

Value Tile::getValue() {
    return this->value;
}