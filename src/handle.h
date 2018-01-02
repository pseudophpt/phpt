#ifndef HANDLE_H
#define HANDLE_H

#include <string>

class handle {
    public:
        handle (void);
        
        /* Base handler class */
        class handler {
            public:
                handler (void) {  }
                virtual ~handler (void) = default; 
                virtual int handle_char (int c) { return 0; }
                virtual std::string get_name (void) { return "GENERIC"; }
        };
        
        class modify : public handler {
            public:
                modify(void);
                int handle_char (int c);
                std::string get_name (void); 
        };
        
        class command : public handler{
            public:
                command (void);
                int handle_char (int c); 
                std::string get_name (void); 
        };
        
        void init (void);
        
        int handle_char (int c);    
        std::string get_name (void);    
        
        void set_handler (handler *new_h); 
        
        static handler *h;
        static std::string clipboard;
};

#endif
