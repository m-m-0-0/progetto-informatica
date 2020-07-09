
#ifndef RACING_UTILITIES_H
#define RACING_UTILITIES_H

#include <chrono>
#include <thread>
#include "Position.h"
#include "../include/curses.h"
class Utilities {
public:
    static void sleep_for(double ms);
    static Position to_ncurses_coord(WINDOW *, Position);
};

#endif
