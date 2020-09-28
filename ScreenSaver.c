/****************************************************************************
 *  Screen Saver app based on ncurses
 *
 * compile: gcc -lncursesw
 *
 ****************************************************************************/
#define _XOPEN_SOURCE_EXTENDED 1
#include <curses.h>
#include <signal.h>
#include <time.h>
#include <locale.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

void draw();
void OnSize();
void resizeHandler(int sig);
WINDOW* mainWin = NULL;

int main(int argc, char** argv)
{
    setlocale(LC_CTYPE, "en_US.UTF-8");
    OnSize();

    while(1){
        draw();
        wrefresh(mainWin);
        napms(1000);
    }
    endwin();
    return 0;
}

void resizeHandler(int sig)
{
    OnSize();
}

void OnSize()
{
    if(mainWin != NULL){
        delwin(mainWin);
        mainWin = NULL;
    }
    endwin();

    initscr();
    int y, x;
    getmaxyx(stdscr, y,x);
    curs_set(0);
    if(has_colors()){
        start_color();
        init_pair(1, COLOR_BLACK, COLOR_YELLOW);
        bkgd(COLOR_PAIR(1) | A_BOLD);
    }
    border(0,0,0,0,0,0,0,0);
    mainWin = subwin(stdscr, y-2, x-2, 1, 1);

    draw();
    refresh();
}

void draw()
{
    int line = 0;
    // logo
    char* logo = "Welcome to XQ Screen Saver\n";
    char* logo_2 = "Press Ctr+C to quit\n";
    mvwaddstr(mainWin, line++, (COLS-strlen(logo))/2, logo);
    mvwaddstr(mainWin, line++, (COLS-strlen(logo_2))/2, logo_2);

    // Hostname
    wchar_t msg[64];
    char buf[128];
    gethostname(buf, sizeof(buf)-1);
    swprintf(msg, sizeof(msg)/sizeof(msg[0]), L"Hostname: %s\n", buf);
    mvwaddwstr(mainWin, line++, 0, msg);

    // Current time
    time_t _now = time(NULL);
    struct tm * now = localtime(&_now);
    swprintf(msg, sizeof(msg)/sizeof(msg[0]), L"Time: %02d:%02d:%02d\n",
            now->tm_hour, now->tm_min, now->tm_sec);
    mvwaddwstr(mainWin, line++, 0, msg);

}

