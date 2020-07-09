#ifndef OBJECT_GAME_H
#define OBJECT_GAME_H

#include "../include/curses.h"
#include "Object.h"
#include "Input.h"
#include "Player.h"
#include <string>

class Game{
private:
    Player* player;
    Input input;

    int level;
    int score;
    int highscore = 0;
    long int base_seed;
    int frame = 1;

    int window_width;
    int window_height;
    int playarea_width;
    int playarea_height;
    int infoarea_width;
    int infoarea_height;
    int messagearea_width = 40;
    int messagearea_height = 8;


    WINDOW* stdscr;
    WINDOW* playarea;
    WINDOW* infoarea;

    double y_scroll = 1;
    double y_speed = 0.2;

    Object** ObjArray;
    int obj_n;

public:
    Game(int, int);
    void init();
    void generateLevel(int level, bool cont, bool first);
    void refreshAll();
    void drawObject(WINDOW* w, Object obj);

    int getBaseSeed();
    void setBaseSeed(int seed);
    int getLevelSeed(int level);
    int getYStart(int level);
    int getYDist(int level);

    void showMessage(std::string message);

    [[noreturn]] void start();

    void updateLife(int l);
    void updateLevel(int l);
    void updateScore(int s);

    void showStartMessage();
};

#endif