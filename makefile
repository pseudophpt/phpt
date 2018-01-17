CXX = g++
CXXFLAGS = -Wall -g

SRC_DIR = ./src
OBJ_DIR = ./obj
BIN_DIR = ./bin

VERSION = 3.23

SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))

all: $(OBJ_FILES)
	g++ -lncurses -o $(BIN_DIR)/phpt-$(VERSION) $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	g++ $(CXXFLAGS) -c -o $@ $<

clean:
	rm $(OBJ_FILES)
