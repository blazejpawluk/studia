CXX = g++
CXXFLAGS = -O2 -std=c++17 -Wall -Wextra
INCLUDES = -Isrc

SRC_DIR = src
OBJ_DIR = bin
ROOT_DIR = .

COMMON_SRC = \
	Graph.cpp \
	BiPartite.cpp \
	EdmondsKarp.cpp \
	GLKPgenerator.cpp \
	HyperCube.cpp

EK_SRC = mainEK.cpp
BP_SRC = mainBP.cpp

COMMON_SRC := $(addprefix $(SRC_DIR)/,$(COMMON_SRC))
EK_SRC := $(SRC_DIR)/$(EK_SRC)
BP_SRC := $(SRC_DIR)/$(BP_SRC)

COMMON_OBJ := $(COMMON_SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
EK_OBJ := $(OBJ_DIR)/mainEK.o
BP_OBJ := $(OBJ_DIR)/mainBP.o

EK_BIN = EdmondsKarp
BP_BIN = Matching

.PHONY: all edmonds-karp matching clean

all: edmonds-karp matching

edmonds-karp: $(EK_BIN)

$(EK_BIN): $(COMMON_OBJ) $(EK_OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@

matching: $(BP_BIN)

$(BP_BIN): $(COMMON_OBJ) $(BP_OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -f $(OBJ_DIR)/*.o
	rm -f EdmondsKarp Matching
