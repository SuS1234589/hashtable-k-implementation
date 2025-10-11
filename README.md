# Custom Hashtable Implementation 
This project is a custom implememtation of a hashtable based on `std::unordered_maps`. This is a closed addressing implementation of a hashtable, where each bucket can hold upto k elements. This project also includes script for testing purposes and benchmarking the implementation with C++ `std::unordered_maps`. The scripts compare both with 1 million, 10 million and 100 million key-value pairs. 

Files
------
`hashtable.h`, `hashtable.cpp` – Custom hashtable implementation.

`generator.cpp` – Generates synthetic test data (testdata.txt) with millions of key-value pairs.

`test_drive.cpp` – Loads data, inserts it into both hash tables, checks correctness, and benchmarks insertion and lookup performance.

`reading.cpp` – (if used) For custom data reading tasks.

`executable.sh` - contains all the commands to test the hashtbale. 

Compilation
-------------
Now to compile and run everything do the following: 
```
g++ -02 -std=c++17 generator.cpp -o generator
./generator
```

The above 2 lines will generate a `.txt` file that would contain all the key-value pairs. Currenyly the number of generated cases is 1 mil. 
To compile and run the test cases, do the following 

```
g++ -03 -std=c++17 test_drive.cpp -o test_drive
./test_drive
```

After you are more familiar with the commands you can use `executable.sh` to test the hashtable.
`./executable.sh`


Benchmark Results
-------------------------------------
```
Entries: 100,000
    CustomHashtable Insert: 17,252 ms
    std::unordered_map Insert: 122 ms
    CustomHashtable Load Factor: 10,000
    std::unordered_map Load Factor: 0.972035
    CustomHashtable Lookup: 17,629 ms
    std::unordered_map Lookup: 18 ms
    Mismatches: 0 Missed Keys: 0

Entries: 1,000,000
    CustomHashtable Insert: 145,776 ms
    std::unordered_map Insert: 578 ms
    CustomHashtable Load Factor: 100,000
    std::unordered_map Load Factor: 0.607446
    CustomHashtable Lookup: 144,274 ms
    std::unordered_map Lookup: 76 ms
    Mismatches: 0 Missed Keys: 0
```

Conclusion 
-----------
This project demonstrates a custom hash table that, when parameterized appropriately, can match or even slightly outperform `std::unordered_map` for specific workloads—though with less generality and scalability. For extremely large datasets, further optimization is required for practical performance.

In the current state, the hashtable takes 10 buckets, where each bucket can hold upto 100 elements. The formula for a customa hashtable implementation load factor is number of elements / number of bucekts. Whenever the load factor is above 1 that means that there were collisions. The purpose of this testing was to stress the load factor and make it greater than 1. 
