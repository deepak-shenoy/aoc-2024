/*
* Advent of Code Day 09
 * Part 01
 * Deepak Shenoy
 *
 */

#include <iostream>
#include <fstream>
#include <string>

#define FILENAME01 "../input.txt"
#define FILENAME02 "../test_data.txt"

#define FREE_SPACE "."

using namespace std;

bool readFile(string fileName, string &line) {
    fstream inputFile(fileName);
    // Assume we just need to read one line for now
    getline(inputFile, line);
    return true;
}

class Block {
    public:
    vector<string> blockContents;
    bool freeSpace;
    int id;
    int pointer;
    Block *nextBlock;
    Block *prevBlock;
};

bool buildBlocks(string &line, Block **startBlock, Block **endBlock) {
    int id = 0;
    Block *newBlock;
    Block *previousBlock = new Block();
    *startBlock = previousBlock;
    for (unsigned int i = 0; i < line.size(); i++) {
        newBlock = new Block();
        newBlock->prevBlock = previousBlock;
        previousBlock->nextBlock = newBlock;
        previousBlock = newBlock;
        int sizeOfBlock = line[i] - '0';
        vector<string> blockContents;
        if (i%2==0) {
            // File contents
            newBlock->id = id;
            string idCode = to_string(id++);
            //char idLowerDigit = idCode[idCode.size()-1];
            blockContents = vector<string>(sizeOfBlock, idCode);
            newBlock->freeSpace = false;
            newBlock->pointer = blockContents.size() - 1;
        } else {
            newBlock->id = 0;
            blockContents = vector<string>(sizeOfBlock, FREE_SPACE);
            newBlock->freeSpace = true;
            newBlock->pointer = 0;
        }
        newBlock->blockContents.insert(newBlock->blockContents.end(), blockContents.begin(), blockContents.end());
    }
    *endBlock = newBlock;
    // Memory leak - clean up old space i.e. delete startBlock
    *startBlock = (*startBlock)->nextBlock;
    return true;
}

bool printAll(Block *startBlock, Block *endBlock) {
    while (startBlock != NULL) {
        for (vector<string>::iterator i = startBlock->blockContents.begin(); i != startBlock->blockContents.end(); i++) {
            printf("%s", i->c_str());
        }
        startBlock = startBlock->nextBlock;
    }
    printf("\n");
    return true;
}

bool compactSpace(Block *startBlock, Block *endBlock) {
    Block *current;
    Block *end;

    current = startBlock;
    end = endBlock;

    // Assume start is at the first free file space location and end
    // points to a file
    while (current != endBlock && current != NULL) {
        if (current->freeSpace == false || current->pointer == current->blockContents.size()) {
            current = current->nextBlock;
            continue;
        }
        if (end->freeSpace == true || end->pointer < 0) {
            end = end->prevBlock;
            continue;
        }

        current->blockContents[current->pointer] = end->blockContents[end->pointer];
        end->blockContents[end->pointer] = FREE_SPACE;
        current->pointer++;
        end->pointer--;
        // printAll(startBlock, endBlock);
        if (end->prevBlock == current && (current->pointer == current->blockContents.size() || end->pointer < 0)) break;
    }
    return true;
}

long calculateCheckSum(Block *startBlock) {
    long sum = 0;
    long blockPosition = 0;
    Block *current = startBlock;
    while (current != NULL) {
        for (vector<string>::iterator i = current->blockContents.begin(); i != current->blockContents.end(); i++) {
            if (i->compare(FREE_SPACE)==0) continue;
            sum += blockPosition * stol(*i);
            blockPosition++;
        }
        current = current->nextBlock;
    }
    return sum;
}

int main()
{
    string lineData;
    readFile(FILENAME01, lineData);
    Block *startBlock;
    Block *endBlock;
    buildBlocks(lineData, &startBlock, &endBlock);
    compactSpace(startBlock, endBlock);
    long result = calculateCheckSum(startBlock);
    printf("Result: %ld\n", result);
    //printAll(startBlock, endBlock);
    return 0;
}
