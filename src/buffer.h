#ifndef BUFFER_H
#define BUFFER_H

#include <vector>
#include <string>

class buffer {
    public:
        static std::vector<std::string> text_buffer;
        buffer (void);
        void insert_char (int line, int column, char c);
        void delete_char (int line, int column);
        void insert_line (int pos, std::string init_string);
        void delete_line (int line);
        void init (void);
}; 

#endif
