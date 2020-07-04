#include "Game.h"
#include "Car.h"
#include "Obstacle.h"
#include "Powerup.h"
#include "../include/curses.h"
#include <string>
#include "stdlib.h"
#include "time.h"

const int START_Y = 1;
const int DIST_Y = 10;

Game::Game(int w_y, int w_x){
    window_height = w_y;
    window_width = w_x;

    playarea_height = window_height-6;
    playarea_width = window_width-2;

    infoarea_height = 5;
    infoarea_width = window_width-2;
}

void Game::refreshAll() {
    wrefresh(playarea);
    wrefresh(infoarea);
    refresh();
}

int Game::getHeight() {
    return playarea_height;
}

int Game::getWidth() {
    return playarea_width;
}

WINDOW* Game::getDefaultWindow(){
    return stdscr;
}

void Game::setScore(int s) {
    score = s;
    std::string score_str = std::to_string(s);
    wmove(infoarea, 1, 1);
    waddstr(infoarea, "score: ");
    waddstr(infoarea, score_str.c_str());
}

void Game::setLevel(int l){
    level = l;
    std::string level_str = std::to_string(l);
    wmove(infoarea, 3, 1);
    waddstr(infoarea, "level: ");
    waddstr(infoarea, level_str.c_str());
}

void Game::showMessage(std::string message){
    WINDOW* messagearea = newwin(messagearea_height,
                                 messagearea_width,
                                 window_height/2 - (messagearea_height/2),
                                 window_width/2 - (messagearea_width/2));

    box(messagearea, ACS_VLINE, ACS_HLINE);
    wmove(messagearea, 1, 1);
    waddstr(messagearea, message.c_str());
    wmove(messagearea, messagearea_height-1, (messagearea_width - message.length()) / 3);
    waddstr(messagearea, "press any button to continue.");
    wrefresh(messagearea);
    refreshAll();
    getch();
    delwin(messagearea);
    touchwin(playarea);
    touchwin(infoarea);
    refreshAll();
}

void Game::generateLevel(int level, int obj_n){
    Object** L = new Object*[obj_n];
    Object* obj;
    int rnd, x, y, points;

    for(int i=0; i < obj_n; i++){
        x = rand()%playarea_width;
        y = START_Y + (i * DIST_Y);
        points = level * 10;

        rnd = rand()%10;
        if (rnd <= 3)
            obj = (Object*)(new Car(x, y, points));
        else if (rnd <= 7)
            obj = (Object*)(new Obstacle(x, y, points));
        else
            obj = (Object*)(new Powerup(x, y, points));

        L[i] = (Object*)obj;
    }

    ObjArray = L;
}

void Game::init(){
    srand(time(0));

    //initialize window
    stdscr = initscr();
    resize_window(stdscr, window_height, window_width);
    resize_term(window_height, window_width);

    //initialize playarea
    playarea = newwin(playarea_height, playarea_width, 1, 1);
    box(playarea, ACS_VLINE, ACS_HLINE);

    //initialize infoarea
    infoarea = newwin(infoarea_height, infoarea_width, playarea_height+1, 1);
    box(infoarea, ACS_VLINE, ACS_HLINE);
    setScore(0);
    setLevel(0);

    refreshAll();
    showMessage("game initialized.");

    //generate level
    generateLevel(1, 100);

    refresh();
    getch();
    endwin();
}

void Game::drawObject(WINDOW* w, Object obj) {
    wmove(w, obj.getPosition().x, obj.getPosition().y);
    waddch(w, obj.getCharacter());
}
