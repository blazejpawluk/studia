TARGET = test

all: $(TARGET)

$(TARGET): BinHeap.cpp Graph.cpp Dijkstra.cpp Dial.cpp RadixHeap.cpp test.cpp
	g++ -o $(TARGET) BinHeap.cpp Graph.cpp Dijkstra.cpp Dial.cpp RadixHeap.cpp test.cpp

clean:
	rm -f test.exe