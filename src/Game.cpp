#include "Game.h"
#include "Car.h"
#include "Obstacle.h"
#include "Powerup.h"
#include "utilities.h"
#include "../include/curses.h"
#include <string>
#include "stdlib.h"
#include "time.h"
#include <chrono>




const int START_Y = 1;
const int DIST_Y = 15;

const int FPS = 15;

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

void Game::generateLevel(int level, int n){
    Object** L = new Object*[n];
    Object* obj;
    int rnd, x, y, points;

    for(int i=0; i < n; i++){
        x = rand()%playarea_width;
        y = START_Y + ((i+1) * DIST_Y);
        points = level * 10;

        rnd = rand()%10;
        if (rnd <= 3)
            obj = (Object*)(new Car(x, y, -points * 2));
        else if (rnd <= 7)
            obj = (Object*)(new Obstacle(x, y, -points));
        else
            obj = (Object*)(new Powerup(x, y, points));

        L[i] = (Object*)obj;
    }

    ObjArray = L;
    obj_n = n;
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
}

void Game::drawObject(WINDOW* w, Object obj) {
    Position pos = Utilities::to_ncurses_coord(playarea, obj.getPosition());
    wmove(w, pos.y, pos.x);
    waddch(w, obj.getCharacter());
}

[[noreturn]] void Game::start(){
    init();

    Object *curr_obj;
    double sleep_ms = (double)1/FPS;
    double delta_t;
    int min_y;
    int max_y;

    //main game loop
    while(true) {
        auto t1 = std::chrono::high_resolution_clock::now();
        min_y = y_scroll;
        max_y = min_y + playarea_height;

        werase(playarea);
        box(playarea, ACS_VLINE, ACS_HLINE);
        for (int i = 0; i < obj_n; i++) {
            curr_obj = ObjArray[i];

            if (curr_obj == NULL)
                continue;

            if (curr_obj->getPosition().y >= min_y && curr_obj->getPosition().y < max_y) {
                drawObject(playarea, (curr_obj->translate(Position(0, -y_scroll))));
            }
        }
        y_scroll += 1;
        setScore(y_scroll);
        auto t2 = std::chrono::high_resolution_clock::now();
        delta_t = std::chrono::duration<double, std::milli>(t2-t1).count();
        Utilities::sleep_for(sleep_ms-delta_t);
        refreshAll();
    }
    getch();
}
