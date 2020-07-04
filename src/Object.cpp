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

Object::Type Object::getType() {
    return type;
}

void Object::setType(Type t) {
    type = t;
}

void Object::setPosition(Position p){
    pos = p;
}

Position Object::getPosition() {
    return pos;
}

char Object::getCharacter() {
    return character;
}

void Object::setCharacter(char c) {
    character = c;
}


bool Object::isColliding(Object obj) {
    return obj.getPosition() == getPosition();
}

Object Object::translate(Position pos) {
    Object* obj = new Object();
    obj->setCharacter(getCharacter());
    obj->setPosition(getPosition() + pos);
    return *obj;
}