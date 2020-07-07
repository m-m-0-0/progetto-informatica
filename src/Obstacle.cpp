#include "Obstacle.h"

Obstacle::Obstacle(int x, int y, int points){
    this->type = Type::Obstacle;
    this->points = points;
    this->pos = Position(x, y);
    this->character = 'X';
    this->color_pair = OBSTACLE_PAIR;
}