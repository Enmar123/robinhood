#pragma once
#include <list>
#include <string>

#include "People.h"

struct Move {
    int x;
    int y;
    unsigned int steps;
};

class Guard :
    public People {
public:
    Guard();
    Guard(int x, int y);

    void update();

    std::string getSymbol();
private:
    std::list<Move> moves;
    std::list<Move> currentmoves;
    std::string symbol = "G";
};

