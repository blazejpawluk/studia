.PHONY: zad1 zad2 results clean

all: zad1 zad2

zad1:
	g++ -o zad1/gen CountryData.cpp zad1/generateData.cpp
	./zad1/gen
	python zad1/generateResults.py

zad2:
	g++ -o zad2/gen CountryData.cpp zad2/generateData.cpp
	./zad2/gen
	python zad2/generateResults.py

results:
	python zad1/generateResults.py
	python zad2/generateResults.py

clean:
	rm -rf zad1/gen zad1/data zad1/results
	rm -rf zad2/gen zad2/data zad2/results