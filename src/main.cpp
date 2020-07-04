#include "Game.h"
#include "Object.h"
#include <iostream>
int main() {
    Game* g;

    g = new Game(50, 50);
    g->init();
}
