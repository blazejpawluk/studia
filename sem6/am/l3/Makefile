.PHONY: clean

all:
	g++ -pthread -std=c++17 -o zad1/gen CountryData.cpp zad1/generateData.cpp
	./zad1/gen
# 	python zad1/generateResults.py

clean:
	rm -rf zad1/gen zad1/data zad1/results