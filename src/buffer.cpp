#include "buffer.h"


std::vector<std::string> buffer::text_buffer;

buffer::buffer (void) {

}

void buffer::init (void) {
    /* Set up first line */
    new_line (0, "");
}

void buffer::new_line (int line, std::string init_string) {
    /* Buffer position */
    auto iterator = text_buffer.begin() + line;
    
    /* Insert at position */
    text_buffer.insert(iterator, init_string);
}

void buffer::insert_char (int line, int column, char c) {
    /* Set value */
    text_buffer[line].insert(column, 1, c);
}
