#include "view.h"
#include "tui.h"

int main()
{
    View* v = View::get();
    v->draw();
    v->run();
    delete v;

    return 0;
}
