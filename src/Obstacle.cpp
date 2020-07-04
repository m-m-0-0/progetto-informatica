#include "Obstacle.h"

Obstacle::Obstacle(int x, int y, int points){
    this->points = points;
    this->pos = Position(x, y);
}

void Obstacle::setPoints(int p) {
    points = p;
}

 int Obstacle::getPoints(){
    return points;
}
