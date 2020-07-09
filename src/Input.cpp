#include "Input.h"

void Input::getInput(){
    int* Tmp = new int[100]{-1};
    int c;
    int i=0;
    for(;;i++){
        c = getch();
        if(c == ERR)
            break;
        Tmp[i] = c;
    }

    keys_n = i+1;
    Keys = new int(keys_n);
    for(int i=0; i<keys_n; i++)
        Keys[i] = Tmp[i];
}

bool Input::isPressed(int key) {
    for(int i=0; i<keys_n; i++){
        if(Keys[i] == key)
            return true;
    }
    return false;
}

void Input::clearInputBuffer(){
    while(getch() != ERR);
}