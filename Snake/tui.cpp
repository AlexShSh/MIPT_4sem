#include <sys/ioctl.h>
#include <termios.h>
#include <iostream>

#include "tui.h"


Tui::Tui()
{
    get_winsize();
}


void Tui::get_winsize()
{
    struct winsize ws;
    ioctl(1, TIOCGWINSZ, &ws);
    this->col = ws.ws_col;
    this->row = ws.ws_row;
}


void Tui::gotoxy(const int x, const int y)
{
    printf("\e[%d;%dH", y, x);
}


void Tui::draw_hline(const int x, const int y, const int size)
{
    for (int i = 0; i < size; i++)
    {
        gotoxy(x + i, y);
        printf("#");
    }
}


void Tui::draw_vline(const int x, const int y, const int size)
{
    for (int i = 0; i < size; i++)
    {
        gotoxy(x, y + i);
        printf("#");
    }
}


void Tui::clear_screen()
{
    printf("\e[H\e[J");
}


void Tui::draw()
{
    clear_screen();
    gotoxy(col/2, 2);
    printf("Snake");
    draw_hline(2, 3, col - 2);
    draw_vline(2, 3, row - 6);
    draw_hline(2, row - 3, col - 2);
    draw_vline(col - 1, 3, row - 6);
    gotoxy(col/2, row - 2);
    printf("AlexShSh, 2019\n");
}


void Tui::run()
{
    getchar();
}


Tui::~Tui()
{
    clear_screen();
    gotoxy(col/2, 1);
    printf("Goodbuy\n");
}

