#include "Powerup.h"

Powerup::Powerup(int x, int y, int points){
    this->type = Type::Powerup;
    this->points = points;
    this->pos = Position(x, y);
    this->character = 'O';
    this->color_pair = POWERUP_PAIR;
}

void Powerup::setPoints(int p) {
    points = p;
}

int Powerup::getPoints(){
    return points;
}