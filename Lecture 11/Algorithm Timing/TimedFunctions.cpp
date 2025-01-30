#include "TimedFunctions.h"
#include "vector.h"
#include <vector>
#include <numeric>
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <random>
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

void beni(int n) {
    for (int i = 0; i < 2 * n; i++) {
        for (int j = 0; j < 5 * n; j++) {
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

void pando(int n) {
    for (int i = 0; i < 3 * n; i++) {
        cout << "*" << endl;
    }
    for (int i = 0; i < 8; i++) {
        cout << "*" << endl;
    }
}

void printNumbers(int n) {
    Vector<int> numbers;
    for (int i = 0; i < n; i++) {
        numbers += i;
    }

    for (int i = 0; i < n; i++) {
        cout << numbers[0] << endl;
        numbers.remove(0); // Remove item at index 0
    }
}

void printNumbers2(int n) {
    Vector<int> numbers;
    for (int i = 0; i < n; i++) {
        numbers += i;
    }

    for (int i = 0; i < n; i++) {
        cout << numbers[0] << endl;
        numbers = numbers.subList(1);
    }
}

void printTrigrams_v1(const string& str) {
    for (int i = 0; i + 3 <= str.length(); i++) {
        string trigram = str.substr(i, 3);
        cout << trigram << endl;
    }
}

void printTrigrams_v2(const string& str) {
    string s = str;
    while (s.length() >= 3) {
        cout << s[0] << s[1] << s[2] << endl;
        s = s.substr(1);
    }
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
        Timing::linRange(10000000, 50000000, 5000000),
        { 1 },
        "averageOf"
    };
}

Timing::TimeTest makePandoTest() {
    return {
        [] (size_t n, size_t, Timing::Timer& timer) {
            ostringstream buffer;
            auto oldBuf = cout.rdbuf(buffer.rdbuf());

            timer.start();
            pando(n);
            timer.stop();

            cout.rdbuf(oldBuf);
        },
        Timing::linRange(1000000, 5000000, 500000),
        { 1 },
        "pando"
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
        Timing::linRange(1000, 5000, 500),
        { 1 },
        "printStars"
    };
}

Timing::TimeTest makeBeniTest() {
    return {
        [] (size_t n, size_t, Timing::Timer& timer) {
            ostringstream buffer;
            auto oldBuf = cout.rdbuf(buffer.rdbuf());

            timer.start();
            beni(n);
            timer.stop();

            cout.rdbuf(oldBuf);
        },
        Timing::linRange(250, 1250, 125),
        { 1 },
        "beni"
    };
}

Timing::TimeTest makePrintNumbersTest() {
    return {
        [] (size_t n, size_t, Timing::Timer& timer) {
            ostringstream buffer;
            auto oldBuf = cout.rdbuf(buffer.rdbuf());

            timer.start();
            printNumbers(n);
            timer.stop();

            cout.rdbuf(oldBuf);
        },
        Timing::linRange(1000, 10000, 500),
        { 1 },
        "printNumbers"
    };
}

Timing::TimeTest makePrintTrigramsV1Test() {
    return {
        [] (size_t n, size_t, Timing::Timer& timer) {
            ostringstream buffer;
            auto oldBuf = cout.rdbuf(buffer.rdbuf());

            string s(n, 0);
            mt19937 generator(137);
            generate_n(s.begin(), n, generator);

            timer.start();
            printTrigrams_v1(s);
            timer.stop();

            cout.rdbuf(oldBuf);
        },
        Timing::linRange(20000, 200000, 10000),
        { 1 },
        "printTrigrams_v1"
    };
}

Timing::TimeTest makePrintTrigramsV2Test() {
    return {
        [] (size_t n, size_t, Timing::Timer& timer) {
            ostringstream buffer;
            auto oldBuf = cout.rdbuf(buffer.rdbuf());

            string s(n, 0);
            mt19937 generator(137);
            generate_n(s.begin(), n, generator);

            timer.start();
            printTrigrams_v2(s);
            timer.stop();

            cout.rdbuf(oldBuf);
        },
        Timing::linRange(20000, 200000, 10000),
        { 1 },
        "printTrigrams_v2"
    };
}

Timing::TimeTest makePrintNumbers2Test() {
    return {
        [] (size_t n, size_t, Timing::Timer& timer) {
            ostringstream buffer;
            auto oldBuf = cout.rdbuf(buffer.rdbuf());

            timer.start();
            printNumbers2(n);
            timer.stop();

            cout.rdbuf(oldBuf);
        },
        Timing::linRange(1000, 10000, 500),
        { 1 },
        "printNumbers (v2)"
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
