#include "handle.h"
#include "buffer.h"
#include "interface.h"
#include "control.h"

/* Variables */
std::string handle::clipboard;
std::string handle::in;
handle::handler *handle::h;

std::unordered_map<int, std::function<int(void)>> handle::command::handle_map;
std::unordered_map<int, std::function<int(void)>> handle::modify::handle_map;

std::vector<std::function<std::string(void)>> handle::status_funcs;

/* Status bar functions */

std::string handle::status_get_lc (void) {
    std::string lc;
    control c;
    
    int line = c.get_cur_line();
    int col = c.get_cur_col();
    
    lc.push_back('L');
    lc.append(std::to_string(line));
    
    lc.push_back(' ');
    
    lc.push_back('C');
    lc.append(std::to_string(col));
    
    return lc;
}

/* Percentage function */

std::string handle::status_percentage (void) {
    std::string p;
    buffer b;
    control c;
    
    int top_line = c.get_top_line();
    p = std::to_string(top_line * 100 / b.get_size());
    
    p.push_back('%');
    
    return p;
}

/* Helper interaction functions */

/* Mode setters */
int handle::set_modify (void) {
    set_handler (new modify); 
    return 1; 
}

int handle::set_command (void) {
    set_handler (new command); 
    return 1; 
}

/* Actions */
int handle::backspace (void) {
    buffer b;
    control c;
    
    /* Get position */
    int line = c.get_cur_line();
    int col = c.get_cur_col();
    
    /* Delete previous character */
    b.delete_char(line, col - 1);
    
    return 1;
}

int handle::del (void) {
    control c;
    
    c.move_x(1);
    return backspace();
}

int handle::enter (void) {
    buffer b;
    control c;
    
    /* Get position */
    int line = c.get_cur_line();
    int col = c.get_cur_col();
    
    int size = b.get_line_size(line);
 
    /* Insert line */   
    b.insert_line(line, col);
    
    c.move_y(1);
    c.move_x(-size);
    
    return 1;
}


int handle::move_up (void) 
{
    control c;
    c.move_y(-1); 
    return 1;
}

int handle::move_down (void) 
{
    control c;
    c.move_y(1); 
    return 1;
}

int handle::move_left (void) 
{
    control c;
    c.move_x(-1); 
    return 1;
}

int handle::move_right (void) 
{
    control c;
    c.move_x(1); 
    return 1;
}

/* Jump to next word */
int handle::next_word (void) {
    buffer b;
    control c;
    
    /* Line won't change, so we evaluate it once here */
    std::string line = b.get_text_buffer()[c.get_cur_line()];
    
    while (line[c.get_cur_col()] != ' ' && (c.get_cur_col() < line.size())) {
        c.move_x(1);
    }
    
    c.move_x(1);
    
    return 1;
}

/* Jump to previous word */
int handle::prev_word (void) {
    buffer b;
    control c;
    
    c.move_x(-1);
    
    /* Line won't change, so we evaluate it once here */
    std::string line = b.get_text_buffer()[c.get_cur_line()];
    
    while (line[c.get_cur_col() - 1] != ' ' && (c.get_cur_col() > 0)) {
        c.move_x(-1);
    }
    
    //c.move_x(-1);
    
    return 1;
}

/* Jump to beginning of line */
int handle::start_line (void) {
    control c;
    
    c.set_cur_col(0);
    
    return 1;
}

/* Jump to end of line */
int handle::end_line (void) {
    control c;
    buffer b;
    
    c.set_cur_col(b.get_line_size(c.get_cur_line()));
    
    return 1;
}

/* Jump to beginning of buffer */
int handle::start_buffer (void) {
    control c;
    
    c.set_cur_col(0);
    c.set_cur_line(0);
    
    return 1;
}

/* Jump to end of buffer */
int handle::end_buffer (void) {
    control c;
    buffer b;
    
    c.set_cur_line(b.get_size() - 1);
    c.set_cur_col(b.get_line_size(c.get_cur_line()));
    
    return 1;
}

/* Scroll down */
int handle::scr_down (void) {
    control c;
    
    c.scr(1);
    
    return 1;
}

/* Scroll up */
int handle::scr_up (void) {
    control c;
    
    c.scr(-1);
    
    return 1;
}

