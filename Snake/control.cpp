#include <iostream>

#include "control.h"
#include "view.h"


CHuman::CHuman()
{
    View* v = View::get();
    v->set_onkey(this);
}


void CHuman::onkey(const int key)
{
    printf("key: %c", (char) key);
}   
