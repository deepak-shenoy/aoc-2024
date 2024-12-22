/*
* Advent of Code Day 05
 * Part 01
 * Deepak Shenoy
 *
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>

#define FILENAME01 "../input.txt"
#define FILENAME02 "../test_data.txt"

#define _DELIMITER "|"

using namespace std;

// Assume that file is correctly formatted
bool readDataFile(string filename, map<int, vector<int>> &rules, vector<vector<int>> &printerList) {
    try {
        ifstream inputFile(filename);
        string line;
        int firstToken, secondToken;
        bool isNotEmptyLine = true;
        while (isNotEmptyLine) {
            getline(inputFile, line);
            if (line.empty()) {
                isNotEmptyLine = false;
                break;
            }
            auto position = line.find(_DELIMITER);
            firstToken = stoi(line.substr(0, position));
            secondToken = stoi(line.substr(position + 1));
            if(rules.find(firstToken) == rules.end()) {
                vector<int> newList = vector<int>({secondToken});
                rules.insert({firstToken, newList});
            } else {
                vector<int> *currentList = &rules[firstToken];
                currentList->push_back(secondToken);
            }
        }

        // Read printer list
        while(!inputFile.eof()) {
            getline(inputFile, line);
            istringstream lineStream(line);
            vector<int> printerLine;
            string pageNumber;
            while (getline(lineStream, pageNumber, ',')) {
                printerLine.push_back(stoi(pageNumber));
            }
            printerList.push_back(printerLine);
        }
    } catch(exception e) {
        printf("Exception occurred: %s\n", e.what());
        exit(-1);
    }
    return true;
}

bool satisfyConstraint(map<int, vector<int>> &rules, const vector<int> &list) {
    if(list.size() == 1) {
        printf("List only has one number\n");
        return false;
    }
    for(int i = 1; i < list.size(); i++) {
        for(int j = i - 1; j < i; j++) {
            for(int r = 0; r < rules[list[i]].size(); r++) {
                if(rules[list[i]][r] == list[j]) {
                    return false;
                }
            }
        }
    }
    return true;
}

bool getValidLists(map<int, vector<int>> &rules, const vector<vector<int>> &printerList, vector<vector<int>> &validListResult) {
    for(int i = 0; i < printerList.size(); i++) {
        if(satisfyConstraint(rules, printerList[i])) {
            validListResult.push_back(printerList[i]);
        }
    }
    return true;
}

int getSumOfMiddleNumbers(vector<vector<int>> &validResultLines) {
    int sum = 0;
    for(int i = 0; i < validResultLines.size(); i++) {
        if(validResultLines[i].size() % 2 == 0) {
            printf("Error: Even number of list items\n");
        }
        sum += validResultLines[i][(validResultLines[i].size() /2)];
    }
    return sum;
}

int main() {
    string inputFileName = FILENAME01;

    map<int, vector<int>> constraints;
    vector<vector<int>> printLists;
    vector<vector<int>> validLists;
    readDataFile(inputFileName, constraints, printLists);
    getValidLists(constraints, printLists, validLists);
    int result = getSumOfMiddleNumbers(validLists);
    printf("Result: Sum %i\n", result);
    return 0;
}