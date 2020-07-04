#ifndef POSITION_OBJECT_H
#define POSITION_OBJECT_H


class Position{
public:
    int x;
    int y;

    Position();
    Position(int, int);


    Position operator+(const Position& a);
    bool operator==(const Position& a) const;
};

#endif //POSITION_OBJECT_H
