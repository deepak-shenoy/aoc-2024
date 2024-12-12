/*
* Advent of Code Day 04
 * Part 01
 * Deepak Shenoy
 *
 */

#include <cassert>
#include <iostream>
#include <fstream>
#include <cstring>

#define FILENAME01 "../input.txt"
#define FILENAME02 "../test_data.txt"
#define WORD__SIZE 4
#define WORD__XMAS "XMAS"
#define REVER_XMAS "SAMX"

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
        string token = "xxxx";
        if (getChatAtXY(x, y, data, &token[0]) &&
            getChatAtXY(x, y + 1, data, &token[1]) &&
            getChatAtXY(x, y + 2, data, &token[2]) &&
            getChatAtXY(x, y + 3, data, &token[3])) {
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
        string token = "xxxx";
        if (getChatAtXY(x, y, data, &token[0]) &&
            getChatAtXY(x, y - 1, data, &token[1]) &&
            getChatAtXY(x, y - 2, data, &token[2]) &&
            getChatAtXY(x, y - 3, data, &token[3])) {
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
        string token = "xxxx";
        if (getChatAtXY(x, y, data, &token[0]) &&
            getChatAtXY(x + 1, y + 1, data, &token[1]) &&
            getChatAtXY(x + 2, y + 2, data, &token[2]) &&
            getChatAtXY(x + 3, y + 3, data, &token[3])) {
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
        string token = "xxxx";
        if (getChatAtXY(x, y, data, &token[0]) &&
            getChatAtXY(x - 1, y + 1, data, &token[1]) &&
            getChatAtXY(x - 2, y + 2, data, &token[2]) &&
            getChatAtXY(x - 3, y + 3, data, &token[3])) {
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
        string token = "xxxx";
        if (getChatAtXY(x, y, data, &token[0]) &&
            getChatAtXY(x - 1, y - 1, data, &token[1]) &&
            getChatAtXY(x - 2, y - 2, data, &token[2]) &&
            getChatAtXY(x - 3, y - 3, data, &token[3])) {
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
        string token = "xxxx";
        if (getChatAtXY(x, y, data, &token[0]) &&
            getChatAtXY(x + 1, y - 1, data, &token[1]) &&
            getChatAtXY(x + 2, y - 2, data, &token[2]) &&
            getChatAtXY(x + 3, y - 3, data, &token[3])) {
            if(token.compare(WORD__XMAS)==0) return true;
            }
    } catch (exception e) {
        printf("Exception occurred (diagonal SE to NW): %s\n", e.what());
    }
    return false;
}

int main()
{
    testFunctions();

    vector<string> dataGrid;
    readData(FILENAME01, &dataGrid);
    return 0;
}


bool testForwardAndReverseSearch() {
    vector<string> dataGridTest = {
        "....XMAS",                // 1
        "....SAMX",                // 2
        "XMAS....",                // 3
        "SAMX....",                // 4
        ".XMAS...",                // 5
        "..SAMX..",                // 6
        "...XMAS.",                // 7
        "...SAMX.",                // 8
        "XMASXMAS",                // 9
        "SAMX.SAMXSAMX...SAMX",    // 10
        ".SAMX...........SAMX.",   // 11
        "XMAS.XMASXMAS...XMAS"     // 12
    };
    printf("(1)  Forward test:  should be true:   %i\n", isForwards(5,1, &dataGridTest));
    printf("(2)  Forward test:  should be false:  %i\n", isForwards(5,2, &dataGridTest));
    printf("(3)  Forward test:  should be false:  %i\n", isForwards(6,2, &dataGridTest));
    printf("(4)  Backward test: should be false:  %i\n", isBackwards(5,3, &dataGridTest));
    printf("(5)  Backward test: should be true:   %i\n", isBackwards(4,4, &dataGridTest));
    printf("(6)  Forward test:  should be true:   %i\n", isForwards(2,5, &dataGridTest));
    printf("(7)  Forward test:  should be false:  %i\n", isBackwards(2,5, &dataGridTest));
    printf("(8)  Backward test: should be true:   %i\n", isBackwards(6,6, &dataGridTest));
    printf("(9)  Forward test:  should be true:   %i\n", isForwards(4,7, &dataGridTest));
    printf("(10) Forward test:  should be false:  %i\n", isBackwards(4,7, &dataGridTest));
    printf("(11) Backward test: should be true:   %i\n", isBackwards(7,8, &dataGridTest));
    printf("(12) Backward test: should be false:  %i\n", isForwards(9,8, &dataGridTest));
    printf("(13) Backward test: should be false:  %i\n", isBackwards(0,8, &dataGridTest));
    printf("(14) Backward test: should be false:  %i\n", isBackwards(0,10, &dataGridTest));
    int findCount = 0;
    for(int i = - 3; i < 20; i++) {
        if(isForwards(i,1, &dataGridTest) == 1) findCount++;
    }
    printf("(15) Forward test: should be true:    %i (count=%i)\n", findCount == 1, findCount);

    findCount = 0;
    for(int i = - 3; i < 30; i++) {
        if(isBackwards(i,10, &dataGridTest) == 1) findCount++;
    }
    printf("(16) Backward test: should be false:  %i (count=%i)\n", findCount == 0, findCount);

    findCount = 0;
    for(int i = - 3; i < 30; i++) {
        if(isBackwards(i,50, &dataGridTest) == 1) findCount++;
    }
    printf("(17) Backward test: should be true:   %i (count=%i)\n", findCount == 0, findCount);

    findCount = 0;
    for(int i = 30; i > -3; i--) {
        if(isBackwards(i,11, &dataGridTest) == 1) findCount++;
    }
    printf("(18) Backward test: should be true:   %i (count=%i)\n", findCount == 2, findCount);

    findCount = 0;
    for(int i = 30; i > -3; i--) {
        if(isForwards(i,12, &dataGridTest) == 1) findCount++;
    }
    printf("(19) Backward test: should be true:   %i (count=%i)\n", findCount == 4, findCount);
    return true;
}

bool testDiagonalFunctions() {
    vector<string> dataGridTest = {
        ".X..SX.....X.S....",           // 1
        "..MA.M....M..A....X",          // 2
        "..MASA...A...M....M",          // 3
        ".XAASS..S....X....A",          // 4
        ".MM..?.......S....S.",         // 5
        "XX.........S.SS",               // 6
        "M..........A.SAA",           // 7
        "A..........M.A.MM",           // 8
        "S..S.S.....X.M..XX",           // 9
        "..A..A.......X...M..",         // 10
        ".M...M...........A.",          // 11
        "X....X...........S"            // 12
    };

    printf("(1)  NW->SE:  should be true:   %i\n", diagonalNWtoSE(2,1, &dataGridTest));
    printf("(2)  NE->SW:  should be true:   %i\n", diagonalNEtoSW(12,1, &dataGridTest));
    printf("(3)  NE->SW:  should be true:   %i\n", diagonalSWtoNE(2,4, &dataGridTest));
    printf("(4)  SW->NE:  should be true:   %i\n", diagonalSWtoNE(2,6, &dataGridTest));
    printf("(5)  SE->NW:  should be true:   %i\n", diagonalSEtoNW(18,9, &dataGridTest));
    printf("(6)  SW->NE:  should be true:   %i\n", diagonalSWtoNE(1,12, &dataGridTest));

    printf("(7)  NW->SE:  should be false:  %i\n", diagonalNWtoSE(3,1, &dataGridTest));
    printf("(8)  NE->SW:  should be false:  %i\n", diagonalNEtoSW(30,1, &dataGridTest));
    printf("(9)  NE->SW:  should be false:  %i\n", diagonalSWtoNE(2,40, &dataGridTest));
    printf("(10) SW->NE:  should be false:  %i\n", diagonalSWtoNE(2,7, &dataGridTest));
    printf("(11) SE->NW:  should be false:  %i\n", diagonalSEtoNW(-1,9, &dataGridTest));
    printf("(12) SW->NE:  should be false:  %i\n", diagonalSWtoNE(3,12, &dataGridTest));

}

bool testUpAndDown() {
    vector<string> dataGridTest = {
        ".....X.......S....",           // 1
        "..X..M.......A....X",          // 2
        "..M..A.......M....M",          // 3
        "..A..S.......X....A",          // 4
        "..S..?.......S....S.",         // 5
        "X..........S..",               // 6
        "M..........A.S....",           // 7
        "A..........M.A....",           // 8
        "S....S.....X.M...X",           // 9
        ".....A.......X...M..",         // 10
        ".....M...........A.",          // 11
        ".....X...........S"            // 12
    };

    printf("(1)  Top down:  should be true:   %i\n", isTopDown(6,1, &dataGridTest));
    printf("(2)  Down Up:   should be false:  %i\n", isDownUp(1,1, &dataGridTest));
    printf("(3)  Top down:  should be true:   %i\n", isTopDown(3,2, &dataGridTest));
    printf("(4)  Top down:  should be true:   %i\n", isTopDown(19,2, &dataGridTest));
    printf("(5)  Down Up:   should be true:   %i\n", isDownUp(14,4, &dataGridTest));
    printf("(6)  Top down:  should be false:  %i\n", isTopDown(20,5, &dataGridTest));
    printf("(7)  Top down:  should be true:   %i\n", isTopDown(1,6, &dataGridTest));
    printf("(8)  Down Up:   should be true:   %i\n", isDownUp(12,9, &dataGridTest));
    printf("(9)  Top down:  should be true:   %i\n", isTopDown(18,9, &dataGridTest));
    printf("(10) Down Up:   should be true:   %i\n", isDownUp(12,9, &dataGridTest));
    printf("(11) Down Up:   should be true:   %i\n", isDownUp(6,12, &dataGridTest));
    printf("(12) Down Up:   should be false:  %i\n", isDownUp(1,12, &dataGridTest));
    return true;
}

bool testFunctions() {
    printf("=================================================================\n");
    printf("Begin Tests....\n");
    printf("Horizontal\n\n");
    testForwardAndReverseSearch();
    printf("\nVertical\n\n");
    testUpAndDown();
    printf("\nDiagonal\n\n");
    testDiagonalFunctions();
    printf("End Tests....\n");
    printf("=================================================================\n\n");
    return true;
}
