#include "Object.h"

Object::Object(Object::Type type, int x, int y, int points){
    this->type = type;
    this->pos = Position(x, y);
}
Position Object::getPosition() {
    return pos;
}