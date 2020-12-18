#pragma once
#include "People.h"
#include <list>
#include <string>

class Guard :
    public People {
public:
    Guard();
    Guard(int x, int y);

    void update();

    std::string getSymbol();
protected:
    std::list<Move> moves;
    std::list<Move> currentmoves;
    std::string symbol = "G";
};

