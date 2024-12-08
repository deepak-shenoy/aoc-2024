/*
* Advent of Code Day 02
 * Part 01
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

int countSafeReports(vector<vector<int>> input) {
    int count = 0;
    int difference;
    for(int i = 0; i < input.size(); i++) {
        int direction;
        if(input[i][0]==input[i][1]) continue; // Not trending up or down
        if(input[i][0] > input[i][1]) direction = MAX___DIFF; else direction = -MAX___DIFF;
        int numberOfValidNumbers = 0;
        for(int j = 0; j < input[i].size() -1 ; j++) {
            difference = input[i][j] - input[i][j+1];
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
        if(numberOfValidNumbers == (input[i].size() - 1)) count++;
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
