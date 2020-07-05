#include "Player.h"
#include "../include/curses.h"

Player::Player(int x, int y, int life) {
    this->pos = Position(x,y);
    this->life = life;
    this->character = ACS_DIAMOND;
}

int Player::getLife() {
    return life;
}

void Player::setLife(int l) {
    life = l;
}

void Player::addLife(Object o) {
    if (isColliding(o) && o.getType() == Type::Powerup)
        life++;

    else if (isColliding(o))
        life--;
}
