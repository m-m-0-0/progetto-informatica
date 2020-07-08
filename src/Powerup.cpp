#include "Powerup.h"

Powerup::Powerup(int x, int y, int points){
    this->type = Type::Powerup;
    this->points = points;
    this->pos = Position(x, y);
    this->character = '@';
    this->color_pair = POWERUP_PAIR;
}