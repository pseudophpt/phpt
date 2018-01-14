#ifndef BUFFER_H
#define BUFFER_H

#include <vector>
#include <string>

class buffer {
    private:
        static std::vector<std::string> text_buffer;
    public:
        buffer (void);
        void init (void);
        void delete_char (int line, int column);
        void insert_char (int line, int column, char c);
        void insert_line (int line, int column);
        void delete_line (int line);
        int get_size (void);
        int get_line_size (int line);
        
        std::vector<std::string> get_text_buffer (void);
};

#endif
