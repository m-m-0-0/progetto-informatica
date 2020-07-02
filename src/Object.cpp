#include "Object.h"

Object::Object(Object::Type type, int x, int y, int points){
    this->type = type;
    this->pos = Position(x, y);
}

void Object::setPosition(Position p){
    pos = p;
}

Position* Object::getPosition() {
    return pos;
}

bool Object::isColliding(int x1, int y1){
    if (x1==x && y1==y){
        return true;
            }
            else
            return false;
}
