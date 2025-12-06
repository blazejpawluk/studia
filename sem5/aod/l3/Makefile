SRC_DIR := src
LIB_DIR := lib
UTILS_DIR := $(SRC_DIR)/utils
ALG_DIR := $(SRC_DIR)/alg

LIB_SRC := $(UTILS_DIR)/Graph.cpp $(UTILS_DIR)/Parser.cpp $(UTILS_DIR)/Writer.cpp

DIJKSTRA_SRC := $(SRC_DIR)/Dijkstra.cpp $(ALG_DIR)/Dijkstra.cpp $(LIB_SRC)
DIAL_SRC := $(SRC_DIR)/Dial.cpp $(ALG_DIR)/Dial.cpp $(LIB_SRC)
RADIXHEAP_SRC := $(SRC_DIR)/RadixHeap.cpp $(ALG_DIR)/RadixHeap.cpp $(LIB_SRC)
TEST_SRC := $(SRC_DIR)/Test.cpp $(ALG_DIR)/Dijkstra.cpp $(ALG_DIR)/Dial.cpp $(ALG_DIR)/RadixHeap.cpp $(LIB_SRC)

DIJKSTRA_BIN := dijkstra
DIAL_BIN := dial
RADIXHEAP_BIN := radixheap
TEST_BIN := test

all: $(DIJKSTRA_BIN) $(DIAL_BIN) $(RADIXHEAP_BIN)

$(DIJKSTRA_BIN): $(DIJKSTRA_SRC)
	g++ -o $@ $(DIJKSTRA_SRC)

$(DIAL_BIN): $(DIAL_SRC)
	g++ -o $@ $(DIAL_SRC)

$(RADIXHEAP_BIN): $(RADIXHEAP_SRC)
	g++ -o $@ $(RADIXHEAP_SRC)

$(TEST_BIN): $(TEST_SRC)
	g++ -o $@ $(TEST_SRC)

clean:
	rm -f $(DIJKSTRA_BIN) $(DIAL_BIN) $(RADIXHEAP_BIN) $(TEST_BIN)

.PHONY: all clean dijkstra dial radixheap