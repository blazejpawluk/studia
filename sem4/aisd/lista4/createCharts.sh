#!/usr/bin/env bash

cd zadanie2
g++ -o data.exe generateData.cpp
./data.exe
python chartGenerator.py
cd ..

cd zadanie4
g++ -o data.exe generateData.cpp
./data.exe
python chartGenerator.py
cd ..

cd zadanie6
g++ -o data.exe generateData.cpp
./data.exe
python chartGenerator.py
cd ..