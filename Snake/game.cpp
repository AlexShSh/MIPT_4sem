#include "game.h"
#include "view.h"

void Game::paint(SnakePainter p)
{
    bool f = true;
    for (const auto& s : snakes)
        for (const auto& c : s.body)
        {
            p(c, f ? s.dir : BODY);
            f = false;
        }
}


Game::Game()
{
    View* v = View::get();
    v->set_model(this);

    snakes.push_back(Snake());
}


Snake::Snake()
{
    body.push_back(Coord(10,10));
    body.push_back(Coord(11,10));
    body.push_back(Coord(12,10));
    body.push_back(Coord(13,10));
    body.push_back(Coord(14,10));
    body.push_back(Coord(15,10));
    dir = LEFT;
}
