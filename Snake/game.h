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


class Snake
{
public:
    Snake();
    Snake(const Snake&);

    Snake& operator=(const Snake&);
    void set_dir(Dir d);
    void move();

    std::list<Coord> body;
    Dir dir;
};


using Rabbit = Coord;


using SnakePainter = std::function<void (Coord, Dir)>;


class Game
{
public:
    Game();
    void add(Snake*);
    void visit(SnakePainter);
    void move();

private:
    std::list<Snake*>  snakes;
    std::list<Rabbit> rabbits;
};

