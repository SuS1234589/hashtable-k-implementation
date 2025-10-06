#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>

int main() {
    const std::string filename = "testdata.txt";
    const int N = 10000000; // 1 million pairs

    std::ofstream out(filename);
    if (!out.is_open()) {
        std::cerr << "Error: Could not open file for writing.\n";
        return 1;
    }

    std::srand(static_cast<unsigned>(std::time(nullptr)));

    for (int i = 0; i < N; i++) {
        std::string key = "key_" + std::to_string(i);
        int value = std::rand() % 100000; // values can repeat
        out << key << " " << value << "\n";
    }

    out.close();
    std::cout << "Generated " << N << " key:value pairs in " << filename << "\n";
    return 0;
}

