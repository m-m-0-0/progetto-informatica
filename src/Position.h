#ifndef OBJECT_POSITION_H
#define OBJECT_POSITION_H

class Position{
public:
    Position();
    Position(int, int);

    Position operator+(const Position& a);
    bool operator==(const Position& a) const;


private:
    int x;
    int y;
};
#endif
