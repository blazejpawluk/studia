all: dijkstra dial radixheap

dijkstra: src/BinHeap.cpp src/Graph.cpp src/algorithm/Dijkstra.cpp src/algorithm/Dial.cpp src/algorithm/RadixHeap.cpp src/Parser.cpp src/Writer.cpp Dijkstra.cpp
	g++ -o dijkstra src/BinHeap.cpp src/Graph.cpp src/algorithm/Dijkstra.cpp src/algorithm/Dial.cpp src/algorithm/RadixHeap.cpp src/Parser.cpp src/Writer.cpp Dijkstra.cpp

dial: src/BinHeap.cpp src/Graph.cpp src/algorithm/Dijkstra.cpp src/algorithm/Dial.cpp src/algorithm/RadixHeap.cpp src/Parser.cpp src/Writer.cpp Dial.cpp
	g++ -o dial src/BinHeap.cpp src/Graph.cpp src/algorithm/Dijkstra.cpp src/algorithm/Dial.cpp src/algorithm/RadixHeap.cpp src/Parser.cpp src/Writer.cpp Dial.cpp

radixheap: src/BinHeap.cpp src/Graph.cpp src/algorithm/Dijkstra.cpp src/algorithm/Dial.cpp src/algorithm/RadixHeap.cpp src/Parser.cpp src/Writer.cpp RadixHeap.cpp
	g++ -o radixheap src/BinHeap.cpp src/Graph.cpp src/algorithm/Dijkstra.cpp src/algorithm/Dial.cpp src/algorithm/RadixHeap.cpp src/Parser.cpp src/Writer.cpp RadixHeap.cpp

test: src/BinHeap.cpp src/Graph.cpp src/algorithm/Dijkstra.cpp src/algorithm/Dial.cpp src/algorithm/RadixHeap.cpp src/Parser.cpp src/Writer.cpp test.cpp
	g++ -o test src/BinHeap.cpp src/Graph.cpp src/algorithm/Dijkstra.cpp src/algorithm/Dial.cpp src/algorithm/RadixHeap.cpp src/Parser.cpp src/Writer.cpp test.cpp

clean:
	rm -f dijkstra dial radixheap