#include <functional>

#include "game.h"
#include "view.h"


Game::Game()
{
    View* v = View::get();
    v->set_model(this);
    v->set_ontimer(500, std::bind(&Game::move, this));
}


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


void Game::add(Snake* s)
{
    snakes.push_back(s);
}


void Game::move()
{
    for (auto s : snakes)
    {
        s->move();
    }
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


void Snake::move()
{
    auto head = body.front();
    switch (this->dir)
    {
        case UP:
            head.second--;
            break;
        case LEFT:
            head.first--;
            break;
        case DOWN:
            head.second++;
            break;
        case RIGHT:
            head.first++;
            break;
        default:
            break;
    }
    body.push_front(head);
    body.pop_back();
}

