.PHONY: zad12

zad12:
	g++ -o zad12/gen CountryData.cpp zad12/generateData.cpp
	./zad12/gen
	python zad12/generateResults.py

clean:
	rm -rf zad12/gen zad12/data zad12/results