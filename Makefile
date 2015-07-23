CC=g++

SOURCE_DIR=src
INC_DIRS=inc
BIN_DIR=obj
LIB_DIR=lib

SOURCES=$(wildcard $(SOURCE_DIR)/*.cpp)
INCLUDES = $(addprefix -I,$(INC_DIRS)) \
		   -I$(LIB_DIR)
OBJECTS=$(SOURCES:%.cpp=$(BIN_DIR)/%.o)
EXECUTABLE=RayRay

IFLAGS=$(INCLUDES)
FLAGS=-O3
CFLAGS=$(FLAGS) -c -Wall -Wno-deprecated -std=c++14
LFLAGS=$(FLAGS)

all: folder $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(IFLAGS) $(LFLAGS) $(OBJECTS) -o $@

$(BIN_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CC) $(IFLAGS) $(CFLAGS) $< -o $@

folder:
	@mkdir -p $(BIN_DIR)

clean:
	rm -rf $(BIN_DIR) $(EXECUTABLE)
