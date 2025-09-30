#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

int main() {
    std::ifstream file("archive/TFT_Challenger_MatchData.csv");
    std::ofstream outFile("combinations.json");
    if (!file.is_open() || !outFile.is_open()) {
        std::cerr << "Could not open the input or output file.\n";
        return 1;
    }

    std::string headerLine;
    std::getline(file, headerLine);
    std::stringstream headerStream(headerLine);
    std::string columnName;
    int combinationColIdx = -1;
    int colIdx = 0;

    // Find the index for the combination column
    while (std::getline(headerStream, columnName, ',')) {
        if (columnName == "combination") {
            combinationColIdx = colIdx;
        }
        ++colIdx;
    }

    if (combinationColIdx == -1) {
        std::cerr << "No 'combination' column found.\n";
        return 1;
    }

    std::string row;
    std::vector<std::string> combinations;
    while (std::getline(file, row)) {
        std::stringstream rowStream(row);
        std::string cell;
        int currColIdx = 0;
        while (std::getline(rowStream, cell, ',')) {
            if (currColIdx == combinationColIdx) {
                combinations.push_back(cell);
                break;
            }
            ++currColIdx;
        }
    }

    // Write as a JSON array to combinations.json
    outFile << "[\n";
    for (size_t i = 0; i < combinations.size(); ++i) {
        outFile << combinations[i];
        if (i != combinations.size() - 1)
            outFile << ",\n";
    }
    outFile << "\n]\n";

    file.close();
    outFile.close();
    return 0;
}

