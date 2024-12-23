/*
* Advent of Code Day 06
 * Part 01
 * Deepak Shenoy
 *
 */

#include <iostream>
#include <fstream>

#define FILENAME01 "../input.txt"
#define FILENAME02 "../test_data.txt"
#define _OBSTACLE1 '#'
#define ___VISITED 'X'
#define _____EMPTY '.'
#define START_CHAR '^'

using namespace std;

bool readFileData(string fileName, vector<string> &inputTerrainData) {
    fstream inputFile(fileName);
    if (!inputFile.is_open()) {
        printf("Error: Could not open file %s\n", fileName.c_str());
        exit(-1);
    }
    string line;
    while(!inputFile.eof()) {
        getline(inputFile, line);
        inputTerrainData.push_back(line);
    }
    return true;
}

bool findStartCoordinates(vector<string> &inputTerrainData, int &x, int &y) {
    for (int i = 0; i < inputTerrainData.size(); i++) {
        string *line = &inputTerrainData[i];
        for (int j = 0; j < line->size(); j++) {
            if (line->at(j) == START_CHAR) {
                line->at(j) = _____EMPTY;
                x = j;
                y = i;
                return true;
            }
        }
    }
    return false;
}

bool moveUp(vector<string> &inputTerrainData, int &x, int &y, int &score) {
    for(int i = y; i > 0; i--) {
        string *nextLine = &inputTerrainData[i -1];
        char nextItem = nextLine->at(x);
        string *currentLine = &inputTerrainData[i];
        char currentItem = currentLine->at(x);
        if(currentItem != ___VISITED) {
            score++;
            currentLine->at(x) = ___VISITED;
        }
        if (nextItem == _OBSTACLE1) {
            y = i;
            return false;
        }
    }
    return true;
}

bool moveDown(vector<string> &inputTerrainData, int &x, int &y, int &score) {
    for(int i = y; i < inputTerrainData.size() - 1; i++) {
        string *nextLine = &inputTerrainData[i + 1];
        string *currentLine = &inputTerrainData[i];
        char nextItem = nextLine->at(x);
        char currentItem = currentLine->at(x);
        if(currentItem != ___VISITED) {
            score++;
            currentLine->at(x) = ___VISITED;
        }
        if (nextItem == _OBSTACLE1) {
            y = i;
            return false;
        }
    }
    return true;
}

bool moveRight(vector<string> &inputTerrainData, int &x, int &y, int &score) {
    string *currentLine = &inputTerrainData[y];
    for(int i = x; i < currentLine->size() - 1; i++) {
        char nextItem = currentLine->at(i + 1);
        char currentItem = currentLine->at(i);
        if(currentItem != ___VISITED) {
            score++;
            currentLine->at(i) = ___VISITED;
        }
        if (nextItem == _OBSTACLE1) {
            x = i;
            return false;
        }
    }
    return true;
}

bool moveLeft(vector<string> &inputTerrainData, int &x, int &y, int &score) {
    string *currentLine = &inputTerrainData[y];
    for(int i = x; i > 0; i--) {
        char nextItem = currentLine->at(i - 1);
        char currentItem = currentLine->at(i);
        if(currentItem != ___VISITED) {
            score++;
            currentLine->at(i) = ___VISITED;
        }
        if (nextItem == _OBSTACLE1) {
            x = i;
            return false;
        }
    }
    return true;
}

int main()
{
    vector<string> terrainData;
    int x, y, score = 1;
    readFileData(FILENAME01, terrainData);
    if (!findStartCoordinates(terrainData, x, y)) {
        printf("Error: Could not find start coordintes\n");
        exit(-1);
    }
    bool outsideGrid = false;
    int direction = 90;
    while(!outsideGrid) {
        if (direction == 90 && !outsideGrid) {
            outsideGrid = moveUp(terrainData, x, y, score);
            if (!outsideGrid) direction = 180;
        }
        if (direction == 180 && !outsideGrid) {
            outsideGrid = moveRight(terrainData, x, y, score);
            if (!outsideGrid) direction = 270;
        }
        if (direction == 270 && !outsideGrid) {
            outsideGrid = moveDown(terrainData, x, y, score);
            if (!outsideGrid) direction = 360;
        }
        if (direction == 360 && !outsideGrid) {
            outsideGrid = moveLeft(terrainData, x, y, score);
            if (!outsideGrid) direction = 90;
        }
    }
    printf("Score: %i\n", score);
    return 0;

}
