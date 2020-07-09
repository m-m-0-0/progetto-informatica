#ifndef OBJECT_PLAYER_H
#define OBJECT_PLAYER_H


#include "Object.h"
#include "Car.h"

class Player : public Car {
public:
    Player(int x, int y, int life);
    int getLife();
    void setLife(int l);

    void addLife();
    void removeLife();
    bool isDead();

private:
    int life;
    int max_life;
};

#endif
