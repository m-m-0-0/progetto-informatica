#ifndef RACING_INPUT_H
#define RACING_INPUT_H

#include "../include/curses.h"

class Input {
public:
    void getInput();
    bool isPressed(int key);
    void clearInputBuffer();

private:
    int* Keys;
    int keys_n;
};


#endif
