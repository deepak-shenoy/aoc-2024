/*
* Advent of Code Day 07
 * Part 02
 * Deepak Shenoy
 *
 */

#include <iostream>
#include <map>
#include <fstream>
#include <sstream>
#include <cmath>

#define FILENAME01 "../input.txt"
#define FILENAME02 "../test_data.txt"
#define NO_OF_OPER 2

using namespace std;

bool readData(string filename, map<long, vector<int>> &inputData) {
    string line;
    try {
        fstream inputFile(filename);
        while(!inputFile.eof()) {
            getline(inputFile, line);
            istringstream lineStream(line);
            string testValue;
            getline(lineStream, testValue, ':');
            string componentNumbers;
            vector<int> componentNumberList;
            while(!lineStream.eof()) {
                lineStream >> componentNumbers;
                componentNumberList.push_back(stoi(componentNumbers.c_str()));
            }
            if(inputData.contains(stol(testValue))) {
                printf("Error: test value already exists\n");
            }
            inputData.insert(make_pair(stol(testValue), componentNumberList));
        }
    } catch(exception &e) {
        printf("Error: could not read file.  Line is '%s'.  Error message: %s\n", line.c_str(), e.what());
        return false;
    }
    return true;
}

string itob3(int number, int numberOfOperators) {
    std::string baseThreeNumber = "";
    if (number == 0) {
        baseThreeNumber = "0";
    } else {
        while (number != 0) {
            int remainder = number % 3;
            baseThreeNumber += '0' + remainder;
            number /= 3;
        }
    }
    std::reverse(baseThreeNumber.begin(), baseThreeNumber.end());
    string result = string(numberOfOperators - baseThreeNumber.length(), '0') + baseThreeNumber;
    return result;
}

bool buildCalculationMatrix(vector<int> calibrationLine, vector<string> &matrixResult) {
    int numberOfOperators = calibrationLine.size() - 1;
    for (int i = 0; i < pow(3, numberOfOperators); i++) {
        string s = itob3(i, numberOfOperators);
        matrixResult.push_back(s);
    }
    return true;
}

bool isLineCalibratedCorrectly(long expectedResult, vector<int> calibrationLine) {
    vector<string> matrix;
    buildCalculationMatrix(calibrationLine, matrix);
    for(int i = 0; i < matrix.size(); i++) {
        string matrixLine = matrix[i];
        long total = calibrationLine[0];
        for(int j = 0; j < matrixLine.size(); j++) {
            if(matrixLine[j] == '0') total += (long) calibrationLine[j + 1];
            if(matrixLine[j] == '1') total *= (long) calibrationLine[j + 1];
            if(matrixLine[j] == '2') {
                string previous = to_string(total) + to_string(calibrationLine[j + 1]);
                total = stol(previous);
            }
        }
        if(total == expectedResult) return true;
    }
    return false;
}

int main()
{
    map<long, vector<int>> calibrationData;
    readData(FILENAME01, calibrationData);
    long result = 0;

    map<long, vector<int>>::iterator it;
    for(it = calibrationData.begin(); it != calibrationData.end(); it++) {
        bool valid = isLineCalibratedCorrectly(it->first, it->second);
        // printf("Result: %i %ld\n", valid, it->first);
        if(valid) result += (long) it->first;
    }
    printf("Result: %ld\n", result);

    return 0;
}
