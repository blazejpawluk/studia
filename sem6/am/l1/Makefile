.PHONY: zad12 zad3 zad4 clean

zad12:
	g++ -o zad12/gen CountryData.cpp zad12/generateData.cpp
	./zad12/gen
	python zad12/generateResults.py

zad3:
	g++ -o zad3/gen CountryData.cpp zad3/generateData.cpp
	./zad3/gen
	python zad3/generateResults.py

zad4:
	g++ -o zad4/gen CountryData.cpp zad4/generateData.cpp
	./zad4/gen
	python zad4/generateResults.py

clean:
	rm -rf zad12/gen zad12/data zad12/results
	rm -rf zad3/gen zad3/data zad3/results
	rm -rf zad4/gen zad4/data zad4/results