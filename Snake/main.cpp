#include "view.h"
#include "tui.h"
#include "control.h"
#include "game.h"

int main()
{
    View* v = View::get();
    Control* hum = new CHuman();
    Game* game = new Game();
    v->draw();
    v->run();
    delete v;

    return 0;
}
