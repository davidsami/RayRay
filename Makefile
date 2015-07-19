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
CFLAGS=-c -O3 -Wall -Wno-deprecated -std=c++11
LFLAGS=-O3

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
	rm -rf $(TEST_BIN_DIR) $(TEST_EXEC)

# Test build
TEST_DIR=test
TEST_BIN_DIR=test/obj
TEST_SOURCES=$(wildcard $(TEST_DIR)/*.cpp) $(filter-out obj/src/main.o,$(OBJECTS))
TEST_OBJECTS=$(TEST_SOURCES:%.cpp=$(TEST_BIN_DIR)/%.o)
TEST_LIB_DIR=${LIB_DIR}/gtest-1.7.0
TEST_EXEC=Test

TEST_IFLAGS=$(IFLAGS) -I$(TEST_LIB_DIR)/include
TEST_CFLAGS=$(CFLAGS)
TEST_LFLAGS=$(LFLAGS) -L$(TEST_LIB_DIR) -lgtest_main -lpthread -lgtest 

test: test_folder $(TEST_EXEC)
	./Test

test_folder:
	@mkdir -p $(TEST_BIN_DIR)

$(TEST_EXEC): $(TEST_OBJECTS)
	$(CC) $(TEST_IFLAGS) $(TEST_LFLAGS) $(TEST_OBJECTS) -o $@

$(TEST_BIN_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CC) $(TEST_IFLAGS) $(TEST_CFLAGS) $< -o $@
