#pragma once

#include "view.h"

class Tui : public View
{
public:
    Tui();
    void draw();
    void run();
    ~Tui();

private:
    int col;
    int row;

    void get_winsize();
    void gotoxy(int x, int y);
    void draw_hline(int x, int y, int size);
    void draw_vline(int x, int y, int size);
    void clear_screen();
};
