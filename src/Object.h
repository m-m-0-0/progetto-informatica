#ifndef OBJECT_OBJECT_H
#define OBJECT_OBJECT_H
#include "Position.h"

class Object{
public:
    enum class Type{
        Car,
        Obstacle,
        Powerup
    };
    Object();
    Object(Type type, int x, int y, int points, char character);

    Position getPosition();
    void setPosition(Position);
    bool isColliding(Object);

protected:
    Position pos = Position(0, 0);
    int points;
    enum Type type;
    char character;
};

#endif

