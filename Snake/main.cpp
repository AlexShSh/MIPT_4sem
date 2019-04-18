#include "view.h"
#include "tui.h"
#include "control.h"
#include "game.h"

int main()
{
    View* v = View::get();

    Snake s;
    Game g;
    CHuman h(&s, &g);
    Rabbit r1(20, 20), r2(20, 30);
    g.add(&s);
    g.add(&r1);
    g.add(&r2);

    v->draw();
    v->run();
    delete v;

    return 0;
}
