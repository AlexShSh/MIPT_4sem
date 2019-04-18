#include <functional>
#include <iostream>
#include <ctime>

#include "game.h"
#include "view.h"


Game::Game()
{
    View* v = View::get();
    v->set_model(this);
    v->set_ontimer(350, std::bind(&Game::update, this));

    srand(time(0));
    spawn_rabbit();
    spawn_rabbit();
}


void Game::visit(SnakePainter sp, RabbitPainter rp)
{
    bool f = true;
    for (auto s : snakes)
    {
        auto body = s->get_body();
        Dir dir = s->get_dir();
        for (const auto& c : body)
        {
            sp(c, f ? dir : BODY);
            f = false;
        }
    }
    for (auto r : rabbits)
    {
        rp(*r);
    }
}


void Game::add(Snake* s)
{
    snakes.push_back(s);
}


void Game::add(Rabbit* r)
{
    rabbits.push_back(r);
}


void Game::move()
{
    for (auto s : snakes)
    {
        s->move(rabbits);
    }
}


void Game::spawn_rabbit()
{
    int x = 5 + rand() % 100;
    int y = 5 + rand() % 30;
    Rabbit* r = new Rabbit(x, y);
    rabbits.push_back(r);  
}


void Game::update()
{
    move();
    if (rabbits.size() < 1 || (rabbits.size() <= RABBITS_MAX && rand() % 10 == 1))
        spawn_rabbit();
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


Dir Snake::get_dir()
{
    return dir;
}


std::list<Coord>& Snake::get_body()
{
    return body;
}


void Snake::move(std::list<Rabbit*>& rabbits)
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

    bool onrab = false;
    for (auto r = rabbits.begin(); r != rabbits.end(); r++)
        if (head == **r)
        {
            rabbits.erase(r);
            onrab = true;
            break;
        }

    if (!onrab)
        body.pop_back();
}

