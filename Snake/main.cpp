#include "view.h"
#include "tui.h"
#include "control.h"
#include "game.h"

int main()
{
    View* v = View::get();

    auto s = new Snake();
    auto h = new CHuman(s);
    auto g = new Game();
    g->add(s);

    v->draw();
    v->run();
    delete v;

    return 0;
}
