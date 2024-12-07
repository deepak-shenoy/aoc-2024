/*
* Advent of Code Day 01
 * Part 02
 * Deepak Shenoy
 *
 */

#include <iostream>
#include <fstream>
#include <map>
#include <sstream>

#define FILENAME01 "../input.txt"
#define FILENAME02 "../test_data.txt"

#define MAX__LINES 1000

using namespace std;

int main()
{
    int lhs[MAX__LINES];
    map<int, int> rhs_map;

    ifstream inputFile(FILENAME01);
    if(!inputFile.is_open()) {
        cout << "Error opening file " << FILENAME01 << endl;
    }

    // Get both lists - lhs is a pure list but rhs is a count of occurances for rhs
    string line;
    int rhsKey;
    int keyValue =0;
    for (int i = 0; i < MAX__LINES && !inputFile.eof(); i++) {
        getline(inputFile, line);
        istringstream ss(line);
        ss >> lhs[i] >> rhsKey;
        if(rhs_map.find(rhsKey) != rhs_map.end()) {
            keyValue = rhs_map[rhsKey];
            rhs_map[rhsKey] = ++keyValue;
        } else {
            rhs_map.insert({rhsKey, 1});
        }
    }
    inputFile.close();

    // Find how many times number on the LHS appears on the RHS and sum that number
    int sum = 0;
    for (int i = 0; i < MAX__LINES; i++) {
        if(auto value = rhs_map.find(lhs[i]); value != rhs_map.end()) {
            sum += value->second * lhs[i];
        }
    }
    printf("Result: %d\n", sum);
    return 0;
}
