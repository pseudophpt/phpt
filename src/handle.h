#ifndef HANDLE_H
#define HANDLE_H

class handle {
    public:
        handle (void);
        
        /* Base handler class */
        class handler {
            public:
                handler (void) {  }
                virtual ~handler (void) = default; 
                virtual int handle_char (int c) { return 0; }
        };
        
        class modify : public handler {
            public:
                modify(void);
                int handle_char (int c);
        };
        
        class command : public handler{
            public:
                command (void);
                int handle_char (int c); 
        };
        
        void init (void);
        
        int handle_char (int c);    
        void set_handler (handler *new_h); 
        
        static handler *h;
};

#endif
