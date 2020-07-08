#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

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
    void generateLevel(int, bool);
    void refreshAll();
    void drawObject(WINDOW*, Object);

    int getHeight();
    int getWidth();

    WINDOW* getDefaultWindow();

    void setScore(int);
    void setLevel(int);
    int getBaseSeed();
    void setBaseSeed(int seed);
    int getLevelSeed(int);
    int getYStart(int);
    int getYDist(int);

    void showMessage(std::string);

    [[noreturn]] void start();

    void updateLife(int l);

    void generateLevel(int level, bool cont, bool first);
};

#endif //GAME_OBJECT_H