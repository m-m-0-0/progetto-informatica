#ifndef UNTITLED_POWERUP_H
#define UNTITLED_POWERUP_H

#include "Object.h"

class Powerup : Object {
public:
    Powerup(int x, int y, int score);

    void setPoints(int s);
    int getPoints();

};
#endif //UNTITLED_OBSTACLE_H
