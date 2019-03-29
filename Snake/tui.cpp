#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>
#include <iostream>
#include <signal.h>

#include "tui.h"


static void win_handler(int sig)
{
    View* v = View::get();
    v->draw();
}


Tui::Tui()
{
    get_winsize();

    struct sigaction sa;
    sa.sa_handler = win_handler;
    sa.sa_flags = SA_RESTART;
    sigaction(SIGWINCH, &sa, NULL);

    struct termios at;
    tcgetattr(0, &at);    
    old_at = at;
    cfmakeraw(&at);
    tcsetattr(0, TCSAFLUSH, &at);
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
    get_winsize();
    gotoxy(col/2, 2);
    printf("Snake");
    draw_hline(2, 3, col - 2);
    draw_vline(2, 3, row - 6);
    draw_hline(2, row - 3, col - 2);
    draw_vline(col - 1, 3, row - 6);
    gotoxy(col/2, row - 2);
    printf("AlexShSh, 2019");
    fflush(stdout);
}


void Tui::run()
{
    if (!onkey_delegate)
        return;

    int key = -1;
    while ((key = getchar()))
    {
        if (key == -1 || key == 'q')
            break;

        onkey_delegate->onkey(key);
    }
}


Tui::~Tui()
{
    clear_screen();
    gotoxy(col/2, 1);
    printf("Goodbuy\n");
    tcsetattr(0, TCSAFLUSH, &old_at);
}

