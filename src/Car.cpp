#include "Car.h"

Car::Car(){
    this->speed = 0;
    this->pos = Position(0,0);
    this->type = Type::Car;
    this->character = 'A';
}

Car::Car(int x, int y, int points) {
    this->speed = 1;
    this->type = Type::Car;
    this->pos = Position(x,y);
    this->character = 'A';
}

Car::Car(int x, int y, int points, int speed) {
    this->speed = speed;
    this->type = Type::Car;
    this->pos = Position(x,y);
    this->character = 'A';
}

void Car::move(Position dir) {
    setPosition(getPosition() + dir);
}
