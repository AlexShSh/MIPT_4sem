#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>
#include <iostream>
#include <signal.h>
#include <functional>
#include <poll.h>
using namespace std::placeholders; 

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

    SnakePainter  sp = std::bind(&View::snakepainter, this, _1, _2);
    RabbitPainter rp = std::bind(&View::rabbitpainter, this, _1);
    game->visit(sp, rp);

    gotoxy(0, 0);
    fflush(stdout);
}


void Tui::run()
{
    if (!onkey_delegate)
        return;

    int time_delay = 0;
    while (1)
    {
        struct timespec start_tp;
        clock_gettime(CLOCK_REALTIME, &start_tp);

        struct pollfd fds;
        fds.fd = STDIN_FILENO;
        fds.events = POLLIN;    
        int res = poll(&fds, 1, timer.first - time_delay);
        if (res > 0)
        {
            char sym;
            read(STDIN_FILENO, &sym, 1);
            if (sym == 'q')
                return;

            onkey_delegate->onkey(sym);

            struct timespec end_tp;
            clock_gettime(CLOCK_REALTIME, &end_tp);
            time_delay = (end_tp.tv_sec - start_tp.tv_sec) * 1000 + 
                         (end_tp.tv_nsec - start_tp.tv_nsec) / 1000000;
        }
        else if (res == 0)
        {
            timer.second();
            draw();
            time_delay = 0;
        }
        else
        {
            //error
        }
    }
}


void Tui::snakepainter(Coord c, Dir d)
{
    gotoxy(c.first, c.second);
    putchar("^v<>o"[d]);
}

void Tui::rabbitpainter(Coord c)
{
    gotoxy(c.first, c.second);
    putchar('@');
}


Tui::~Tui()
{
    clear_screen();
    gotoxy(col/2, 1);
    printf("Goodbuy\n\r");
    tcsetattr(0, TCSAFLUSH, &old_at);
}

