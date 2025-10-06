# Custom Hashtable Implementation 
This project is a custom implememtation of a hashtable based on `std::unordered_maps`. This is a closed addressing implementation of a hashtable, where each bucket can hold upto k elements. This project also includes script for testing purposes and benchmarking the implementation with C++ `std::unordered_maps`. The scripts compare both with 1 million, 10 million and 100 million key-value pairs. 

Files
------
`hashtable.h`, `hashtable.cpp` – Custom hashtable implementation.

`generator.cpp` – Generates synthetic test data (testdata.txt) with millions of key-value pairs.

`test_drive.cpp` – Loads data, inserts it into both hash tables, checks correctness, and benchmarks insertion and lookup performance.

`reading.cpp` – (if used) For custom data reading tasks.

Compilation
-------------
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
Benchmark Results
-------------------------------------
```
Entries: 1,000,000
  CustomHashtable Insert:         1377 ms
  std::unordered_map Insert:      1544 ms
  CustomHashtable Load Factor:    3.99999e-06
  std::unordered_map Load Factor: 0.607446
  CustomHashtable Lookup:         220 ms
  std::unordered_map Lookup:      263 ms
  Mismatches: 0  Missed Keys: 0

Entries: 10,000,000
  CustomHashtable Insert:         13,739 ms
  std::unordered_map Insert:      16,409 ms
  CustomHashtable Load Factor:    4e-07
  std::unordered_map Load Factor: 0.759303
  CustomHashtable Lookup:         3,350 ms
  std::unordered_map Lookup:      3,328 ms
  Mismatches: 0  Missed Keys: 0

Entries: 100,000,000
  CustomHashtable Insert:         674,605 ms
  std::unordered_map: Not measured (test interrupted)
  Lookup: Not measured (impractical for current implementation)
```

Conclusion 
-----------
This project demonstrates a custom hash table that, when parameterized appropriately, can match or even slightly outperform `std::unordered_map` for specific workloads—though with less generality and scalability. For extremely large datasets, further optimization is required for practical performance.

I chose to create my custom hashtable with a bucket count equal to the number of elements inserted, which led to a very low load factor and almost no collisions. This maximized performance for lookup and insertion but used much more memory than typical hash tables. For real-world use, it’s common to use fewer buckets and a higher load factor to save space, but for benchmarking and demonstration, this setup clearly shows the impact of bucket count on speed.
