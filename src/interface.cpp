#include "interface.h"
#include "buffer.h"
#include "handle.h"

int interface::cur_line;
int interface::cur_col;
int interface::top_line;

void interface::init (void) {
    /* Screen initialization */
    
    initscr(); /* Init screen */
    keypad(stdscr, TRUE);
    noecho(); /* No printing to screen when someone types */
    move(0, 0);
    refresh(); /* Refresh screen */
    
    /* Set up colors */
    
    start_color();
    init_pair (1, 7, 0); /* White on black, default */
    init_pair (2, 0, 7); /* Black on white, bottom bar */
    init_pair (3, 7, 1); /* White on red, logo */

    attron(COLOR_PAIR(1));
    
    /* Initialize variables */
    
    cur_line = 0;
    cur_col = 0;
    top_line = 0;
}

void interface::quit (void) {
    endwin();
}

/* Get character method, calls ncurses */
int interface::getchar (void) {
    return getch();
}

/* Move cursor position */
void interface::move_x (int delta_x) {
    cur_col += delta_x;
    
    /* Error correcting */
    {
        buffer b;
        
        /* If before start, set to start */
        if (cur_col < 0)
            cur_col = 0;
        
        /* It can't be both, so we use an else if to test if it's after the end */
        else if (cur_col >= b.text_buffer[cur_line].size())
            cur_col = b.text_buffer[cur_line].size();
    }   
}

void interface::move_y (int delta_y) {
    cur_line += delta_y;
    
    buffer b;
    
    if (cur_line < 0) 
        cur_line = 0;

    else if (cur_line >= b.text_buffer.size())
        cur_line = b.text_buffer.size() - 1;

    if (cur_col > b.text_buffer[cur_line].size())
        cur_col = b.text_buffer[cur_line].size();
}

/* Scroll screen */
void interface::scr (int amount) {
    top_line += amount;
    
    /* Error correcting */
    if (top_line < 0)
        top_line = 0;
}

void interface::draw (void) {
    clear ();
    
    {
        buffer b;
        handle h;
        
        int maxy = getmaxy(stdscr);
        
        /* Print all characters in the buffer until we go off screen */
        for (int i = top_line; (i < b.text_buffer.size()) && (getcury(stdscr) < (maxy - 2)); i ++) {
            std::string line_no = "     ";
            std::string no = std::to_string(i);
            line_no.replace(4 - no.size(), no.size(), no);
            
            std::string line = b.text_buffer[i];
            
            bool is_cur_line = (i == cur_line);
            
            if (is_cur_line)
                attron(COLOR_PAIR(2));
            attron(A_BOLD);
            addstr (line_no.c_str());
            attroff(A_BOLD);
            if (is_cur_line)
                attron(COLOR_PAIR(1));
            addch(' ');
            
            
            if (is_cur_line) {
                /* Last character */
                line.append(" ");
                /* C version */
                const char *str_line = line.c_str();
                /* If the current column is 0, it should be selected */
                if (cur_col == 0)
                    attron(COLOR_PAIR(2));
                /* For each character, add it, and if it's the current characer set the attribute */
                for (int i = 0; i < line.size(); i ++) {
                    if (i == cur_col)
                        attron(COLOR_PAIR(2));
                    
                    addch(str_line[i]);
                    attron(COLOR_PAIR(1));
                }
            }
            else {
                const char *str_line = line.c_str();
                addstr (str_line); 
            }
            addch ('\n');
        }
        
        /* Set cursor to bottom */
        move (getmaxy(stdscr) - 1, 0);
        
        /* Logo */
        attron(COLOR_PAIR(3));
        
        std::string name = "phpt-2.20";
        
        addch(' ');
        
        addstr(name.c_str());
        
        addch (' ');
        
        /* Mode */
        attron(A_BOLD);
        addstr(h.get_name().c_str());
        attroff(A_BOLD);
        
        addch(' ');
        
        /* Black on white */
        attron(COLOR_PAIR(2));
        
        addch(' ');
        
        /* Line and column numbers */
        addch('L');
        addstr(std::to_string(cur_line + 1).c_str());
        
        addch(' ');
        
        addch('C');
        addstr(std::to_string(cur_col + 1).c_str());
        
        /* Fill rest of space */
        for (int i = getcurx(stdscr); i < getmaxx(stdscr); i ++) {
            addch(' ');
        }   
        
        /* Back to normal */
        attron(COLOR_PAIR(1));
    }
    refresh ();
}
