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
    Object(Type type, int x, int y, int points, unsigned long character);

    Type getType();
    void setType(Type);
    Position getPosition();
    void setPosition(Position);
    unsigned long getCharacter();
    void setCharacter(unsigned long);
    bool isActive();
    void setActive(bool);

    bool isColliding(Object);

    Object translate(Position);

protected:
    Position pos = Position(0, 0);
    int points;
    enum Type type;
    unsigned long character;
    bool active;
};

#endif

