#include "handle.h"
#include "interface.h"
#include "buffer.h"

handle::handler *handle::h;

/* Constructor for modify class */
handle::modify::modify (void) {

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
                return 0;
            }
            break;
        default:
            {
                /* Set up buffer and interface */
                buffer b;
                interface i;
                b.insert_char (i.pos_x, i.pos_y, (char)c);
                /* Next character */
                i.move_x(1);
            }
            break; 
    }    
    return 1;
}

/* Constructor for command class */
handle::command::command (void) {

}

/* Handler for command mode */
int handle::command::handle_char (int c) {
    return 0; 
}

/* Constructor for handle class */
handle::handle (void) {
}

void handle::init (void) {
    /* Default handler is modify */
    handle::h = new modify;
}

/* Input handler. Calls current handler */
int handle::handle_char (int c) {
    /* Call respective handler */
    return h->handle_char(c);
}

/* Sets input handler */
void handle::set_handler (handler *new_h) {
    /* Set handler */
    //delete h;
    h = new_h;
}


