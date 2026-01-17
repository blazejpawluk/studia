CXX := g++
CXXFLAGS := -Wall -Wextra -std=c++17 -O3 -march=native -flto

SRC_DIR := src
BIN_DIR := bin
OUT_DIR := output

SRCS := $(filter-out $(SRC_DIR)/experiments/%,$(wildcard $(SRC_DIR)/*.cpp))
SRCS += $(wildcard $(SRC_DIR)/*.cpp)

OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(BIN_DIR)/%.o,$(SRCS))

TARGET := EdmondKarp

EXP_SRC := $(SRC_DIR)/experiments/generateData.cpp
EXP_OBJ := $(BIN_DIR)/experiments/generateData.o
EXP_TARGET := $(BIN_DIR)/generateData

.PHONY: all experiment clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(BIN_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(EXP_TARGET): $(EXP_OBJ) $(BIN_DIR)/Graph.o $(BIN_DIR)/HyperCube.o $(BIN_DIR)/EdmondsKarp.o | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(EXP_OBJ): $(EXP_SRC) | $(BIN_DIR)/experiments
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BIN_DIR)/experiments:
	mkdir -p $(BIN_DIR)/experiments

experiment: $(OUT_DIR) $(EXP_TARGET)
	@./$(EXP_TARGET)
	@python3 $(SRC_DIR)/experiments/generateCharts.py

$(OUT_DIR):
	mkdir -p $(OUT_DIR)

clean:
	rm -f $(TARGET)
	rm -rf $(BIN_DIR)/*
	rm -rf $(OUT_DIR)/*