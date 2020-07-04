#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "../include/curses.h"
#include "Object.h"
#include <string>

class Game{
private:
    int level;
    int score;

    int window_width;
    int window_height;
    int playarea_width;
    int playarea_height;
    int infoarea_width;
    int infoarea_height;
    int messagearea_width = 40;
    int messagearea_height = 6;

    WINDOW* stdscr;
    WINDOW* playarea;
    WINDOW* infoarea;

    Object** ObjArray;
public:
    Game(int, int);
    void init();
    void generateLevel(int, int);
    void refreshAll();
    void drawObject(WINDOW*, Object);

    int getHeight();
    int getWidth();

    WINDOW* getDefaultWindow();

    void setScore(int);
    void setLevel(int);

    void showMessage(std::string);
};

#endif //GAME_OBJECT_H