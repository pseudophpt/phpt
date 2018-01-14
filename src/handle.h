#ifndef HANDLE_H
#define HANDLE_H

#include <string>
#include <unordered_map>
#include <functional>
#include <ncurses.h>

class handle 
{   
    private:        
        static int set_modify (void); 
        static int set_command (void); 
        
        static int backspace (void); 
        static int del (void); 
        static int enter (void); 
        
        static int move_down (void); 
        static int move_up (void); 
        static int move_left (void); 
        static int move_right (void); 
        
        class handler {
            public:
                handler (void) {  }
                virtual ~handler (void) = default;
                virtual std::string get_name (void) { return "UNKNOWN"; }
                virtual int handle_char (int c) { return 0; }
        };
        
        class modify : public handler {
            public:
                static std::unordered_map<int, std::function<int(void)>> handle_map;
                modify (void) {  }
                int handle_char (int c);
                std::string get_name (void);
        };
     
        class command : public handler {
            public:
                static std::unordered_map<int, std::function<int(void)>> handle_map;
                command (void) {  }
                int handle_char (int c);
                std::string get_name (void);
        };
       
        class input : public handler {
            private:
                static int command;
                void perform (int c, std::string input);
            public:
                input (int c) { command = c; }
                int handle_char (int c);
                std::string get_name (void);
        };
        
        static std::string clipboard;
        static std::string in;
        static handler *h;
    
    public:
        handle (void) {  }
        
        static void set_handler (handler *new_h);
        int handle_char (int c);
        static std::string get_name (void);
        static void init (void);
};

#endif
