#include <ncurses.h>
#include <vector>
#include <string>
#include "interface.h"
#include "buffer.h"

int interface::pos_x;
int interface::pos_y;

void interface::init (void) {
    /* Screen initialization */
    
    initscr(); /* Init screen */
    keypad(stdscr, TRUE);
    noecho(); /* No printing to screen when someone types */
    move(0, 0);
    draw(); /* Refresh screen */
    
    /* Initialize variables */
    
    pos_x = 0;
    pos_y = 0;
}

void interface::quit (void) {
    endwin();
}

/* Get character method, calls ncurses */
int interface::getchar (void) {
    return getch();
}

void interface::move_x (int delta_x) {
    pos_x += delta_x;
}

void interface::move_y (int delta_y) {
    pos_y += delta_y;
}

void interface::draw (void) {
    {
        buffer b;
        for (std::string s : b.text_buffer) {
            for (char c : s) {
                addch(c);
            }
            addch('\n');
        }
    }

    refresh();
}
