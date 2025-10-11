#!/bin/bash
g++ -O2 -std=c++17 generator.cpp -o generator
./generator 
echo "running test_drive"
g++ -O3 -std=c++17 test_drive.cpp -o test_drive
./test_drive


