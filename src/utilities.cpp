#ifndef UTILITIES_CPP
#define UTILITIES_CPP

#include <chrono>
#include <thread>
#include "Position.h"
#include "utilities.h"
#include "../include/curses.h"

typedef std::chrono::high_resolution_clock _clock;
template <typename T>
using duration = std::chrono::duration<T>;

//from https://stackoverflow.com/questions/13397571/precise-thread-sleep-needed-max-1ms-error
void Utilities::sleep_for(double dt)
{
    static constexpr duration<double> MinSleepDuration(0);
    _clock::time_point start = _clock::now();
    while (duration<double>(_clock::now() - start).count() < dt) {
        std::this_thread::sleep_for(MinSleepDuration);
    }
}

Position Utilities::to_ncurses_coord(WINDOW* w, Position pos){
    return Position(pos.x, w->_maxy - pos.y);
}

#endif