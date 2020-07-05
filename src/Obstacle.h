#ifndef UNTITLED_OBSTACLE_H
#define UNTITLED_OBSTACLE_H

#include "Object.h"

class Obstacle : public Object {
public:
    Obstacle(int x, int y, int score);

    void setPoints(int s);
    int getPoints();

};


#endif //UNTITLED_OBSTACLE_H
