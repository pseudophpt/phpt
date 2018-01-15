#ifndef CONTROL_H
#define CONTROL_H

#include <ncurses.h>
#include <vector>
#include <string>

class control {
    private:
        static int cur_line;
        static int cur_col;
        static int top_line;
    
    public:
        control (void) {  }
        
        void init (void);
        
        void move_x (int delta_x);
        void move_y (int delta_y);
        
        void scr (int amount);
        
        int get_cur_line (void);
        int get_cur_col (void);
        int get_top_line (void);
        
        void set_cur_line (int cur_line);
        void set_cur_col (int cur_col);
        void set_top_line (int top_line);
};

#endif
