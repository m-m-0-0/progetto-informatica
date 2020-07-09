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

void Game::updateScore(int s) {
    score = s;
    std::string score_str = std::to_string(s);
    wmove(infoarea, 3, 1);
    wdeleteln(infoarea);
    waddstr(infoarea, "score:\t");
    waddstr(infoarea, score_str.c_str());
}

void Game::updateLevel(int l){
    level = l;
    std::string level_str = std::to_string(l);
    wmove(infoarea, 2, 1);
    wdeleteln(infoarea);
    waddstr(infoarea, "level:\t");
    waddstr(infoarea, level_str.c_str());
}

void Game::updateLife(int l){
    std::string life_str = std::to_string(l);
    wmove(infoarea, 1, 1);
    wdeleteln(infoarea);
    waddstr(infoarea, "life:\t");
    waddstr(infoarea, life_str.c_str());
}

int Game::getBaseSeed(){
    return base_seed;
}

void Game::setBaseSeed(int seed){
    base_seed = seed;
}

int Game::getLevelSeed(int level){
    return getBaseSeed() + level - 1;
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
        L[i] = obj;
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

    refreshAll();
    //showMessage("@\t+100 punti\n ▓\t-150 punti\n A\t-200 punti\n ogni 500 punti sali di\n un livello.\n ");
    showStartMessage();
    showMessage("uscire dalla strada\n ti fara' perdere\n punti, fai attenzione!\n muoviti con le frecce\n sinistra e destra.\n\n Creato da:\n Anselmo Ferrari\n Francesco Maria Vaccari\n Mauro Molari\n");

    score = 0;
    level = 1;

    //generate level
    generateLevel(level, false, true);

    refresh();
}

void Game::drawObject(WINDOW *w, Object obj) {
    Position pos = Utilities::to_ncurses_coord(playarea, obj.getPosition());
    wmove(w, pos.y, pos.x);
    waddch(w, obj.getCharacter());
}

void Game::showStartMessage(){
    nodelay(stdscr, false);
    WINDOW* messagearea = newwin(messagearea_height,
                                 messagearea_width,
                                 window_height/2 - (messagearea_height/2),
                                 window_width/2 - (messagearea_width/2));
    touchwin(messagearea);
    wrefresh(messagearea);
    wmove(messagearea, 1, 1);
    std::string message1 = "@\t+100 punti\n ";
    std::string message2 = "\t-200 punti\n A\t-150 punti\n ogni 500 punti sali di\n un livello.\n ";
    waddstr(messagearea, message1.c_str());
    waddch(messagearea, ACS_CKBOARD);
    waddstr(messagearea, message2.c_str());
    waddstr(messagearea, "\n premi invio.");
    box(messagearea, ACS_VLINE, ACS_HLINE);
    wrefresh(messagearea);
    getch();
    delwin(messagearea);
    touchwin(playarea);
    touchwin(infoarea);
    nodelay(stdscr, true);
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
#ifdef DEBUG
        if (input.isPressed(KEY_UP))
            score += 500;
        if(input.isPressed(KEY_DOWN))
            score -= 500;
#endif
        //check if player is outside of bounds and remove one points if it is
        if(player->getPosition().x < 1 || player->getPosition().x >= playarea_width - 1)
            score--;

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
                if (frame % (int)(y_speed * FPS * 2) == 0
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

                   score += curr_obj->getPoints();
                    curr_obj->setActive(false);
                }
                //draw the object
                drawObject(playarea, (curr_obj->translate(Position(0, -(int)y_scroll))));
            }
        }

        //if we're getting to the end of the generated portion of the level, generate more of it
        if (y_scroll + 100> (getYStart(level) + (getYDist(level) * OBJ_PER_LEVEL)) - getYDist(level) * 10) {
            generateLevel(level, true, false);
            y_scroll = 0;
        }

        //scroll the screen
        y_scroll += y_speed * (level / 5.0) + 0.2;

        //check what level we're on
        if(score / 500 + 1 != level) {
            level = score / 500 + 1;
            generateLevel(level);
            y_scroll = 0;
        }

        if(score > highscore)
            highscore = score;

        wclear(infoarea);
        updateLife(player->getLife());
        updateLevel(level);
        updateScore(score);
        box(infoarea, ACS_VLINE, ACS_HLINE);
        frame++;

        //sleep to mantain constant framerate;
        auto t2 = std::chrono::high_resolution_clock::now();
        delta_t = std::chrono::duration<double, std::milli>(t2 - t1).count();
        Utilities::sleep_for(sleep_ms - delta_t);
        refreshAll();
    }
    std::string highscore_str = std::to_string(highscore);;
    showMessage(" Game Over!\n High score: " + highscore_str);
    exit(0);
}