/*
* Advent of Code Day 10
 * Part 01
 * Deepak Shenoy
 *
 */

#include <iostream>
#include <fstream>

#define FILENAME01 "../input.txt"
#define FILENAME02 "../test_data.txt"

using namespace std;

bool readFile(string fileName, vector<string> &inputData) {
    fstream inputFile(fileName);
    string line;
    while (!inputFile.eof()) {
        getline(inputFile, line);
        inputData.push_back(line);
    }
    return true;
}

bool checkAtXY(int x, int y, char c, vector<string> &inputData) {
    if (x < 0 || y < 0) return false;
    if (x > inputData[0].size()) return false;
    if (y > inputData.size()) return false;
    char ch = inputData[y][x];
    if (ch != c) return false;
    return true;
}

bool checkLeft(int x, int y, char c, vector<string> &inputData) {
    return checkAtXY(x - 1, y, c, inputData);
}

bool checkRight(int x, int y, char c, vector<string> &inputData) {
    return checkAtXY(x + 1, y, c, inputData);
}

bool checkUp(int x, int y, char c, vector<string> &inputData) {
    return checkAtXY(x, y - 1, c, inputData);
}

bool checkDown(int x, int y, char c, vector<string> &inputData) {
    return checkAtXY(x, y + 1, c, inputData);
}

int isValidTrail(int x, int y, char ch, vector<string> &inputData, int startX, int startY, vector<tuple<tuple<int, int>, tuple<int, int>>> &foundTrails) {
    int score = 0;
    ch = ch + 1;
    if (ch == ('9' + 1)) {
        foundTrails.push_back(make_tuple(make_tuple(startX, startY), make_tuple(x, y)));
        score = 1;
    }
    if (checkLeft(x, y, ch, inputData)) score += isValidTrail(x - 1, y, ch, inputData, startX, startY, foundTrails);
    if (checkRight(x, y, ch, inputData)) score +=  isValidTrail(x + 1, y, ch, inputData, startX, startY, foundTrails);
    if (checkDown(x, y, ch, inputData)) score +=  isValidTrail(x, y + 1, ch, inputData, startX, startY, foundTrails);
    if (checkUp(x, y, ch, inputData)) score +=  isValidTrail(x, y - 1, ch, inputData, startX, startY, foundTrails);
    return score;
}

int countTrails(vector<string> &inputData) {
    int count = 0;
    for (int y = 0; y < inputData.size(); y++) {
        for (int x = 0; x < inputData[0].size(); x++) {
            int trailScore = 0;
            vector<tuple<tuple<int, int>, tuple<int, int>>> trails;
            if (checkAtXY(x, y, '0', inputData)) {
                trailScore = isValidTrail(x, y, '0', inputData, x, y, trails);
            }
            sort(trails.begin(), trails.end());
            auto it = unique(trails.begin(), trails.end());
            trails.erase(it, trails.end());
            //printf("Trailscore: %i\n", trails.size());
            count += trails.size();
        }
    }
    return count;
}

int main() {
    vector<string> terrainData;
    readFile(FILENAME01, terrainData);
    int result = countTrails(terrainData);
    printf("Result: %i\n", result);
    return 0;
}