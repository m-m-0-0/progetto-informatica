
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

protected:
    int life;
};

#endif //UNTITLED_PLAYER_H
