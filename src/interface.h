#ifndef INTERFACE_H
#define INTERFACE_H

#include <ncurses.h>
#include <vector>
#include <string>

class interface {
    private:
        std::string format_line_number (int line_number);
    public:
        interface (void) {  }
        
        void init (void);
        void quit (void);
        
        int getchar (void);
        
        void draw (std::vector<std::string> buffer, int cur_line, int cur_col, int top_line);
};

#endif
