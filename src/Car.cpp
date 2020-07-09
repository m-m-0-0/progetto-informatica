#include "Car.h"

Car::Car(){
    this->pos = Position(0,0);
    this->type = Type::Car;
    this->character = 'A';
    this->color_pair = CAR_PAIR;
}

Car::Car(int x, int y, int points) {
    this->type = Type::Car;
    this->pos = Position(x,y);
    this->points = points;
    this->character = 'A';
}

void Car::move(Position dir) {
    setPosition(getPosition() + dir);
}
