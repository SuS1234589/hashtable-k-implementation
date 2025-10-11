#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <chrono>
#include "hashtable.h" // your implementation

using namespace std;
using namespace std::chrono;

int main() {
    const string filename = "testdata.txt";
    ifstream in(filename);
    if (!in.is_open()) {
        cerr << "Error: Could not open " << filename << endl;
        return 1;
    }

    Hashtable<string, int> customTable(10, 100);
    unordered_map<string, int> stdTable;
    vector<string> keys;
    string line, key;
    int value;
    size_t lineCount = 0;

    // --- Timing insertion: Custom Hashtable ---
    in.clear();
    in.seekg(0, ios::beg);
    auto custom_insert_start = high_resolution_clock::now();
    while (getline(in, line)) {
        istringstream iss(line);
        if (!(iss >> key >> value)) continue;
        customTable.insert(key, value);
        keys.push_back(key); // Store key for lookup timing
        ++lineCount;
    }
    auto custom_insert_end = high_resolution_clock::now();
    auto custom_insert_ms = duration_cast<milliseconds>(custom_insert_end - custom_insert_start).count();
    cout << "CustomHashtable Insertion: " << custom_insert_ms << " ms" << endl;

    // --- Timing insertion: std::unordered_map ---
    in.close();
    in.open(filename);
    lineCount = 0;
    auto std_insert_start = high_resolution_clock::now();
    while (getline(in, line)) {
        istringstream iss(line);
        if (!(iss >> key >> value)) continue;
        stdTable[key] = value;
        ++lineCount;
    }
    auto std_insert_end = high_resolution_clock::now();
    auto std_insert_ms = duration_cast<milliseconds>(std_insert_end - std_insert_start).count();
    cout << "std::unordered_map Insertion: " << std_insert_ms << " ms" << endl;

    cout << "\nLoaded " << lineCount << " entries into both tables.\n";


// Print load factor for custom table
double loadFactor = static_cast<double>(lineCount) / customTable.bucket_count;
cout << "CustomHashtable Load Factor: " << loadFactor << endl;

// Optionally, for std::unordered_map:
double stdLoadFactor = double(stdTable.size()) / stdTable.bucket_count();
cout << "std::unordered_map Load Factor: " << stdLoadFactor << endl;

// --- Timing lookup, etc, goes here ---

    // --- Timing lookup: CustomHashtable for all keys ---
    auto custom_lookup_start = high_resolution_clock::now();
    size_t custom_misses = 0;
    for (const auto& k : keys) {
        if (!customTable.find(k)) ++custom_misses;
    }
    auto custom_lookup_end = high_resolution_clock::now();
    auto custom_lookup_ms = duration_cast<milliseconds>(custom_lookup_end - custom_lookup_start).count();
    cout << "CustomHashtable Lookup: " << custom_lookup_ms << " ms" << endl;

    // --- Timing lookup: std::unordered_map for all keys ---
    auto std_lookup_start = high_resolution_clock::now();
    size_t std_misses = 0;
    for (const auto& k : keys) {
        if (stdTable.find(k) == stdTable.end()) ++std_misses;
    }
    auto std_lookup_end = high_resolution_clock::now();
    auto std_lookup_ms = duration_cast<milliseconds>(std_lookup_end - std_lookup_start).count();
    cout << "std::unordered_map Lookup: " << std_lookup_ms << " ms" << endl;

    // --- Correctness check: Compare all key-value pairs ---
    size_t mismatches = 0;
    for (size_t i = 0; i < customTable.table.size(); ++i) {
        Bucket<string, int>* bucket = customTable.table[i];
        size_t bucketNodeCount = 0;
        while (bucket) {
            for (size_t j = 0; j < bucket->elements.size(); ++j) {
                auto& pair = bucket->elements[j];
                auto it = stdTable.find(pair.first);
                if (it == stdTable.end() || it->second != pair.second) {
                    ++mismatches;
                }
            }
            bucket = bucket->next;
            if (bucketNodeCount > 100000000){
              cerr<<"Error: too many bucket nodes traversed, possible loop"<< endl;
              break;
      }
        }
    }

    if (mismatches == 0)
        cout << "\nNo mismatches: custom table matches std::unordered_map.\n";
    else
        cout << "\nTotal mismatches: " << mismatches << "\n";

    cout << "\nCustomHashtable missed " << custom_misses << " keys\n";
    cout << "std::unordered_map missed " << std_misses << " keys\n";

    in.close();
    return 0;
}

