/*
* Advent of Code Day 12
 * Part 01
 * Deepak Shenoy
 *
 */

#include <iostream>
#include <fstream>

#define FILENAME01 "../input.txt"
#define FILENAME02 "../test_data.txt"

using namespace std;

bool readInputFile(const string &fileName, vector<string> &inputData) {
    fstream inputFile(fileName);
    string line;
    while (!inputFile.eof()) {
        getline(inputFile, line);
        inputData.push_back(line);
    }
    return true;
}

char getValueAtXY(int x, int y, vector<string> &inputData) {
    return inputData[y][x];
}

bool inBounds(int x, int y, vector<string> &inputData) {
    if (x < 0 || x >= inputData[0].size() || y < 0 || y >= inputData.size()) return false;
    // Inside main area
    return true;
}

// Checks if we have visited that coordinate for a valid record
bool hasVisited(int x, int y, vector<tuple<int, int>> &visitedValues) {
    for (vector<tuple<int, int>>::iterator i = visitedValues.begin(); i != visitedValues.end(); i++) {
        if (get<0>(*i) == x && get<1>(*i) == y) {
            return true;
        }
    }
    return false;
}

bool addRegion(int x, int y, vector<tuple<int, int>> &regionList) {
    for (vector<tuple<int, int>>::iterator i = regionList.begin(); i < regionList.end(); i++) {
        if (get<0>(*i) == x && get<1>(*i) == y) return false;
    }
    regionList.push_back(tuple<int, int>(x, y));
    return true;
}

bool getImmediateConnectedRegions(int x, int y, char ch, vector<string> &inputData, vector<tuple<int, int>> &immediateRegions, vector<tuple<int, int>> &visitedValues) {
    if (inBounds(x - 1, y, inputData) &&  getValueAtXY(x - 1, y, inputData) == ch && !hasVisited(x - 1, y, visitedValues)) {
        addRegion(x - 1, y, immediateRegions);
    }
    if (inBounds(x + 1, y, inputData) &&  getValueAtXY(x + 1, y, inputData) == ch && !hasVisited(x + 1, y, visitedValues)) {
        addRegion(x + 1, y, immediateRegions);
    }
    if (inBounds(x, y - 1, inputData) &&  getValueAtXY(x, y - 1, inputData) == ch && !hasVisited(x, y - 1, visitedValues)) {
        addRegion(x, y - 1, immediateRegions);
    }
    if (inBounds(x, y + 1, inputData) &&  getValueAtXY(x, y + 1, inputData) == ch && !hasVisited(x, y + 1, visitedValues)) {
        addRegion(x, y + 1, immediateRegions);
    }
    return true;
}

bool getRegion(int x, int y, vector<string> &inputData, vector<tuple<int, int>> &visitedValues, vector<tuple<int, int>> &foundRegion) {
    vector<tuple<int, int>> WIP_Region = vector<tuple<int, int>>({make_tuple(x, y)});
    char regionCode = getValueAtXY(x, y, inputData);
    while (WIP_Region.size() > 0) {
        vector<tuple<int, int>> additionalRegions;
        for (vector<tuple<int, int>>::iterator i = WIP_Region.begin(); i != WIP_Region.end(); i++) {
            // Final region result
            if (!hasVisited(get<0>(*i), get<1>(*i), visitedValues)) addRegion(get<0>(*i), get<1>(*i), foundRegion);
            // Mark our reference regions as visited (new region have not been visited yet)
            addRegion(get<0>(*i), get<1>(*i), visitedValues);
            // Add new regions around current connected regions to the list we need to search further
            getImmediateConnectedRegions(get<0>(*i), get<1>(*i), regionCode, inputData, additionalRegions, visitedValues);
        }
        //visitedValues.insert(visitedValues.end(), WIP_Region.begin(), WIP_Region.end());
        WIP_Region = additionalRegions;
    }
    return true;
}

bool findRegions(vector<vector<tuple<int, int>>> &regions, vector<tuple<int, int>> &visited, vector<string> &inputGrid) {
    for (int y = 0; y < inputGrid.size(); y++) {
        for (int x = 0; x < inputGrid[0].size(); x++) {
            vector<tuple<int, int>> newRegion;
            getRegion(x, y, inputGrid, visited, newRegion);
            if (newRegion.size() > 0) regions.push_back(newRegion);
        }
    }
    return true;
}

int howManyEdgesNeeded(vector<tuple<int, int>> &region, vector<string> &inputData) {
    int totalEdgesNeeded = 0;
    for (vector<tuple<int, int>>::iterator i = region.begin(); i != region.end(); i++) {
        int x = get<0>(*i); int y = get<1>(*i);
        int edgesNeeded = 4;
        for (vector<tuple<int, int>>::iterator j = region.begin(); j != region.end(); j++) {
            if (get<0>(*j) == x - 1 && get<1>(*j) == y) edgesNeeded--; // Left member found
            if (get<0>(*j) == x + 1 && get<1>(*j) == y) edgesNeeded--; // Right member found
            if (get<0>(*j) == x && get<1>(*j) == y + 1) edgesNeeded--; // Top member found
            if (get<0>(*j) == x && get<1>(*j) == y - 1) edgesNeeded--; // Bottom member found
        }
        totalEdgesNeeded += edgesNeeded;
    }
    return totalEdgesNeeded;
}

int getCost(vector<vector<tuple<int, int>>> &regions, vector<string> &inputData) {
    int totalCost = 0;
    for (vector<tuple<int, int>> region : regions) {
        int area = region.size();
        int perimeter = howManyEdgesNeeded(region, inputData);
        int itemCost = area * perimeter;
        printf("Area (%i) Perimeter (%i) \n", area, perimeter);
        totalCost += itemCost;
    }
    return totalCost;
}

int main() {
    vector<tuple<int, int>> visited;
    vector<string> inputGrid;
    readInputFile(FILENAME01, inputGrid);
    vector<vector<tuple<int, int>>> regions;
    findRegions(regions, visited, inputGrid);
    int result = getCost(regions, inputGrid);
    printf("Result: %i", result);
}