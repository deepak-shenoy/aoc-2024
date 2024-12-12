/*
* Advent of Code Day 04
 * Part 02
 * Deepak Shenoy
 *
 */

#include <cassert>
#include <iostream>
#include <fstream>
#include <cstring>

#define FILENAME01 "../input.txt"
#define FILENAME02 "../test_data.txt"
#define WORD__SIZE 3
#define WORD__XMAS "MAS"
#define REVER_XMAS "SAM"

using namespace std;

bool testFunctions();

void readData(const string fileName, vector<string> *data) {
    ifstream inputFile(fileName);
    if(!inputFile.is_open()) {
        cout << "Error opening file " << fileName << endl;
        exit(1);
    }
    string line;
    while(!inputFile.eof()) {
        getline(inputFile, line);
        data->push_back(line);
    }
    inputFile.close();
}

// Indexes start at 1
bool getChatAtXY(const int x, const int y, const vector<string> *data, char *result) {
    if(y>data->size()) {
        cout<<"Y is out of bounds" << endl;
        return false;
    }
    string line = data->at(y - 1);
    if(x>line.size()) {
        cout<<"X is out of bounds" << endl;
        return false;
    }
    *result = line[x - 1];
    return true;
}

// Indexes start at 1
bool isLetterA(const int x, const int y, const vector<string> *data) {
    if(y>data->size()) {
        cout<<"Y is out of bounds" << endl;
        return false;
    }
    string line = data->at(y - 1);
    if(x>line.size()) {
        cout<<"X is out of bounds" << endl;
        return false;
    }
    char letter = line[x - 1];
    if (letter == 'a' || letter == 'A') {
        return true;
    }
    return false;
}

// Indexes start at 1
bool isForwards(const int x, const int y, const vector<string> *data) {
    try {
        if (y < 1 || x < 1 || y>data->size()) {
            return false;
        }
        string line = data->at(y - 1);
        if(x + WORD__SIZE - 1 > line.size()) {
            return false;
        }
        if(line.substr((x -1), WORD__SIZE).compare(WORD__XMAS) == 0) {
            return true;
        }

    } catch (exception e) {
        printf("Exception occurred (isForward): %s\n", e.what());
    }
    return false;
}

bool isBackwards(const int x, const int y, const vector<string> *data) {
    try {
        if (y < 1 || x < 1 || y>data->size()) {
            return false;
        }
        string line = data->at(y - 1);
        if(x - WORD__SIZE < 0) {
            return false;
        }
        if(x > line.size()) return false; // Gone past line
        if(line.substr(x - WORD__SIZE, WORD__SIZE).compare(REVER_XMAS) == 0) {
            return true;
        }
    } catch (exception e) {
        printf("Exception occurred (isBackward): %s\n", e.what());
        throw;
    }
    return false;
}

bool isTopDown(const int x, const int y, const vector<string> *data) {
    try {
        if (y < 1 || x < 1 || y + WORD__SIZE -1 > data->size()) {
            return false;
        }
        string token = "xxx";
        if (getChatAtXY(x, y, data, &token[0]) &&
            getChatAtXY(x, y + 1, data, &token[1]) &&
            getChatAtXY(x, y + 2, data, &token[2])) {
            if(token.compare(WORD__XMAS)==0) return true;
        }
    } catch (exception e) {
        printf("Exception occurred (top down): %s\n", e.what());
    }
    return false;
}

bool isDownUp(const int x, const int y, const vector<string> *data) {
    try {
        if (y < 1 || x < 1 || y - WORD__SIZE < 0) {
            return false;
        }
        string token = "xxx";
        if (getChatAtXY(x, y, data, &token[0]) &&
            getChatAtXY(x, y - 1, data, &token[1]) &&
            getChatAtXY(x, y - 2, data, &token[2])) {
            if(token.compare(WORD__XMAS)==0) return true;
            }
    } catch (exception e) {
        printf("Exception occurred (top down): %s\n", e.what());
    }
    return false;
}

bool diagonalNWtoSE(const int x, const int y, const vector<string> *data) {
    try {
        if (y < 1 || x < 1 || y + WORD__SIZE -1 > data->size()) {
            return false;
        }
        string token = "xxx";
        if (getChatAtXY(x, y, data, &token[0]) &&
            getChatAtXY(x + 1, y + 1, data, &token[1]) &&
            getChatAtXY(x + 2, y + 2, data, &token[2])) {
            if(token.compare(WORD__XMAS)==0) return true;
            }
    } catch (exception e) {
        printf("Exception occurred (diagonal NW to SE): %s\n", e.what());
    }
    return false;
}

bool diagonalNEtoSW(const int x, const int y, const vector<string> *data) {
    try {
        if (y < 1 || x < 1 || y + WORD__SIZE -1 > data->size()) {
            return false;
        }
        string token = "xxx";
        if (getChatAtXY(x, y, data, &token[0]) &&
            getChatAtXY(x - 1, y + 1, data, &token[1]) &&
            getChatAtXY(x - 2, y + 2, data, &token[2])) {
            if(token.compare(WORD__XMAS)==0) return true;
            }
    } catch (exception e) {
        printf("Exception occurred (diagonal NE to SW): %s\n", e.what());
    }
    return false;
}

bool diagonalSEtoNW(const int x, const int y, const vector<string> *data) {
    try {
        if (y < 1 || x < 1 || y - WORD__SIZE < 0) {
            return false;
        }
        string token = "xxx";
        if (getChatAtXY(x, y, data, &token[0]) &&
            getChatAtXY(x - 1, y - 1, data, &token[1]) &&
            getChatAtXY(x - 2, y - 2, data, &token[2])) {
            if(token.compare(WORD__XMAS)==0) return true;
            }
    } catch (exception e) {
        printf("Exception occurred (diagonal SE to NW): %s\n", e.what());
    }
    return false;
}

bool diagonalSWtoNE(const int x, const int y, const vector<string> *data) {
    try {
        if (y < 1 || x < 1 || y - WORD__SIZE < 0) {
            return false;
        }
        string token = "xxx";
        if (getChatAtXY(x, y, data, &token[0]) &&
            getChatAtXY(x + 1, y - 1, data, &token[1]) &&
            getChatAtXY(x + 2, y - 2, data, &token[2])) {
            if(token.compare(WORD__XMAS)==0) return true;
            }
    } catch (exception e) {
        printf("Exception occurred (diagonal SE to NW): %s\n", e.what());
    }
    return false;
}

int main()
{
    // testFunctions();

    vector<string> dataGrid;
    readData(FILENAME01, &dataGrid);

    int score = 0;
    for(int y = 1; y <= dataGrid.size(); y++) {
        string line = dataGrid.at(y - 1);
        int lineScore = 0; // For debugging
        for (int x = 1; x <= line.size(); x++) {
            int foundAtCoordinate = 0;
            if (isLetterA(x, y, &dataGrid)) {
                if (diagonalNWtoSE(x - 1, y - 1, &dataGrid)) foundAtCoordinate++;
                if (diagonalNEtoSW(x + 1, y - 1, &dataGrid)) foundAtCoordinate++;
                if (diagonalSEtoNW(x + 1, y + 1, &dataGrid)) foundAtCoordinate++;
                if (diagonalSWtoNE(x - 1, y + 1, &dataGrid)) foundAtCoordinate++;
            }
            if (foundAtCoordinate == 2) {
                lineScore ++;
            } else if (foundAtCoordinate > 1) {
                printf("Error - should have detected only two patterns at (%i, %i)\n", x, y);
            }
        }
        score += lineScore;
    }
    printf("Total score:  %i\n", score);
    return 0;
}
