#ifndef TILE_H
#define TILE_H

typedef char Letter;

typedef int Score;

class Tile{
public:
    Tile(Letter letter, Score score);
    Tile(Tile &other);

    Letter getLetter();
    Score getScore();

    Letter letter;
    Score score;
};

#endif
