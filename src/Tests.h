//
// Created by mm00 on 02-Jul-20.
//

#ifndef RACING_TESTS_H
#include "Game.h"
#define RACING_TESTS_H

class Tests{
private:
    bool is_init;
    Game* g;

public:
    void initTest();
    void infoTest();
    void objectTest();
    void messageTest();

};

#endif //RACING_TESTS_H
