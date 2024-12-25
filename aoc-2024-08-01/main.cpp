/*
* Advent of Code Day 08
 * Part 01
 * Deepak Shenoy
 *
 */

#include <iostream>
#include <fstream>
#include <map>

#define FILENAME01 "../input.txt"
#define FILENAME02 "../test_data.txt"

#define NO_ANTENNA '.'

using namespace std;

bool readDataFile(string fileName, vector<string>& inputDataFile) {
    fstream inputFile(fileName);
    if (!inputFile.is_open()) {
        printf("Error opening data file\n");
        exit(-1);
    }
    string line;
    while(!inputFile.eof()) {
        getline(inputFile, line);
        inputDataFile.push_back(line);
    }
    return true;
}

class Coordinate {
public:
    int x, y; // Easy access
    Coordinate(int x, int y): x{x}, y{y} {}
};

bool getCoordinates(map<char, vector<Coordinate>>& coordinates, vector<string>& inputDataFile) {
    for(int i = 0; i < inputDataFile.size(); i++) {
        string line = inputDataFile[i];
        for (int j = 0; j < line.size(); j++) {
            if (line[j] != NO_ANTENNA) {
                char antennaKey = line[j];
                if(coordinates.find(antennaKey) == coordinates.end()) {
                    coordinates.insert(make_pair(antennaKey, vector<Coordinate>({Coordinate(j, i)})));
                } else {
                    vector<Coordinate> currentList = coordinates[antennaKey];
                    currentList.push_back(Coordinate(j, i));
                    coordinates[antennaKey] = currentList;
                }
            }
        }
    }
    return true;
}

class GridCheck {
private:
    int maxX, maxY;
public:
    GridCheck(vector<string> dataMap) {
        maxX = dataMap[0].size();
        maxY = dataMap.size();
    }
    bool isInGrid(int x, int y) {
        return x < maxX && y < maxY && x >= 0 && y >= 0;
    }
};

bool addCoordinate(Coordinate coordinate, vector<Coordinate>& uniqueCoordinates) {
    for(vector<Coordinate>::iterator i = uniqueCoordinates.begin(); i != uniqueCoordinates.end(); i++) {
        if(coordinate.x == i->x && coordinate.y == i->y) return false;
    }
    uniqueCoordinates.push_back(coordinate);
    return true;
}

int findAntiNodes(map<char, vector<Coordinate>>& coordinates, vector<string> dataMap, vector<Coordinate>& uniqueCoordinates) {
    GridCheck gridCheck(dataMap);
    int uniqueLocations = 0;
    for(map<char, vector<Coordinate>>::iterator i = coordinates.begin(); i != coordinates.end(); i++ ) {
        vector<Coordinate> coordinateList = i->second;
        for(vector<Coordinate>::iterator j = coordinateList.begin(); j != coordinateList.end() - 1; j++) {
            for(vector<Coordinate>::iterator k = j + 1; k != coordinateList.end(); k++) {
                if(j->x == k->x) {
                    if(gridCheck.isInGrid(j->x, j->y - 1)) {
                        addCoordinate(Coordinate(j->x, j->y - 1), uniqueCoordinates);
                    }
                    if(gridCheck.isInGrid(k->x, k->y + 1)) {
                        addCoordinate(Coordinate(k->x, k->y + 1), uniqueCoordinates);
                    }
                    continue;
                }
                if(k->y == j->y) {
                    if(gridCheck.isInGrid(j->x - 1, j->y)) {
                        addCoordinate(Coordinate(j->x - 1, j->y), uniqueCoordinates);
                    }
                    if(gridCheck.isInGrid(k->x + 1, k->y)) {
                        addCoordinate(Coordinate(k->x + 1, k->y), uniqueCoordinates);
                    }
                    continue;
                }
                int xDiff = k->x - j->x;
                int yDiff = k->y - j->y;
                if(xDiff > 0 && yDiff > 0) {
                    if(gridCheck.isInGrid(j->x - xDiff, j->y - yDiff)) {
                        addCoordinate(Coordinate(j->x - xDiff, j->y - yDiff), uniqueCoordinates);
                    }
                    if(gridCheck.isInGrid(k->x + xDiff, k->y + yDiff)) {
                        addCoordinate(Coordinate(k->x + xDiff, k->y + yDiff), uniqueCoordinates);
                    }
                    continue;
                }
                if(xDiff < 0 && yDiff > 0) {
                    if(gridCheck.isInGrid(j->x + abs(xDiff), j->y - yDiff)) {
                        addCoordinate(Coordinate(j->x + abs(xDiff), j->y - yDiff), uniqueCoordinates);
                    }
                    if(gridCheck.isInGrid(k->x - abs(xDiff), k->y + yDiff)) {
                        addCoordinate(Coordinate(k->x - abs(xDiff), k->y + yDiff), uniqueCoordinates);
                    }
                    continue;
                }
                printf("Error: Missing use-case for coordinate check\n");
            }
        }
    }
    return uniqueLocations;
}

int main()
{
    vector<string> dataMap;
    vector<char> antennaCodes;
    map<char, vector<Coordinate>> coordinates;
    vector<Coordinate> uniqueCoordinates;
    readDataFile(FILENAME01, dataMap);
    getCoordinates(coordinates, dataMap);
    int result = findAntiNodes(coordinates, dataMap, uniqueCoordinates);
    printf("Result: %lu\n", uniqueCoordinates.size());
    return 0;
}
