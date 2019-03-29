#pragma once

#include "keypressable.h"

class View
{
public:
    void virtual draw() = 0;
    void virtual run()  = 0;
    virtual ~View()     = 0; 
    void setonkey(Keypressable* k);

    static View* get();

protected:
    Keypressable* onkey_delegate;

private:
    static View* inst;
};

