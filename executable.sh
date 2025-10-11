#!/bin/bash

g++ -std=c++17 generator.cpp -o generator
./generator 
echo"running test_drive"
g++ -std=c++17 test_drive.cpp -o test_drive
./test_drive 
