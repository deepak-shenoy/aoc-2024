/*
* Advent of Code Day 02
 * Part 02
 * Deepak Shenoy
 *
 */

#include <iostream>
#include <fstream>
#include <sstream>

#define FILENAME01 "../input.txt"
#define FILENAME02 "../test_data.txt"

#define MAX__LINES 1000
#define MAX_LEVELS 5
#define MAX___DIFF 3

using namespace std;

bool readFile(const string fileName, vector<vector<int>> *input) {
    ifstream inputFile(fileName);
    if(!inputFile.is_open()) {
        cout << "Error opening file " << fileName << endl;
        return false;
    }
    string line;
    int dataItem;
    for(int i = 0; !inputFile.eof(); i++) {
        getline(inputFile, line);
        istringstream ss(line);
        vector<int> dataLine;
        for(int j = 0; !ss.eof(); j++) {
            ss >> dataItem;
            dataLine.push_back(dataItem);
        }
        input->push_back(dataLine);
    }
    return true;
}

bool isValidSequence(const int direction, const int firstCell, const int secondCell) {
    int difference = firstCell - secondCell;
    if(direction>0) {
        if(difference !=0 && difference <= MAX___DIFF && difference > 0) {
            return true;
        }
    } else {
        if(difference !=0 && difference >= -MAX___DIFF&& difference < 0) {
            return true;
        }
    }
    return false;
}

bool isLineValid(vector<int> line) {
    int numberOfValidNumbers = 0;
    int direction;
    if(line[0]==line[1]) return false; // Not trending up or down
    if(line[0] > line[1]) direction = MAX___DIFF; else direction = -MAX___DIFF;
    for(int j = 0; j < line.size() -1 ; j++) {
        int difference = line[j] - line[j+1];
        if(direction>0) {
            if(difference !=0 && difference <= MAX___DIFF && difference > 0) {
                numberOfValidNumbers++;
            }
        } else {
            if(difference !=0 && difference >= -MAX___DIFF&& difference < 0) {
                numberOfValidNumbers++;
            }
        }
    }
    if(numberOfValidNumbers == (line.size() - 1)) return true;
    return false;
}

int countSafeReports(vector<vector<int>> input) {
    int count = 0;
    for(int i = 0; i < input.size(); i++) {
        vector<int> line = input[i];
        if(isLineValid(line)) {
            count++;
        } else {
            for(int j = 0; j < line.size() ; j++) {
                vector<int> lineCopy = line;
                lineCopy.erase(lineCopy.begin() + j);
                if(isLineValid(lineCopy)) {
                    count++;
                    break;
                }
            }
        }
    }
    return count;
}

int main() {
    vector<vector<int>> inputData;
    readFile(FILENAME01, &inputData);
    int result = countSafeReports(inputData);
    cout << "Result: "<< result << endl;
    return 0;
}
