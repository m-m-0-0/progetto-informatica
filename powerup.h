#ifndef UNTITLED_POWERUP_H
#define UNTITLED_POWERUP_H


class Powerup : Object {
protected:
    int score;
public:
    Powerup(int x, int y, int score){
        this->score = score;
        this->pos = Position(x, y);
    }

    int Match (int x1, int y1){
        if (x1==x && y1==y){
            return score;
        }
        else
            return 0;
    }
};


#endif //UNTITLED_POWERUP_H
