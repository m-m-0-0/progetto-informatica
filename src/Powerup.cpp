#include "Powerup.h"

Powerup::Powerup(int x, int y, int points){
    this->points = points;
    this->pos = Position(x, y);
}

void Powerup::setPoints(int p) {
    points = p;
}

int Powerup::getPoints(){
    return points;
}
