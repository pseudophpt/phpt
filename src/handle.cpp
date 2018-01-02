#include "handle.h"
#include "interface.h"
#include "buffer.h"

handle::handler *handle::h;
std::string handle::clipboard;

/* Constructor for modify class */
handle::modify::modify (void) {

}

std::string handle::modify::get_name (void) {
    return "MODIFY";
}

std::string handle::command::get_name (void) {
    return "COMMAND";
}

std::string handle::get_name (void) {
    return h->get_name();
}

/* Handler for modify mode */
int handle::modify::handle_char (int c) {
    switch (c) {
        case KEY_UP:
            {
                interface i;
                i.move_y(-1);
            }
            break;
        case KEY_DOWN:
            {
                interface i;
                i.move_y(1);
            }
            break;
        case KEY_LEFT:
            {
                interface i;
                i.move_x(-1);
            }
            break;
        case KEY_RIGHT:
            {
                interface i;
                i.move_x(1);
            }
            break;
        case KEY_F(1):
            {
                handle h;
                h.set_handler(new handle::command);
            }
            break;
        case '\n':
            {
                buffer b;
                interface i;
                
                std::string empty = "";
                b.insert_line(i.cur_line + 1, empty);
                i.move_y(1);
            }
            break;
        case KEY_PPAGE:
            {
                interface i;
                i.scr(-1);
            }
            break;
        case KEY_NPAGE:
            {
                interface i;
                i.scr(1);
            }
            break;
        case KEY_BACKSPACE:
            {
                buffer b;
                interface i; 
                
                b.delete_char(i.cur_line, i.cur_col - 1);
                i.move_x(-1);
            }
            break;
        default:
            {
                /* Set up buffer and interface */
                buffer b;
                interface i;
                
                b.insert_char (i.cur_line, i.cur_col, (char)c);
                /* Next character */
                i.move_x(1);
            }
            break; 
    }    
    {
        interface i;
        i.draw ();
    }
    return 1;
}

/* Constructor for command class */
handle::command::command (void) {

}

/* Handler for command mode */
int handle::command::handle_char (int c) {
    switch(c) {
        case 'k':
        case KEY_UP:
            {
                interface i;
                i.move_y(-1);
            }
            break;
        case 'l':
        case KEY_DOWN:
            {
                interface i;
                i.move_y(1);
            }
            break;
        case 'j':
        case KEY_LEFT:
            {
                interface i;
                i.move_x(-1);
            }
            break;
        case ';':
        case KEY_RIGHT:
            {
                interface i;
                i.move_x(1);
            }
            break;
        case KEY_F(2):
            {
                handle h;
                h.set_handler(new handle::modify);
            }
            break;
        case 'q':
            return 0;
            break;
        case 'u':
            {
                buffer b;
                interface i;
                
                clipboard = b.text_buffer[i.cur_line];
                
            }
            break;
        case 'i':
            {
                buffer b;
                interface i;
                
                clipboard = b.text_buffer[i.cur_line];
                b.delete_line(i.cur_line);
            }
            break; 
        case 'o':
            {
                buffer b;
                interface i;
                
                b.insert_line(i.cur_line + 1, clipboard);
            }
            break;
        case 'p':
            {
                buffer b;
                interface i; 
                
                b.delete_line(i.cur_line);
                b.insert_line(i.cur_line, clipboard);
            }
            break;
        case '7':
            {
                interface i;
                
                i.cur_col = 0;
                i.cur_line = 0;
            }
            break;
        case '8':
            {
                interface i;
                
                i.cur_col = 0;
            }
            break;
        case '9':
            {
                interface i;
                buffer b;
                
                i.cur_col = b.text_buffer[i.cur_line].size();
            }
            break;
        case '0':
            {   
                interface i;
                buffer b;
                
                i.cur_line = b.text_buffer.size() - 1;
                i.cur_col = b.text_buffer[i.cur_line].size();   
            }       
    }
    {
        interface i;
        i.draw();
    }    
 
    return 1; 
}

/* Constructor for handle class */
handle::handle (void) {
}

void handle::init (void) {
    /* Default handler is modify */
    handle::h = new modify;
    
    /* Init clipboard */
    clipboard = "";
}

/* Input handler. Calls current handler */
int handle::handle_char (int c) {
    /* Call respective handler */
    return h->handle_char(c);
}

/* Sets input handler */
void handle::set_handler (handler *new_h) {
    /* Set handler */
    delete h;
    h = new_h;
}


