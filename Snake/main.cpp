#include "view.h"
#include "tui.h"
#include "control.h"
#include "game.h"

int main()
{
    View* v = View::get();

    auto s = new Snake();
    auto g = new Game();
    auto h = new CHuman(s, g);
    g->add(s);

    v->draw();
    v->run();
    delete v;

    return 0;
}
