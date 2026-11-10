#include <ncurses.h>

int main() {

    initscr();

    printw("hello");

    refresh();

    getch();

    endwin();

    return 0;
}