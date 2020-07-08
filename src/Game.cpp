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

    messagearea_height = playarea_height - 2;
    messagearea_width = playarea_width - 2;

}

void Game::refreshAll() {
    wrefresh(playarea);
    wrefresh(infoarea);
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
    wdeleteln(infoarea);
    waddstr(infoarea, "score: ");
    waddstr(infoarea, score_str.c_str());
    box(infoarea, ACS_VLINE, ACS_HLINE);
}

void Game::setLevel(int l){
    level = l;
    std::string level_str = std::to_string(l);
    wmove(infoarea, 2, 1);
    wdeleteln(infoarea);
    waddstr(infoarea, "level: ");
    waddstr(infoarea, level_str.c_str());
    box(infoarea, ACS_VLINE, ACS_HLINE);
}

void Game::updateLife(int l){
    std::string life_str = std::to_string(l);
    wmove(infoarea, 3, 1);
    wdeleteln(infoarea);
    waddstr(infoarea, "life: ");
    waddstr(infoarea, life_str.c_str());
    box(infoarea, ACS_VLINE, ACS_HLINE);
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
    touchwin(messagearea);
    wrefresh(messagearea);
    wmove(messagearea, 1, 1);
    waddstr(messagearea, message.c_str());
    waddstr(messagearea, "\n premi invio.");
    box(messagearea, ACS_VLINE, ACS_HLINE);
    wrefresh(messagearea);
    getch();
    delwin(messagearea);
    touchwin(playarea);
    touchwin(infoarea);
    nodelay(stdscr, true);
}

void Game::generateLevel(int level, bool cont=false, bool first=false) {
    Object **L;
    int n = OBJ_PER_LEVEL;
    L = new Object *[n];
    int y_start = getYStart(level);
    int y_dist = getYDist(level);
    //if not a continuation of the current level, set the rand seed to the level seed.
    //this is done to make sure each level is generated randomly, but that each level
    //will be generated in the same way for the same execution of the game.

    if (!cont) {
        srand(getLevelSeed(level));
    }

    Object *obj;
    int rnd, x, y, points;

    int active_n = 0;
    if(!first) {
        for (int i = 0; i < n; i++) {
            if (ObjArray[i]->isActive()) {
                ObjArray[i]->setPosition(ObjArray[i]->getPosition() + Position(0, -y_scroll));
                L[active_n++] = ObjArray[i];
            }
        }
    }
    for(int i=active_n; i<n; i++){
        //generate the level randomly
        x = (rand() % (playarea_width - 2)) + 1;
        y = y_start + ((i + 1) * y_dist);

        rnd = rand() % 10;
        if (rnd <= 2) {
             points = -200;
             obj = (Object *) (new Car(x, y, points));
        } else if (rnd <= 6) {
             points = -150;
             obj = (Object *) (new Obstacle(x, y, points));
        } else {
             points = 100;
             obj = (Object *) (new Powerup(x, y, points));
        }
        obj->setActive(true);
        L[i] = (Object *) obj;
    }
    ObjArray = L;
    obj_n = n;
}

void Game::init() {
    setBaseSeed(time(0));
    ObjArray = new Object*{NULL};

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

    //initialize color pairs
    init_pair(PLAYER_PAIR, COLOR_RED, COLOR_WHITE);
    init_pair(CAR_PAIR, COLOR_BLUE, COLOR_BLACK);
    init_pair(OBSTACLE_PAIR, COLOR_WHITE, COLOR_WHITE);
    init_pair(POWERUP_PAIR, COLOR_GREEN, COLOR_BLACK);

    //initialize playarea
    playarea = newwin(playarea_height, playarea_width, 1, 1);
    box(playarea, ACS_VLINE, ACS_HLINE);

    nodelay(playarea, true);
    keypad(playarea, true);

    //initialize infoarea
    infoarea = newwin(infoarea_height, infoarea_width, playarea_height + 1, 1);
    box(infoarea, ACS_VLINE, ACS_HLINE);

    refreshAll();
    showMessage("O +100 punti\n X -150 punti\n A -200 punti\n ogni 1000 punti sali di\n un livello.\n buona fortuna!");

    setScore(0);
    setLevel(1);

    //generate level
    generateLevel(level, false, true);

    refresh();
}

void Game::drawObject(WINDOW *w, Object obj) {
    Position pos = Utilities::to_ncurses_coord(playarea, obj.getPosition());
    wmove(w, pos.y, pos.x);
    wattron(w, COLOR_PAIR(obj.getColorPair()));
    waddch(w, obj.getCharacter());
    wattroff(w, COLOR_PAIR(obj.getColorPair()));
}

[[noreturn]] void Game::start() {
    init();
    y_scroll = 0;
    player = new Player(playarea_width / 2, 2, 4);

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

        //check if player is still alive or if score < 0
        if(player->isDead() || score < 0)
            break;

        //move player based on input
        if (input.isPressed(KEY_RIGHT))
            player->move(Position(1, 0));
        if (input.isPressed(KEY_LEFT))
            player->move(Position(-1, 0));
        if (input.isPressed(KEY_ENTER))
            showMessage("pausa");

        //draw player
        drawObject(playarea, *player);

        //for each object
        for (int i = 0; i < obj_n; i++) {
            curr_obj = ObjArray[i];

            //check if active or needs to be deactivated
            if (!curr_obj->isActive())
                continue;

            if(curr_obj->getPosition().y <= y_scroll){
                curr_obj->setActive(false);
                continue;
            }

            //check that it is on screen
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

                //check player collision with the object
                if (player->translate(Position(0,y_scroll)).isColliding(*curr_obj)){
                    if(curr_obj->getType() == Object::Type::Powerup)
                        player->addLife();
                    else
                        player->removeLife();

                    setScore(score + curr_obj->getPoints());
                    curr_obj->setActive(false);
                }
                //draw the object
                drawObject(playarea, (curr_obj->translate(Position(0, -(int)y_scroll))));
            }
        }

        //if we're getting to the end of the generated portion of the level, generate more of it
        if (y_scroll > (getYStart(level) + (getYDist(level) * OBJ_PER_LEVEL)) - getYDist(level) * 10) {
            generateLevel(level, true, false);
            y_scroll = 0;
        }

        //scroll the screen
        y_scroll += y_speed * (level / 5.0) + 0.2;

        setScore(score);
        if(score / 500 + 1 != level) {
            setLevel(score / 500 + 1);
            generateLevel(level);
        }

        if(score > highscore)
            highscore = score;

        updateLife(player->getLife());

        //sleep to mantain constant framerate;
        auto t2 = std::chrono::high_resolution_clock::now();
        delta_t = std::chrono::duration<double, std::milli>(t2 - t1).count();
        Utilities::sleep_for(sleep_ms - delta_t);
        refreshAll();
    }
    std::string highscore_str = std::to_string(highscore);;
    showMessage(" Game Over!\n High score: " + highscore_str);
}