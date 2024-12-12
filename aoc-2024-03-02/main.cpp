/*
* Advent of Code Day 03
 * Part 02
 * Deepak Shenoy
 *
 */

#include <iostream>
#include <fstream>
#include <regex>

#define FILENAME01 "../input.txt"
#define FILENAME02 "../test_data.txt"

#define REG_EX_MUL_EXPR "mul\\([0-9]*\\,[0-9]*\\)"
#define REG_EX___PARAMS "([0-9]*)\\,([0-9]*)"
#define REG_EX_COMMANDS "((mul\\([0-9]*\\,[0-9]*\\))|(don't\\(\\))|(do\\(\\)))"
#define DO______COMMAND "do()"
#define DONT____COMMAND "don't()"

using namespace std;

static regex MULT_COMMAND(REG_EX_MUL_EXPR);
static regex PARAM_VALUES(REG_EX___PARAMS);
static regex ALL_COMMANDS(REG_EX_COMMANDS);

void getMatchesFromFile(string fileName, vector<string> *multCommands) {
    ifstream inputFile(fileName);
    // Cannot find file
    if(!inputFile.is_open()) {
        cerr << "Error - could not open file " << fileName << endl;
        exit(-1);
    }
    string line;
    while(!inputFile.eof()) {
        getline(inputFile, line);
        sregex_iterator it(line.begin(), line.end(), ALL_COMMANDS);
        sregex_iterator end;
        while (it != end) {
            smatch match = *it;
            multCommands->push_back(match.str());
            ++it;
        }
    }
}

int multiplyParams(vector<string> *multCommands) {
    int sum = 0;
    bool includeCalc = true;
    for(int i = 0; i < multCommands->size(); i++) {
        string line = multCommands->at(i);
        if(line.compare(DO______COMMAND) == 0) {
            includeCalc = true;
            continue;
        }
        if(line.compare(DONT____COMMAND) == 0) {
            includeCalc = false;
            continue;
        }
        sregex_iterator it(line.begin(), line.end(), PARAM_VALUES);
        sregex_iterator end;
        smatch match = *it;
        int firstParam = stoi(match[1]);
        int secondParam = stoi(match[2]);
        if(includeCalc) sum += (firstParam * secondParam);
    }
    return sum;
}

int main()
{
    vector<string> commands;
    getMatchesFromFile(FILENAME01, &commands);
    int result = multiplyParams(&commands);
    cout << "Results is: " << result << endl;
    return 0;
}