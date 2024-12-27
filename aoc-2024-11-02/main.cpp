/*
* Advent of Code Day 11
 * Part 02
 * Deepak Shenoy
 *
 */

#include <iostream>
#include <fstream>
#include <map>

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

vector<string> breakDownNumber(string numberValue) {
    vector<string> newNumbers;
    long stoneNumberSize = numberValue.length();
    if (numberValue.compare("0") == 0) {
        newNumbers.push_back("1");
    } else if (stoneNumberSize % 2 == 0) {
        newNumbers.push_back(numberValue.substr(0, stoneNumberSize / 2));
        string rhsNumber = numberValue.substr(stoneNumberSize / 2, stoneNumberSize);
        long rhsNumberValue = stol(rhsNumber);
        newNumbers.push_back(to_string(rhsNumberValue));
    } else newNumbers.push_back(to_string((stol(numberValue) * 2024)));
    return newNumbers;
}

long memoizationBuilder(string numberVal, int iteration, map<tuple<string, long>, long> &memoizationMap) {
    tuple<string, long> key = make_tuple(numberVal, iteration);
    long value = 0;
    if (memoizationMap.find(key) != memoizationMap.end()) {
        return memoizationMap[key];
    } else {
        vector<string> newNumbers = breakDownNumber(numberVal);
        if (iteration == 1) return newNumbers.size();
        for (int i = 0; i < newNumbers.size() && iteration > 0; i++) {
            value += memoizationBuilder(newNumbers[i], iteration - 1, memoizationMap);
        }
        iteration--;
        memoizationMap[key] = value;
    }
    return value;
}

long processStonesMemoization(vector<string> &stones, int iterations, map<tuple<string, long>, long> &memoizationMap) {
    long count = 0;
    for (int i = 0; i < stones.size(); i++) {
        count += memoizationBuilder(stones[i], iterations, memoizationMap);
    }
    return count;
}

int main() {
    vector<string> listOfStones;
    map<tuple<string, long>, long> memoizationOfStoneFormations;
    readData(FILENAME01, listOfStones);
    long result = processStonesMemoization(listOfStones, 75, memoizationOfStoneFormations);
    printf("\nFinal result: %lu\n", result);
    return 0;
}