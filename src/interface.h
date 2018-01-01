#ifndef INTERFACE_H

#define INTERFACE_H

#include <ncurses.h>

class interface {
    public:
        void init (void);
        
        void move_x (int delta_x);
        void move_y (int delta_y);
        
        void draw (void);
        
        int getchar (void);
        
        void quit (void);
        
        static int pos_x;
        static int pos_y;
};

#endif

