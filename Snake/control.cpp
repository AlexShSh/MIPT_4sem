#include <iostream>

#include "control.h"
#include "view.h"


CHuman::CHuman()
{
    View* v = View::get();
    v->setonkey(this);
}


void CHuman::onkey(const int key)
{
    printf("key: %c\n", (char) key);
}   
