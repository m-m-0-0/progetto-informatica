#include "Game.h"
#include "Car.h"
#include "Obstacle.h"
#include "Powerup.h"
#include "utilities.h"
#include "../include/curses.h"
#include <string>
#include "stdlib.h"
#include "time.h"
#include "Player.h"
#include <chrono>




const int Y_START = 1;
const int Y_DIST = 10;
const int OBJ_PER_LEVEL = 100;
const int FPS = 30;

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

int Game::getBaseSeed(){
    return base_seed;
}

void Game::setBaseSeed(int seed){
    base_seed = seed;
}

int Game::getLevelSeed(int level){
    return base_seed + level - 1;
}

int Game::getYStart(int level) {
    return Y_START;
}

int Game::getYDist(int level){
    return Y_DIST - ((float)level/2);
}

void Game::showMessage(std::string message){
    nodelay(stdscr, false);
    WINDOW* messagearea = newwin(messagearea_height,
                                 messagearea_width,
                                 window_height/2 - (messagearea_height/2),
                                 window_width/2 - (messagearea_width/2));

    box(messagearea, ACS_VLINE, ACS_HLINE);
    wmove(messagearea, 1, 1);
    waddstr(messagearea, message.c_str());
    wmove(messagearea,0,0);
    wmove(messagearea, messagearea_height-1, (messagearea_width - message.length()) / 3);
    box(messagearea, ACS_VLINE, ACS_HLINE);
    waddstr(messagearea, "press any button to continue.");
    wrefresh(messagearea);
    refreshAll();
    getch();
    delwin(messagearea);
    touchwin(playarea);
    touchwin(infoarea);
    nodelay(stdscr, true);
    refreshAll();
}

void Game::generateLevel(int level, int y_start, int y_dist, bool cont=false) {
    Object **L;
    int n = OBJ_PER_LEVEL;
    L = new Object *[n];

    //if not a continuation of the current level, set the rand seed to the level seed.
    //this is done to make sure each level is generated randomly, but that each level
    //will be generated in the same way for the same execution of the game.

    if (!cont) {
        srand(getLevelSeed(level));
    }

    Object *obj;
    int rnd, x, y, points;

    int active_n = 0;
     for(int i=0; i<n; i++) {
         if (cont && ObjArray[i]->isActive()) {
             ObjArray[i]->setPosition(ObjArray[i]->getPosition() + Position(0, -y_scroll));
             L[active_n++] = ObjArray[i];
         }
     }
     for(int i=active_n; i<n; i++){
         //generate the level randomly
         x = rand() % playarea_width;
         y = y_start + ((i + 1) * y_dist);
         points = level * 10;

         rnd = rand() % 10;
         if (rnd <= 3)
             obj = (Object * )(new Car(x, y, -points * 2));
         else if (rnd <= 7)
             obj = (Object * )(new Obstacle(x, y, -points));
         else
             obj = (Object * )(new Powerup(x, y, points));

         obj->setActive(true);
         L[i] = (Object *) obj;
     }
    ObjArray = L;
    obj_n = n;
}

void Game::init() {
    setBaseSeed(time(0));
    level = 15;
    score = 0;

    //initialize window
    stdscr = initscr();
    resize_window(stdscr, window_height, window_width);
    resize_term(window_height, window_width);

    //set options
    raw();
    nodelay(stdscr, true);
    keypad(stdscr, true);
    start_color();
    curs_set(0);
    noecho();

    //initialize playarea
    playarea = newwin(playarea_height, playarea_width, 1, 1);
    box(playarea, ACS_VLINE, ACS_HLINE);

    nodelay(playarea, true);
    keypad(playarea, true);

    //initialize infoarea
    infoarea = newwin(infoarea_height, infoarea_width, playarea_height + 1, 1);
    box(infoarea, ACS_VLINE, ACS_HLINE);
    setScore(score);
    setLevel(level);

    refreshAll();
    showMessage("X = ostacoli\n O = powerup\n A = automobili\n raggiungi il punteggio prestabilito\n per salire di livello!");

    //generate level
    generateLevel(level, getYStart(level), getYDist(level));

    refresh();
}

void Game::drawObject(WINDOW *w, Object obj) {
    Position pos = Utilities::to_ncurses_coord(playarea, obj.getPosition());
    wmove(w, pos.y, pos.x);
    waddch(w, obj.getCharacter());
}

[[noreturn]] void Game::start() {
    init();
    y_scroll = 0;
    player = new Player(playarea_width / 2, 2, 10);

    Object *curr_obj;
    double sleep_ms = (double) 1 / FPS;
    double delta_t;
    int min_y;
    int max_y;

    //main game loop
    while (true) {
        auto t1 = std::chrono::high_resolution_clock::now();
        min_y = (int) y_scroll;
        max_y = min_y + playarea_height;
        input.getInput();

        werase(playarea);
        box(playarea, ACS_VLINE, ACS_HLINE);

        if (input.isPressed(KEY_RIGHT))
            player->move(Position(1, 0));
        if (input.isPressed(KEY_LEFT))
            player->move(Position(-1, 0));

        drawObject(playarea, *player);

        for (int i = 0; i < obj_n; i++) {
            curr_obj = ObjArray[i];

            if (!curr_obj->isActive())
                continue;

            if(curr_obj->getPosition().y <= y_scroll){
                curr_obj->setActive(false);
                continue;
            }

            if (curr_obj->getPosition().y > min_y && curr_obj->getPosition().y < max_y) {
                if ((y_scroll - (int) y_scroll <= 1e-3) && (int) y_scroll % 2 == 0
                    && curr_obj->getType() == Object::Type::Car) { //move the cars forward and randomly left or right
                    Car *c = (Car *) curr_obj;
                    int dir = rand() % 2;

                    if (dir && c->getPosition().x != playarea_width - 1)
                        c->move(Position(1, 1));
                    else if (!dir && c->getPosition().x != 1)
                        c->move(Position(-1, 1));

                }
                drawObject(playarea, (curr_obj->translate(Position(0, -(int)y_scroll))));
            }
        }

        if (y_scroll > (getYStart(level) + (getYDist(level) * OBJ_PER_LEVEL)) - getYDist(level) * 10) {
            generateLevel(level, getYStart(level), getYDist(level), true);
            y_scroll = 0;
        }

        y_scroll += y_speed * (level / 5.0) + 0.2;
        setScore((int) y_scroll);
        auto t2 = std::chrono::high_resolution_clock::now();
        delta_t = std::chrono::duration<double, std::milli>(t2 - t1).count();
        Utilities::sleep_for(sleep_ms - delta_t);
        refreshAll();
    }
    getch();
}