#include "Position.h"

Position::Position(){
    this->x = 0;
    this->y = 0;
}

Position::Position(int x, int y) {
    this->x = x;
    this->y = y;
}

Position Position::operator+(const Position& a){
    return Position(a.x+x, a.y+y);
}

bool Position::operator==(const Position& a) const{
    return a.x == x && a.y == y;
}
