/*
* Advent of Code Day 08
 * Part 02
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

int findAntiNodes(map<char, vector<Coordinate>>& coordinates, vector<string> dataMap, vector<Coordinate> &uniqueCoordinates) {
    GridCheck gridCheck(dataMap);
    int uniqueLocations = 0;
    for(map<char, vector<Coordinate>>::iterator i = coordinates.begin(); i != coordinates.end(); i++ ) {
        vector<Coordinate> coordinateList = i->second;
        for(vector<Coordinate>::iterator j = coordinateList.begin(); j != coordinateList.end() - 1; j++) {
            for(vector<Coordinate>::iterator k = j + 1; k != coordinateList.end(); k++) {
                int jx = j->x; int jy = j->y; int kx = k->x; int ky = k->y;
                bool keepScanning1 = true; bool keepScanning2 = true;
                int xDiff = k->x - j->x;
                int yDiff = k->y - j->y;
                while(keepScanning1 || keepScanning2) {
                    if(j->x == k->x) {
                        jy--;
                        if((keepScanning1 = gridCheck.isInGrid(j->x, jy))) {
                            addCoordinate(Coordinate(j->x, jy), uniqueCoordinates);
                        }
                        ky++;
                        if((keepScanning2 = gridCheck.isInGrid(k->x, ky))) {
                            addCoordinate(Coordinate(k->x, ky), uniqueCoordinates);
                        }
                        continue;
                    }
                    if(k->y == j->y) {
                        jx--;
                        if((keepScanning1 = gridCheck.isInGrid(jx, j->y))) {
                            addCoordinate(Coordinate(jx, j->y), uniqueCoordinates);
                        }
                        kx++;
                        if((keepScanning2 = gridCheck.isInGrid(kx, k->y))) {
                            addCoordinate(Coordinate(kx, k->y), uniqueCoordinates);
                        }
                        continue;
                    }
                    if(xDiff > 0 && yDiff > 0) {
                        jx-=xDiff;
                        jy-=yDiff;
                        if((keepScanning1 = gridCheck.isInGrid(jx, jy))) {
                            addCoordinate(Coordinate(jx, jy), uniqueCoordinates);
                        }
                        kx+=xDiff;
                        ky+=yDiff;
                        if((keepScanning2 = gridCheck.isInGrid(kx, ky))) {
                            addCoordinate(Coordinate(kx, ky), uniqueCoordinates);
                        }
                        continue;
                    }
                    if(xDiff < 0 && yDiff > 0) {
                        jx+=abs(xDiff);
                        jy-=yDiff;
                        if((keepScanning1 = gridCheck.isInGrid(jx, jy))) {
                            addCoordinate(Coordinate(jx, jy), uniqueCoordinates);
                        }
                        kx-=abs(xDiff);
                        ky+=yDiff;
                        if((keepScanning2 = gridCheck.isInGrid(kx, ky))) {
                            addCoordinate(Coordinate(kx, ky), uniqueCoordinates);
                        }
                        continue;
                    }
                }
                if(!keepScanning1 && !keepScanning2) continue;
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
    readDataFile(FILENAME01, dataMap);
    getCoordinates(coordinates, dataMap);
    vector<Coordinate> uniqueCoordinates;
    // Add all stations
    for (map<char, vector<Coordinate>>::iterator i = coordinates.begin(); i != coordinates.end(); i++) {
        uniqueCoordinates.insert(uniqueCoordinates.end(), i->second.begin(), i->second.end());
    }
    findAntiNodes(coordinates, dataMap, uniqueCoordinates);
    printf("Result: %lu\n", uniqueCoordinates.size());
    return 0;
}

// Test code
// vector<Coordinate> coordinateList = {
//     Coordinate(0,0), Coordinate(1,0), Coordinate(6,0),Coordinate(11,0),
//     Coordinate(1,1), Coordinate(3,1),
//     Coordinate(2,2),Coordinate(4,2), Coordinate(10,2),
//     Coordinate(2,3), Coordinate(3,3),
//     Coordinate(9,4),
//     Coordinate(1,5),Coordinate(5,5), Coordinate(11,5),
//     Coordinate(3,6), Coordinate(6,6),
//     Coordinate(0,7),Coordinate(5,7), Coordinate(7,7),
//     Coordinate(2,8),
//     Coordinate(4,9),
//     Coordinate(1,10),Coordinate(10,10),
//     Coordinate(3,11),Coordinate(10,11), Coordinate(11,11)
// };
//
// for (vector<Coordinate>::iterator i = coordinateList.begin(); i != coordinateList.end(); i++) {
//     int jj=0;
//     for (vector<Coordinate>::iterator j = uniqueCoordinates.begin(); j != uniqueCoordinates.end(); j++, jj++) {
//         if (j->x == i->x && j->y == i->y) {
//             uniqueCoordinates.erase(j);
//             break;
//         }
//     }
// }
