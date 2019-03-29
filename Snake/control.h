#pragma once

#include "keypressable.h"


class Control
{
};


class CHuman : public Control, public Keypressable
{
public:
    CHuman();
    void onkey(const int key);
};
