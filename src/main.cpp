#include "interface.h"
#include "buffer.h"
#include "handle.h"

int main()
{	
    {
        interface i;
        i.init();
        
        handle h;
        h.init();
        
        while (h.handle_char(i.getchar())); 
        i.quit();
    }
	return 0;
}
