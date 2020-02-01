#include "TimedFunctions.h"
#include <vector>
#include <numeric>
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>
using namespace std;

double averageOf(const vector<int>& vec) {
    double total = 0.0;

    for (size_t i = 0; i < vec.size(); i++) {
        total += vec[i];
    }

    return total / vec.size();
}

void printStars(int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << '*' << endl;
        }
    }
}

void hmmThatsStrange(int) {
    cout << "Mirth and Whimsy" << endl;
}

string flipFlop(const string& input) {
   int half = input.length() / 2;

   string left   = input.substr(0, half);
   string right  = input.substr(half);

   string flipped = right + left;

   return flipped;
}



/* Stuff to make the GUI work well with us. */
Timing::TimeTest makeAverageOfTest() {
    return {
        [] (size_t n, size_t, Timing::Timer& timer) {
            vector<int> values(n);

            timer.start();
            (void) averageOf(values);
            timer.stop();
        },
        Timing::linRange(10000000, 100000000, 5000000),
        { 1 },
        "averageOf"
    };
}

Timing::TimeTest makePrintStarsTest() {
    return {
        [] (size_t n, size_t, Timing::Timer& timer) {
            ostringstream buffer;
            auto oldBuf = cout.rdbuf(buffer.rdbuf());

            timer.start();
            printStars(n);
            timer.stop();

            cout.rdbuf(oldBuf);
        },
        Timing::linRange(1000, 10000, 500),
        { 1 },
        "printStars"
    };
}

Timing::TimeTest makeHmmThatsStrangeTest() {
    return {
        [] (size_t n, size_t, Timing::Timer& timer) {
            ostringstream buffer;
            auto oldBuf = cout.rdbuf(buffer.rdbuf());

            timer.start();
            hmmThatsStrange(n);
            timer.stop();

            cout.rdbuf(oldBuf);
        },
        Timing::linRange(100000, 1000000, 50000),
        { 1 },
        "hmmThatsStrange"
    };
}

volatile int dontOptimizeMeBro = 0;

Timing::TimeTest makeFlipFlopTest() {
    return {
        [] (size_t n, size_t, Timing::Timer& timer) {
            string str(n, ' ');
            generate(str.begin(), str.end(), rand);
            timer.start();
            string result = flipFlop(str);
            timer.stop();

            dontOptimizeMeBro += accumulate(result.begin(), result.end(), 0);
        },
        Timing::linRange(1000000, 8000000, 50000),
        { 1 },
        "flipFlop"
    };
}
