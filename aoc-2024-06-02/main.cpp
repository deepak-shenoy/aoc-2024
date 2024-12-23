/*
* Advent of Code Day 06
 * Part 02
 * Deepak Shenoy
 *
 */

#include <iostream>
#include <fstream>
#include <set>

#define FILENAME01 "../input.txt"
#define FILENAME02 "../test_data.txt"
#define _OBSTACLE1 '#'
#define ___VISITED 'X'
#define _____EMPTY '.'
#define START_CHAR '^'
#define PARADOX_CH 'O'

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
        if (nextItem == _OBSTACLE1 || nextItem == PARADOX_CH) {
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
        if (nextItem == _OBSTACLE1 || nextItem == PARADOX_CH) {
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
        if (nextItem == _OBSTACLE1 || nextItem == PARADOX_CH) {
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
        if (nextItem == _OBSTACLE1 || nextItem == PARADOX_CH) {
            x = i;
            return false;
        }
    }
    return true;
}

class Coordinate {
private:
    int x, y, direction;
public:
    Coordinate(int x, int y, int direction) : x(x), y(y), direction(direction) {}
    bool operator<(const Coordinate &other) const {
        if (x < other.x) { return true; };
        if (x == other.x && y < other.y) { return true; }
        if (x == other.x && y == other.y && direction < other.direction) { return true; }
        return false;
    }
};

bool coordinateExists(int x, int y, int direction, set<Coordinate> &coords) {
    if(!coords.contains(Coordinate(x, y, direction))) {
        coords.insert(Coordinate(x, y, direction));
        return false;
    }
    return true;

}

int main()
{
    vector<string> terrainData;
    int xStart, yStart, score = 1;
    readFileData(FILENAME01, terrainData);
    if (!findStartCoordinates(terrainData, xStart, yStart)) {
        printf("Error: Could not find start coordintes\n");
        exit(-1);
    }


    int loopCount = 0;
    for (int ay = 0; ay < terrainData.size(); ay++) {
        for (int ax = 0; ax < terrainData[ay].size(); ax++) {
            if(ay==yStart && ax==xStart) continue;

            int x = xStart;
            int y = yStart;

            set<Coordinate> coordinates;

            vector<string> terrainWorkingCopyData = terrainData;
            string *lineToAddObstacle = &terrainWorkingCopyData[ay];
            lineToAddObstacle->at(ax) = PARADOX_CH;

            bool outsideGrid = false;
            int direction = 90;

            //if(coordinates.contains()) {}

            while(!outsideGrid) {
                if (direction == 90 && !outsideGrid) {
                    if(coordinateExists(x, y, direction, coordinates)) {
                        loopCount++;
                        break;
                    };
                    outsideGrid = moveUp(terrainWorkingCopyData, x, y, score);
                    if (!outsideGrid) direction = 180;
                }
                if (direction == 180 && !outsideGrid) {
                    if(coordinateExists(x, y, direction, coordinates)) {
                        loopCount++;
                        break;
                    };
                    outsideGrid = moveRight(terrainWorkingCopyData, x, y, score);
                    if (!outsideGrid) direction = 270;
                }
                if (direction == 270 && !outsideGrid) {
                    if(coordinateExists(x, y, direction, coordinates)) {
                        loopCount++;
                        break;
                    };
                    outsideGrid = moveDown(terrainWorkingCopyData, x, y, score);
                    if (!outsideGrid) direction = 360;
                }
                if (direction == 360 && !outsideGrid) {
                    if(coordinateExists(x, y, direction, coordinates)) {
                        loopCount++;
                        break;
                    };
                    outsideGrid = moveLeft(terrainWorkingCopyData, x, y, score);
                    if (!outsideGrid) direction = 90;
                }
            }
        }
    }
    printf("Score: %i Loop Count: %i\n", score, loopCount);
    return 0;
}
