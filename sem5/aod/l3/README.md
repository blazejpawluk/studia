Autor: Błażej Pawluk, 279738

PORÓWNANIE IMPLEMENTACJI ALGORYTMU DIJKSTRY

Porónywane algorytmy:
* Podstawowa wersja algorytmu Dijkstry
* Algorytm Diala
* Algorytm RadixHeap

Struktura projektu:
inputs/ 					*pliki grafów (.gr)*
	|-- Long-C/
	|-- Long-n/
	|-- Random4-C/
	|-- Random4-n/
	|-- Square-C/
	|-- Square-n/
	|-- USA-road-t/

outputs/ 					*wyniki testów*
	|-- raw/ 				*wyniki generowane (formaty .txt)*
		|-- Long-C.txt 		*wyniki testów dla problemu ss w formacie opisanym poniżej dla tej rodziny grafów*
		|-- Long-n.txt
		|-- Random4-C.txt
		|-- Random4-n.txt
		|-- Square-C.txt
		|-- Square-n.txt
		|-- USA-road-t.txt
		|-- paths.txt 		*wyniki testów dla problemu p2p w formacie opisanym poniżej*

	|-- graphs /			*wyniki przedstawione w formie grafów*

lib/ 						*pliki nagłówkowe*
	|-- alg/				*testowane algorytmy*
		|-- dijkstra.hpp
		|-- dial.hpp
		|-- radixheap.hpp
	
	|-- Graph.hpp			*struct grafu*
	|-- Parser.hpp			*funkcje przetwarzające input*
	|-- Writer.hpp			*funkcje tworzące pliki wynikowe*

alg/
	|-- alg/				*implementacje funckji z plików nagłówkowych
	|-- utils/

	|-- Dijkstra.cpp		*kody do testowania pojedynczych algorytmów*
	|-- Dial.cpp
	|-- RadixHeap.cpp

	|-- Test.cpp			*kod do przeprowadzenia ogólnych testów - generuje pliki do folderu raw*

.gitignore
Makefile
README.md

Polecenia Makefile:
* make *tworzy pliki dijkstra, dial, radixheap do testowania pojedynczych algorytmow*
* make algorytm *tworzy plik algorytm do testowania danego algorytmu*
* make test *tworzy plik test do przeprowadzenia ogólnych testów*
* make clean *usuwa wszystkie pliki wykonawcze z folderu*

Uruchomienie programów:
tryb ss:
  .algorytm -d graf.gr -ss <źródła.ss> -oss wynik.res

tryb p2p:
  .algorytm -d graf.gr -p2p pary.p2p -op2p wynik.res