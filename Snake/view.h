#pragma once

#include "game.h"
#include "keypressable.h"

class View
{
public:
    virtual void draw() = 0;
    virtual void run() = 0;
    virtual void snakepainter(Coord c, Dir d) = 0;
    virtual ~View() = 0; 

    void set_onkey(Keypressable* k);
    void set_model(Game* g);

    static View* get();

protected:
    Keypressable* onkey_delegate;
    Game*         game;

private:
    static View* inst;
};

