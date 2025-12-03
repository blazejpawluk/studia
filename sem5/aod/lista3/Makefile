TARGET = graph-test

all: $(TARGET)

$(TARGET): BinHeap.cpp Graph.cpp Dijkstra.cpp Dial.cpp RadixHeap.cpp Parser.cpp Writer.cpp Main.cpp
	g++ -o $(TARGET) BinHeap.cpp Graph.cpp Dijkstra.cpp Dial.cpp RadixHeap.cpp Parser.cpp Writer.cpp Main.cpp

clean:
	rm -f $(TARGET)