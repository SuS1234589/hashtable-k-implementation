#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include "hashtable.h"   // <-- your implementation

int main() {
    const std::string filename = "testdata.txt";
    std::ifstream in(filename);

    if (!in.is_open()) {
        std::cerr << "Error: Could not open " << filename << "\n";
        return 1;
    }

    // ✅ adjust these args for your Hashtable
    Hashtable<std::string, int> customTable(1000003, 4);
    std::unordered_map<std::string, int> stdTable;

    std::string line, key;
    int value;
    size_t lineCount = 0;

    // Load pairs into both tables
    while (std::getline(in, line)) {
        std::istringstream iss(line);
        if (!(iss >> key >> value)) continue;

        customTable.insert(key, value);
        stdTable[key] = value;
        ++lineCount;
    }

    in.close();
    std::cout << "Loaded " << lineCount << " entries into both tables.\n";

    // ✅ Compare all keys
    size_t mismatches = 0;
    for (const auto &pair : stdTable) {
        const std::string &testKey = pair.first;
        int stdVal = pair.second;

        if (!customTable.find(testKey)) {
            std::cout << "[MISSING] " << testKey << " not found in custom table\n";
            ++mismatches;
            continue;
        }

        int customVal = customTable.get(testKey);
        if (customVal != stdVal) {
            std::cout << "[MISMATCH] " << testKey 
                      << " custom=" << customVal 
                      << " std=" << stdVal << "\n";
            ++mismatches;
        }
    }

    if (mismatches == 0) {
        std::cout << "no mismatches it works\n";
    } else {
        std::cout << "Total mismatches: " << mismatches << "\n";
    }

    return 0;
}

