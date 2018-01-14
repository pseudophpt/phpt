#include "buffer.h"
#include "control.h"

std::vector<std::string> buffer::text_buffer;

buffer::buffer (void) {
    
}

/* Initialize text buffer */
void buffer::init (void) {
    /* Make initial element of empty string */
    text_buffer.push_back(std::string(""));
}

/* Get text buffer */
std::vector<std::string> buffer::get_text_buffer (void) {
    return text_buffer;
}

/* Erase one character at line, column */
void buffer::delete_char (int line, int column) {
    control c;
    /* Negative one since it's "off screen" */
    bool column_zero = (column == -1);
    bool line_zero = (line == 0);
    
    /* Does the character exist? */
    bool exists = (line <= get_size())
        && (column <= get_line_size(line)) 
        && (column >= -1)
        && (line >= 0);
    
    if (exists && column_zero && !line_zero) {
        int line_length = text_buffer[line - 1].size();
        
        /* Append current line to previous line */
        text_buffer[line - 1].append(text_buffer[line]);
        
        auto it = text_buffer.begin() + line;
        text_buffer.erase(it);
        
        c.move_y (-1);
        c.move_x (line_length);
    }

    else if (exists && !column_zero) {
        /* Cut normally */
        text_buffer[line].erase(column, 1);    
        c.move_x (-1);
    }
}

/* Insert one character at line, column */
void buffer::insert_char (int line, int column, char c) {
    text_buffer[line].insert(column, 1, c);    
} 

/* Split current line on next line */
void buffer::insert_line (int line, int col) {
    /* Get everything after current cursor */
    std::string sub = text_buffer[line].substr(col, get_line_size(line) - col);
    
    /* Remove that portion from current line */
    text_buffer[line].erase(col, get_line_size(line) - col);
    
    /* Put the new line after the current one */
    auto it = text_buffer.begin() + line + 1;
    text_buffer.insert(it, sub);
}

void buffer::delete_line (int line) {
    
}

/* Get line count */
int buffer::get_size (void) {
    return text_buffer.size();
}

/* Get character count of line */
int buffer::get_line_size (int line) {
    return text_buffer[line].size();
}
