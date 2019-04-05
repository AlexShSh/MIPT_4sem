#include "game.h"
#include "view.h"

void Game::visit(SnakePainter p)
{
    bool f = true;
    for (auto s : snakes)
        for (const auto& c : s->body)
        {
            p(c, f ? s->dir : BODY);
            f = false;
        }
}


Game::Game()
{
    View* v = View::get();
    v->set_model(this);
}


void Game::add(Snake* s)
{
    snakes.push_back(s);
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


Snake::Snake(const Snake& s):
    body(s.body), dir(s.dir)
{}


Snake& Snake::operator=(const Snake& s)
{
    dir = s.dir;
    body = s.body;

    return *this;
}


void Snake::set_dir(Dir d)
{
    dir = d;
}

