#include "control.h"
#include "buffer.h"

/* Class variables */
int control::cur_line;
int control::cur_col;
int control::top_line;

/* Initialize */
void control::init (void) { 
    /* Initialize variables */
    cur_line = 0;
    cur_col = 0;
    top_line = 0;
}

/* Getters */
int control::get_cur_line (void) {
    return cur_line;
}

int control::get_cur_col (void) {
    return cur_col;
}

int control::get_top_line (void) {
    return top_line;
}

/* Move cursor in the x direction */
void control::move_x (int delta_x) {
    /* Increment delta x */
    cur_col += delta_x;
    
    /* Fix errors */
    {
        /* Interact with the buffer in a scope */
        buffer b;
        
        /* Don't let it go before the end of the line */
        if (cur_col < 0)
            cur_col = 0;
        
        /* Or after, for that matter */
        else if (cur_col >= b.get_line_size(cur_line))
            cur_col = b.get_line_size(cur_line);
    }   
}

/* Move cursor in the y direction */
void control::move_y (int delta_y) {
    /* Increment delta y */
    cur_line += delta_y;

    /* Fix errors */
    {
        /* Interact with the buffer in a scope */
        buffer b;
        
        /* Don't let it go before the end of the line */
        if (cur_line < 0)
            cur_line = 0;
        
        /* Or after, for that matter */
        else if (cur_line >= b.get_size())
            cur_line = b.get_size() - 1;
        
        /* Also make sure we're not outside of the  */
        if (cur_col >= b.get_line_size(cur_line))
            cur_col = b.get_line_size(cur_line);
        
    }
}

/* Scroll screen by a certain amount */
void control::scr (int amount) {
    /* Increment top line */
    top_line += amount;
    
    /* Error correcting */
    if (top_line < 0)
        top_line = 0;
}

