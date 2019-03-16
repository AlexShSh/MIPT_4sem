#include "view.h"
#include "tui.h"

View::~View() {}


View* View::inst;


View* View::get()
{
    if (inst)
        return inst;

    return new Tui;
}
