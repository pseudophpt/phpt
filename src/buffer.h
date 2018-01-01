#ifndef BUFFER_H
#define BUFFER_H

#include <vector>
#include <string>

class buffer {
    public:
        static std::vector<std::string> text_buffer;
        buffer (void);
        void new_line (int line, std::string init_string);
        void insert_char (int line, int column, char c);
        void init (void);
}; 

#endif
