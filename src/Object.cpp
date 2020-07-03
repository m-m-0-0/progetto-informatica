#include "Object.h"

Object::Object(){
    this->pos = Position(0,0);
    this->points = 0;
    this->character = ' ';
}

Object::Object(Object::Type type, int x, int y, int points, char character){
    this->type = type;
    this->pos = Position(x, y);
    this->points = points;
    this->character = character;
}

void Object::setPosition(Position p){
    pos = p;
}

Position Object::getPosition() {
    return pos;
}

bool Object::isColliding(Object obj) {
    return obj.getPosition() == getPosition();
}
