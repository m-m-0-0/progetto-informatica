//
// Created by mm00 on 14-May-20.
//

#ifndef POSITION_OBJECT_H
#define POSITION_OBJECT_H

#endif //POSITION_OBJECT_H

class Position{
public:
    int x;
    int y;

    Position();
    Position(int, int);


    Position operator+(const Position& a);
    bool operator==(const Position& a) const;
};

#ifndef RACING_POSITION_H
#define RACING_POSITION_H

#endif //RACING_POSITION_H
