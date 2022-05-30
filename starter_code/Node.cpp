
#include "Node.h"

Node::Node(Tile* tile, Node* next) :
            tile(tile), next(next)
{}

Node::Node(Node& other)
{
   this->tile = new Tile(*(other.tile));
}

Node::~Node() {
   delete this->tile;
}
