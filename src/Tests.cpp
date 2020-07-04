#include "Tests.h"
#include "Game.h"

void Tests::initTest(){
    g = new Game(50, 50);
    g->init();
}

void Tests::messageTest(){

}

void Tests::infoTest() {
    if(!is_init){
        wmove(g->getDefaultWindow(), 0, 0);
        waddstr(g->getDefaultWindow(), "initialize the game first.");
    }

    g->setScore(0);
    g->setLevel(1);

    g->showMessage("score set to 0, level set to 1");



}