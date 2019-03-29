#include "view.h"
#include "tui.h"
#include "keypressable.h"


View::~View() {}


View* View::inst = nullptr;

View* View::get()
{
    if (!inst)
        inst = new Tui;

    return inst;
}


void View::setonkey(Keypressable* k)
{
    onkey_delegate = k;
}
