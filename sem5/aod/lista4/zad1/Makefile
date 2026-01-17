CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -O3 -march=native -flto

SRC_DIR = src
BIN_DIR = bin

TARGET = edmonds-karp

SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(BIN_DIR)/%.o,$(SRCS))

all: $(TARGET)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(TARGET): $(BIN_DIR) $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

$(BIN_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(BIN_DIR)/*.o $(TARGET)

.PHONY: all clean
