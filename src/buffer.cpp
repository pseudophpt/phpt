#include "buffer.h"
#include "interface.h"
#include "handle.h" 

std::vector<std::string> buffer::text_buffer;

buffer::buffer (void) {

}

void buffer::init (void) {
    /* Empty buffer */
    std::string empty = "";
    text_buffer.insert(text_buffer.begin(), empty);
}

void buffer::delete_char (int line, int column) {
    /* Delete character at position */
    if (column < 0) { 
        /* Save and delete current line */
        if (line > 0) {
            std::string old_str = text_buffer[line];
            text_buffer.erase(text_buffer.begin() + line); 
            
            text_buffer[line - 1].append(old_str);
            {
                /* Move up a line */
                interface i;
                
                i.move_y(-1);
                i.move_x(1 + text_buffer[line - 1].size() - old_str.size());
            }
        }   
    }
    else {
        text_buffer[line].erase(column, 1);
    }   
}

void buffer::insert_char (int line, int column, char c) {
    /* Set value */
    text_buffer[line].insert(column, 1, c);
}

void buffer::insert_line (int pos, std::string init_string) {
    auto it = text_buffer.begin() + pos;

    text_buffer.insert(it, init_string);
}

void buffer::delete_line (int line) {
    auto it = text_buffer.begin() + line;

    text_buffer.erase(it);
}
