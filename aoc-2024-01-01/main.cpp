/*
 * Advent of Code Day 01
 * Part 01
 * Deepak Shenoy
 *
 */
#include <fstream>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <time.h>

#define FILENAME01 "../input.txt"
#define FILENAME02 "../test_data.txt"
#define MAX_LEVELS 64
#define MAX__LINES 1000

using namespace std;

// Quicksort algorithm modified from https://stackoverflow.com/questions/55008384/can-quicksort-be-implemented-in-c-without-stack-and-recursion
int quickSort(int *arr, size_t elements) {
    size_t beg[MAX_LEVELS] = { 0 }, end[MAX_LEVELS] = { 0 }, L, R;
    int i = 0;

    beg[0] = 0;
    end[0] = elements;
    while (i >= 0) {
        L = beg[i];
        R = end[i];
        if (L + 1 < R--) {
            int piv = arr[L];
            if (i == MAX_LEVELS - 1)
                return -1;
            while (L < R) {
                while (arr[R] >= piv && L < R)
                    R--;
                if (L < R)
                    arr[L++] = arr[R];
                while (arr[L] <= piv && L < R)
                    L++;
                if (L < R)
                    arr[R--] = arr[L];
            }
            arr[L] = piv;
            if (L - beg[i] > end[i] - R) {
                beg[i + 1] = L + 1;
                end[i + 1] = end[i];
                end[i++] = L;
            } else {
                beg[i + 1] = beg[i];
                end[i + 1] = L;
                beg[i++] = L + 1;
            }
        } else {
            i--;
        }
    }
    return 0;
}

// Read data
bool readFile(const string filename, int lhs[], int rhs[], const int maxLines) {
    fstream inputfile(filename);
    if(!inputfile.is_open()) {
        cerr << "Error opening file " << filename << endl;
        exit(1);
    }
    string line;
    for (int l = 0; l < maxLines; l++) {
        getline(inputfile, line);
        istringstream ss(line);
        ss >> lhs[l];
        ss >> rhs[l];
    }
    return true;
}

// Sum of differences
int sumOfDifferences(int lhs[], int rhs[], const int maxLines) {
    int sum = 0;
    for (int i; i < maxLines; i++) {
        sum += abs(lhs[i] - rhs[i]);
    }
    return sum;
}

int testsort(int *a, size_t size, const char *desc) {
    clock_t t = clock();
    size_t i;

    if (quickSort(a, size)) {
        printf("%s: quickSort failure\n", desc);
        return 1;
    }
    //for (i = 1; i < size; i++) printf("%d\n", a[i]);
    for (i = 1; i < size; i++) {
        if (a[i - 1] > a[i]) {
            printf("%s: sorting error: a[%zu]=%d > a[%zu]=%d\n",
                   desc, i - 1, a[i - 1], i, a[i]);
            return 2;
        }
    }
    t = clock() - t;
    printf("%s: %zu elements sorted in %.3fms\n",
           desc, size, t * 1000.0 / CLOCKS_PER_SEC);
    return 0;
}

int main(int argc, char *argv[]) {
    int l_side[MAX__LINES], r_side[MAX__LINES];
    readFile(FILENAME01, l_side, r_side, MAX__LINES);
    quickSort(l_side, MAX__LINES);
    quickSort(r_side, MAX__LINES);
    int result = sumOfDifferences(l_side, r_side, MAX__LINES);
    printf("Result: %d\n", result);
    return 0;


    size_t i, size = 1000000;
    // Allocate pointers corresponding to the size of the array of numbers
    int *a = (int*) malloc(sizeof(*a) * size);
    // Check that malloc was successful
    if (a != NULL) {
        for (i = 0; i < size; i++)
            a[i] = rand();
        testsort(a, size, "random");
        free(a);
    }
    return 0;
}
