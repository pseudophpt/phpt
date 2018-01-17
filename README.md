# Usage

`./bin/phpt-<ver>`

# Controls

### Modify

Modify mode is your standard text editing mode. Type to enter text, arrow keys to navigate. Press `F2` to enter this mode

### Input

In this mode, anything you type will be put in the bottom bar. When you press enter, it passes this command to whatever brought you.

### Command

Command mode allows you to do many fast operations

* `5` to go to beginning of file, `6` to go to beginning of line, `7` to go to previous word, `8` to go to next word,`9` to go to end of line, `0` to go to end of file
* *currently unimplemented* `u` to copy line, `i` to cut, `o` to paste line, `p` to paste overwrite
* `jkl;` arrow keys like in vim
* `q` to quit
* *currently unimplemented* `y` to find and replace [input mode]: <find term> <replace term>

Press `F1` to enter this mode 

# Updates

### 3.20 
* Add status bar

###### r1 (3.21) - Add line and column function for status bar

###### r2 (3.22) - Fix line and column numbers, add percentage, add scrolling functionality

###### r3 (3.23) - Fix tab, add autocompleting brackets, add mode status

### 3.10
* Add cursor
* Fix word movement

###### r1 (3.11) - Add quit button

###### r2 (3.12) - Add line numbers

###### r3 (3.13) - Add line number highlighting, clean up `interface.cpp`

### 3.00
* Complete rewrite
* Enters fixed
* Use unordered map instead of switch cases for customizability
* Add word movement

### 2.30

* Add updates (kind of meta, huh?)
* Add input mode
* Add find and replace

### 2.20

* Add cursor, more

### 2.10

* Added highlighted line, more segfaults fixed

### 2.00

* Added line numbering, status bar
* Fixed various issues with segfaults

### 1.00

* Initial
* Simple text editing




