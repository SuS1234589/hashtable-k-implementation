# Custom Hashtable Implementation 
This project is a custom implememtation of a hashtable based on `std::unordered_maps`. This is a closed addressing implementation of a hashtable, where each bucket can hold upto k elements. This project also includes script for testing purposes and benchmarking the implementation with C++ `std::unordered_maps`. The scripts compare both with 1 million, 10 million and 100 million key-value pairs. 

##Files
`hashtable.h`, `hashtable.cpp` – Custom hashtable implementation.

`generator.cpp` – Generates synthetic test data (testdata.txt) with millions of key-value pairs.

`test_drive.cpp` – Loads data, inserts it into both hash tables, checks correctness, and benchmarks insertion and lookup performance.

`reading.cpp` – (if used) For custom data reading tasks.

##Compilation
Now to compile and run everything do the following: 
```
g++ -std=c++17 generator.cpp -o generator
./generator
```

The above 2 lines will generate a `.txt` file that would contain all the key-value pairs. Currenyly the number of generated cases is 1 mil. 
To compile and run the test cases, do the following 

```
g++ -std=c++17 test_drive.cpp -o test_drive
./test_drive
```

After this commmand-line will print out the benchmark for the 2 programs. 
Here are the results of running 1 million, 10 million and 100 million test cases. 

Entries      |  CustomHashtable Insert (ms)  |  std::unordered_map Insert (ms)  |  CustomHashtable Lookup (ms)  |  std::unordered_map Lookup (ms)  |  Mismatches  |  Missed Keys
-------------+-------------------------------+----------------------------------+-------------------------------+----------------------------------+--------------+-------------
1,000,000    |  1377                         |  1544                            |  220                          |  263                             |  0           |  0          
10,000,000   |  13739                        |  16409                           |  3350                         |  3328                            |  0           |  0          
100,000,000  |  674,605 (insert only)        |  —                               |  [unmeasured: impractical]    |  —                               |  —           |  —          