/* This initializes all handling functions */
void handle::init (void) {
    /* Set the handler to command, default */
    h = new command;
    
    /* Set modes */
    command::handle_map[KEY_F(1)] = set_command;
    command::handle_map[KEY_F(2)] = set_modify;
    
    modify::handle_map[KEY_F(1)] = set_command;
    modify::handle_map[KEY_F(2)] = set_modify;
    
    /* Simple actions */
    modify::handle_map[KEY_BACKSPACE] = backspace;
    modify::handle_map[KEY_DC] = del;
    modify::handle_map['\n'] = enter;
    
    command::handle_map[KEY_DC] = del;
    command::handle_map['\n'] = enter;
    
    /*  Navigation */
    modify::handle_map[KEY_UP] = move_up;
    modify::handle_map[KEY_DOWN] = move_down;
    modify::handle_map[KEY_LEFT] = move_left;
    modify::handle_map[KEY_RIGHT] = move_right;
    
    command::handle_map[KEY_UP] = move_up;
    command::handle_map[KEY_DOWN] = move_down;
    command::handle_map[KEY_LEFT] = move_left;
    command::handle_map[KEY_RIGHT] = move_right;
    
    command::handle_map['l'] = move_up;
    command::handle_map['k'] = move_down;
    command::handle_map['j'] = move_left;
    command::handle_map[';'] = move_right;
    
    command::handle_map['5'] = start_buffer;
    command::handle_map['6'] = start_line;
    command::handle_map['7'] = prev_word;
    command::handle_map['8'] = next_word;
    command::handle_map['9'] = end_line;
    command::handle_map['0'] = end_buffer;
    
    command::handle_map['q'] = quit;    
    
    command::handle_map[KEY_NPAGE] = scr_down;
    command::handle_map[KEY_PPAGE] = scr_up;
    
    modify::handle_map[KEY_NPAGE] = scr_down;
    modify::handle_map[KEY_PPAGE] = scr_up;
    
    /* Status bar elements */
    
    /* Line and column numbeers */
    status_funcs.push_back(status_get_lc);
    status_funcs.push_back(status_percentage);
}

/* This sets the handler */
void handle::set_handler (handler *new_h) {
    /* De-allocate the old handler */
    delete h;
    /* Set the new one */
    h = new_h;
}

/* This function calls the current handler, to handle user input */
int handle::handle_char (int c) {
    /* Call respective handler */
    return h->handle_char(c);
}

/* This function calls the respective get_name function to get the current handler name */
std::string handle::get_name (void) {
    /* Call respective get_name() */
    return h->get_name();
}

/* Get the names of each handler */
std::string handle::modify::get_name (void) {
    return "MODIFY";
}

std::string handle::command::get_name (void) {
    return "COMMAND";
}

std::string handle::input::get_name (void) {
    return "INPUT";
}

/* Handles user input in each mode */ 
int handle::command::handle_char (int c) {
    interface i;
    control ct;
    buffer b;
    
    int cur_line = ct.get_cur_line();
    int cur_col = ct.get_cur_col();
    int top_line = ct.get_top_line();
    
    int ret = 1;
    
    /* Find handler for c */
    auto it = handle_map.find(c);
    /* If it exists, run it */
    if (it != handle_map.end()) {
        ret = it->second();
    }
    
    if (ret) {
        std::vector<std::string> text_buffer = b.get_text_buffer();
        cur_col = ct.get_cur_col();
        cur_line = ct.get_cur_line();
        top_line = ct.get_top_line();
        std::vector<std::string> status;
        
        for (std::function<std::string()> f : status_funcs ) {
            status.push_back(f());
        }
        
        i.draw(text_buffer, status, cur_line, cur_col, top_line);
    }
    
    return ret;
}

int handle::input::handle_char (int c) {
    return 1;
}

/* Handle character input in modify mode */
int handle::modify::handle_char (int c) {
    interface i;
    control ct;
    buffer b;
    
    int cur_line = ct.get_cur_line();
    int cur_col = ct.get_cur_col();
    int top_line = ct.get_top_line();
    
    /* Return value */
    int ret = 1;
    
    /* Find handler for c */
    auto it = handle_map.find(c);

    /* If it exists, run it */
    if (it != handle_map.end()) {
        ret = it->second();
    }
    
    else {
        b.insert_char(cur_line, cur_col, c);
        ct.move_x(1);
        
        ret = 1;
    }
    
    if (ret) {
        std::vector<std::string> text_buffer = b.get_text_buffer();
        cur_col = ct.get_cur_col();
        cur_line = ct.get_cur_line();
        top_line = ct.get_top_line();
        std::vector<std::string> status;
        
        for (std::function<std::string()> f : status_funcs ) {
            status.push_back(f());
        }
        
        i.draw(text_buffer, status, cur_line, cur_col, top_line);
    }    
    
    return ret;
}
