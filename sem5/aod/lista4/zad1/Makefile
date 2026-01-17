CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -O3 -march=native -flto

SRC_DIR = src
BIN_DIR = bin

TARGET = main

SRCS = $(SRC_DIR)/main.cpp \
       $(SRC_DIR)/Graph.cpp \
       $(SRC_DIR)/HyperCube.cpp \
	   $(SRC_DIR)/EdmondsKarp.cpp

OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(BIN_DIR)/%.o)
HEADERS = $(SRC_DIR)/Graph.hpp

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

$(BIN_DIR)/%.o: $(SRC_DIR)/%.cpp $(HEADERS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(BIN_DIR)/*.o $(TARGET)

.PHONY: all clean
