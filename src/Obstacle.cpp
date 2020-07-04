#include "Obstacle.h"

Obstacle::Obstacle(int x, int y, int points){
    this->type = Type::Obstacle;
    this->points = points;
    this->pos = Position(x, y);
    this->character = 'X';
}

void Obstacle::setPoints(int p) {
    points = p;
}

int Obstacle::getPoints(){
    return points;
}
