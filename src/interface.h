#ifndef INTERFACE_H
#define INTERFACE_H

#include <ncurses.h>
#include <vector>
#include <string>

class interface {
    private:
        std::string format_line_number (int line_number);
        void draw_line (std::string& line, int line_no, int cur_line, int cur_col);
        void draw_bar (std::vector<std::string>& status);
    public:
        interface (void) {  }
        
        void init (void);
        void quit (void);
        
        int getchar (void);
        
        void draw (std::vector<std::string>& buffer, std::vector<std::string>& status, int cur_line, int cur_col, int top_line);
};

#endif
