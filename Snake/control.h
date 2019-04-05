#pragma once

#include "game.h"
#include "keypressable.h"


class Control
{
public:
    Control(Snake* s);

protected:
    Snake* model;
};


class CHuman : public Control, public Keypressable
{
public:
    CHuman(Snake* s);
    void onkey(const int key);
};
