#ifndef RACING_INPUT_H
#define RACING_INPUT_H

#include "../include/curses.h"

class Input {
public:
    int* getInput();
    bool isPressed(int);
    void clearInputBuffer();

private:
    int* Keys;
    int keys_n;
};


#endif //RACING_INPUT_H
