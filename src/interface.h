#ifndef INTERFACE_H

#define INTERFACE_H

#include <ncurses.h>
#include <string>

class interface {
    public:
        void init (void);
        
        void move_x (int delta_x);
        void move_y (int delta_y);
        
        void draw (void);
        
        void scr (int amount);
        
        int getchar (void);
        
        void quit (void);
        
        static int cur_line;
        static int cur_col;
        static int top_line;
};

#endif

