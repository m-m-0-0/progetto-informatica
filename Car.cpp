#include "Car.h"

Car::Car(){

    this->speed = 0;
    this->pos = Position(0,0);
    this->type = Object::Type::Car;

}

Car::Car(Type type, int x, int y, int points, int speed) {
    this->speed = speed;
    this->type = Object::Type::Car;
    this->pos = Position(x,y);

}

void Car::move(Position dir) {
    setPosition

}
