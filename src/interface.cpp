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

/* Gives formatted string of the current line number */
std::string interface::format_line_number (int line) {
    /* Formatted string output */
    std::string formatted = "";
    
    /* Current line string */
    std::string line_number = std::to_string (line);
    
    /* Padding */
    for (int j = 0; j < (5 - line_number.size()); j ++)
        formatted.push_back(' ');
    
    /* Add line number itself */
    formatted.append(line_number);
    
    /* Final padding */
    formatted.push_back(' ');
    
    return formatted;
}

/* Draw a single line */
void interface::draw_line (std::string line, int line_no, int cur_line, int cur_col) {
    /* If it's the current line, get ready to highlight */
    if (line_no == cur_line) {
        /* Add line number */
        attron(COLOR_PAIR(2));
        addstr(format_line_number(line_no).c_str());
        attron(COLOR_PAIR(1));
        
        addch(' ');
        
        /* Add filler character if it's the selected line */
        line.push_back(' ');
        
        /* For each character in line, add it. If it's selected, set the attribute */
        for (int j = 0; j < line.size(); j ++) {
            attron(COLOR_PAIR(1));
            if (j == cur_col)
                attron(COLOR_PAIR(2));
            addch(line[j]);
        }
    }
    
    /* Just a normal line */
    else {
        /* Add line number */
        addstr(format_line_number(line_no).c_str());
        
        addch(' ');
        
        /* Add current line */
        addstr (line.c_str());
    }
    attron(COLOR_PAIR(1));
}

/* Draw whole interface */
void interface::draw (std::vector<std::string> buffer, int cur_line, int cur_col, int top_line) {
    clear();
    attron(COLOR_PAIR(0));
    
    /* Draw lines */
    for (int i = top_line; i < buffer.size(); i ++) {
        draw_line(buffer[i], i, cur_line, cur_col);
        addch('\n');
    }
    
    addstr(std::to_string(cur_line).c_str());
    addch('\n');
    addstr(std::to_string(cur_col).c_str());
   
    /* Refresh screen and clear for next frame */
    refresh();
}
