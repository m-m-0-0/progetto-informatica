#ifndef OBJECT_CAR_H
#define OBJECT_CAR_H

#include "Object.h"

class Car: public Object{
public:
    Car();
    Car(int, int, int);
    void move(Position dir);
};

#endif
