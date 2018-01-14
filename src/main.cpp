#include "interface.h"
#include "buffer.h"
#include "handle.h"
#include "control.h"
#include <iostream>

int main(void)
{	
    {
        interface i;
        i.init();
        
        handle h;
        h.init();
        
        buffer b;
        b.init();
        
        control c;
        c.init();
        
        while (h.handle_char(i.getchar())); 
        i.quit();
    }
	return 0;
}
