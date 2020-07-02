#include "Position.h"

Position::Position(int x, int y) {
    this->x = x;
    this->y = y;
}

Position Position::operator+(const Position& a){
    return Position(a.x+x, a.y+y);
}
