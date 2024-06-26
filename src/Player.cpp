#include "Player.h"
#include "../include/curses.h"

Player::Player(int x, int y, int life) {
    this->pos = Position(x,y);
    this->life = life;
    this->max_life = life;
    this->character = ACS_DIAMOND;
    this->color_pair = PLAYER_PAIR;
}

int Player::getLife() {
    return life;
}

void Player::setLife(int l) {
    life = l;
}

void Player::addLife() {
    if(life < max_life)
        life++;
}

void Player::removeLife() {
    if(life > 0)
        life--;
}

bool Player::isDead() {
    return life == 0;
}