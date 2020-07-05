#ifndef RACING_CAR_H
#define RACING_CAR_H

#include "Object.h"

class Car: public Object{
public:
    Car();
    Car(int, int, int, int);
    Car(int, int, int);
    int getSpeed();
    void setSpeed(int);
    void move(Position dir);

protected:
    int speed;
};


#endif //RACING_CAR_H
