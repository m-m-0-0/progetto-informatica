#ifndef OBJECT_OBJECT_H
#define OBJECT_OBJECT_H

#include "Position.h"

const int PLAYER_PAIR = 0;
const int CAR_PAIR = 1;
const int OBSTACLE_PAIR = 2;
const int POWERUP_PAIR = 3;

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
    void setType(Type t);
    Position getPosition();
    void setPosition(Position pos);
    int getPoints();
    void setPoints(int p);
    unsigned long getCharacter();
    void setCharacter(unsigned long c);
    int getColorPair();
    void setColorPair(int);
    bool isActive();
    void setActive(bool);

    bool isColliding(Object);

    Object translate(Position);

protected:
    Position pos = Position(0, 0);
    int points;
    enum Type type;
    unsigned long character;
    int color_pair;
    bool active;
};

#endif

