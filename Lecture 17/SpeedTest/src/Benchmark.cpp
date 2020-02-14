/*****************************************************
 * File: Benchmark.cpp
 *
 * A program to clock HashSet versus Set!
 */
#include <iostream>
#include <string>
#include <chrono>
#include "hashset.h"
#include "set.h"
#include "vector.h"
#include "console.h"
using namespace std;

Vector<int> randomPermutationOf(int n) {
    Vector<int> result;
    for (int i = 0; i < n; i++) {
        result += n;
    }

    /* Shuffle the vector using the Fisher-Yates shuffle. Take CS109 for details! */
    for (int i = 0; i < n; i++) {
        swap(result[i], result[randomInteger(i, n - 1)]);
    }

    return result;
}

static const int kMinSize  = 1000000;
static const int kStepSize = 1000000;
static const int kNumSteps = 10;

template <typename ContainerType> void speedTest(const string& type) {
    for (int i = 0; i < kNumSteps; i++) {
        int numElems = kMinSize + i * kStepSize;
        auto permutation = randomPermutationOf(numElems);

        auto startTime = chrono::system_clock::now();

        /* Create a new scope so that we time both the constructor and the destructor. */
        {
            ContainerType set;
            /* Add all the elements. */
            for (int elem: permutation) {
                set += elem;
            }

            /* Look each of them up. */
            for (int i = 0; i < numElems; i++) {
                (void) set.contains(i);
            }
        }

        auto elapsed  = chrono::system_clock::now() - startTime;
        cout << type << " with " << numElems << " elems: " <<  chrono::duration_cast<chrono::milliseconds>(elapsed).count() << "ms" << endl;
    }
}

int main() {
    speedTest<Set<int>>("Set<int>");
    speedTest<HashSet<int>>("HashSet<int>");
    return 0;
}
