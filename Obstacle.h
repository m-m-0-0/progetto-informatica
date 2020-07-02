#ifndef UNTITLED_OBSTACLE_H
#define UNTITLED_OBSTACLE_H


class Obstacle : Object {
        protected:
        int score;
        public:
        Obstacle(int x, int y, int score){
            this->score = score;
            this->pos = Position(x, y);
        }

        int Match (int x1, int y1){
            if (x1==x && y1==y){
                return (-1) *score;
            }
            else
                return 0;
        }
    };
};


#endif //UNTITLED_OBSTACLE_H
