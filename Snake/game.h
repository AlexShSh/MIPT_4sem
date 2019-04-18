#pragma once

#include <list>
#include <utility>
#include <functional>


using Coord = std::pair<int, int>;

enum Dir
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    BODY
};


using Rabbit = Coord;


class Snake
{
public:
    Snake();
    Snake(const Snake&);

    Snake& operator=(const Snake&);
    void set_dir(Dir d);
    void move(std::list<Rabbit*>& rabbits);
    Dir get_dir();
    std::list<Coord>& get_body();

private:
    std::list<Coord> body;
    Dir dir;
};


using SnakePainter  = std::function<void (Coord, Dir)>;
using RabbitPainter = std::function<void(Coord)>;


class Game
{
public:
    Game();
    void add(Snake* s);
    void add(Rabbit* r);
    void visit(SnakePainter sp, RabbitPainter rp);
    void move();

private:
    std::list<Snake*>  snakes;
    std::list<Rabbit*> rabbits;
};

