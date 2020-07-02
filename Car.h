#ifndef RACING_CAR_H
#define RACING_CAR_H


#include "Object.h"

class Car: Object{
public:

    /*enum Direction {
        UP,
        DOWN,
        LEFT,
        RIGHT
    };
    */
    Car();
    // Car(Object, int);
    Car(Type, int, int, int, int);
    void move(Position dir);
    void setSpeed(int);
    int getSpeed();

private:

    int speed;

};


#endif //RACING_CAR_H