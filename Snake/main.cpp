#include "view.h"
#include "tui.h"
#include "control.h"

int main()
{
    View* v = View::get();
    Control* hum = new CHuman();
    v->draw();
    v->run();
    delete v;

    return 0;
}
