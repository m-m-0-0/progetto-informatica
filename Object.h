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

    Object(Type type, int x, int y, int points);

    Position getPosition();

private:
    Position pos;
    int points;
    enum Type type;
};

#endif

