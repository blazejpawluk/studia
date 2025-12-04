TARGET = program

all: $(TARGET)

$(TARGET): src/BinHeap.cpp src/Graph.cpp src/algorithm/Dijkstra.cpp src/algorithm/Dial.cpp src/algorithm/RadixHeap.cpp src/Parser.cpp src/Writer.cpp Main.cpp
	g++ -o $(TARGET) src/BinHeap.cpp src/Graph.cpp src/algorithm/Dijkstra.cpp src/algorithm/Dial.cpp src/algorithm/RadixHeap.cpp src/Parser.cpp src/Writer.cpp Main.cpp

clean:
	rm -f $(TARGET)