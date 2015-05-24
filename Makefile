CC=g++

SOURCE_DIR=src
INC_DIRS=inc
BIN_DIR=obj

SOURCES=$(wildcard $(SOURCE_DIR)/*.cpp)
INCLUDES = $(addprefix -I,$(INC_DIRS))
OBJECTS=$(SOURCES:%.cpp=$(BIN_DIR)/%.o)
EXECUTABLE=RayRay

IFLAGS=$(INCLUDES)
CFLAGS=-c -Wall -std=c++11
LFLAGS=

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

