/*
* Advent of Code Day 11
 * Part 01
 * Deepak Shenoy
 *
 */

#include <iostream>
#include <fstream>

#define FILENAME01 "../input.txt"
#define FILENAME02 "../test_data.txt"

using namespace std;

bool readData(string fileName, vector<string> &inputData) {
    fstream inputFile(fileName);
    if (!inputFile.is_open()) {
        printf("Error: cannot open file %s\n", fileName.c_str());
        exit(-1);
    }
    string item;
    while (!inputFile.eof()) {
        getline(inputFile, item, ' ');
        inputData.push_back(item);
    }
    return true;
}

bool processStones(vector<string> &stones) {
    vector<string> newList;
    for (int i = 0; i < stones.size(); i++) {
        if (stones[i].compare("0") == 0) {
            newList.push_back("1");
            continue;
        }
        long stoneNumberSize = stones[i].length();
        if (stoneNumberSize % 2 == 0) {
            newList.push_back(stones[i].substr(0, stoneNumberSize / 2));
            string rhsNumber = stones[i].substr(stoneNumberSize / 2, stoneNumberSize);
            long rhsNumberValue = stol(rhsNumber);
            newList.push_back(to_string(rhsNumberValue));
            continue;
        }
        long stoneValue = stol(stones[i]) * 2024;
        newList.push_back(to_string(stoneValue));
    }
    stones = newList;
    return true;
}

int main() {
    vector<string> listOfStones;
    readData(FILENAME01, listOfStones);
    for (int j = 0; j < 25; j++) {
        processStones(listOfStones);
    }
    printf("Result: %i\n", listOfStones.size());
    return 0;
}