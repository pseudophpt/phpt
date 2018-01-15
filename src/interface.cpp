#include "interface.h"
#include "buffer.h"


/* Initialize all fuctions interfacing with ncurses */
void interface::init (void) {
    /* Initialize screen */
    initscr();
    /* Enable function keys */
    keypad(stdscr, TRUE);
    /* Disable printing to screen when typing */
    noecho();
    /* Set cursor to beginning */
    move(0, 0);
    /* Display screen */
    refresh();
    
    /* Color settings */
    start_color();
    
    init_pair (1, 7, 0); /* White on black, default */
    init_pair (2, 0, 7); /* Black on white, bottom bar */
    init_pair (3, 7, 1); /* White on red, logo */
    init_pair (4, 7, 2); /* White on cyan, line and column numbers */
}

/* Ends ncurses processes */
void interface::quit (void) {
    endwin();
}

/* Receives user input */
int interface::getchar (void) {
    wint_t ch;
    get_wch(&ch);
    return ch;
}

void interface::draw (std::vector<std::string> buffer, int cur_line, int cur_col, int top_line) {
    clear();
    for (std::string s : buffer) {
        addstr (s.c_str());
        addch ('\n');
    }
    addstr(std::to_string(cur_line).c_str());
    addch('\n');
    addstr(std::to_string(cur_col).c_str());
   
    /* Refresh screen and clear for next frame */
    refresh();
}
