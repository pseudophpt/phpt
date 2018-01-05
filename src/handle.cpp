#include "handle.h"
#include "interface.h"
#include "buffer.h"

handle::handler *handle::h;
std::string handle::clipboard;
std::string handle::in;
int handle::input::command;

/* Constructor for modify class */
handle::modify::modify (void) {

}

/* Constructor for command class */
handle::command::command (void) {

}

/* Constructor for modify class */
handle::input::input (int c) {
    command = c; 
}

/* Constructor for handle class */
handle::handle (void) {

}

std::string handle::modify::get_name (void) {
    return "MODIFY";
}

std::string handle::command::get_name (void) {
    return "COMMAND";
}

std::string handle::input::get_name (void) {
    return "INPUT";
}

std::string handle::get_name (void) {
    return h->get_name();
}

void handle::init (void) {
    /* Default handler is command */
    handle::h = new command;
    
    /* Init clipboard and input */
    clipboard = "";
    in= "";
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

void handle::input::perform (int c, std::string i) {
    switch (c) {
        case 'y':
            {
                buffer b;
                
                std::vector<std::string> tokens;
                std::istringstream iss(i.c_str());
                
                for (std::string s; iss >> s; )
                    tokens.push_back(s);
                
                if (tokens.size() < 2)
                    return;
                
                std::string find = tokens[0];
                std::string replace = tokens[1];
                
                for (std::string &s : b.text_buffer) {
                    boost::replace_all(s, find, replace);
                }   
            }
            break;
    }
}

/* Handler for input mode */
int handle::input::handle_char (int c) {
    switch (c) {
        case '\n':
            {
                handle h;
                
                h.set_handler (new handle::command);
                perform(command, in);
                in = "";
                
            }
            break;
        case KEY_BACKSPACE:
            if (in.size() > 0)
                in.pop_back();
            break;
        default:
            in.push_back(c);
            break; 
    }
    {
        interface i;
        i.draw();
    }
    return 1;
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
        case '{':
            {
                buffer b;
                interface i;
                
                b.insert_char(i.cur_line, i.cur_col, '{');
                b.insert_char(i.cur_line, i.cur_col + 1, '}');
                
                i.move_x(1);
            }
            break;
        case '(':
            {
                buffer b;
                interface i;
                
                b.insert_char(i.cur_line, i.cur_col, '(');
                b.insert_char(i.cur_line, i.cur_col + 1, ')');
                
                i.move_x(1);
            }
            break;
        case '[':
            {
                buffer b;
                interface i;
                
                b.insert_char(i.cur_line, i.cur_col, '[');
                b.insert_char(i.cur_line, i.cur_col + 1, ']');
                
                i.move_x(1);
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
        /* Tab */
        case 9:
            {
                buffer b;
                interface i;
                
                for (int j = 0; j < 4; j ++) {
                    b.insert_char(i.cur_line, i.cur_col, ' ');
                }   
                
                i.move_x(4);
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
            break;     
        case 'y':
            {
                handle h;
                h.set_handler(new handle::input('y'));
            }
    }
    {
        interface i;
        i.draw();
    }    
 
    return 1; 
}



