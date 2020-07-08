
#ifndef UNTITLED_PLAYER_H
#define UNTITLED_PLAYER_H


#include "Object.h"
#include "Car.h"

class Player : public Car {
public:
    Player(int, int, int);
    int getLife();
    void setLife(int);

    void addLife();
    void removeLife();
    bool isDead();

protected:
    int life;
    int max_life;
};

#endif //UNTITLED_PLAYER_H
