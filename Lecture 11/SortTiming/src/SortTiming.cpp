/* File: SortTiming.cpp
 *
 * A program to run sorting algorithms and see how long they take to finish on different
 * data sets.
 */
#include <iostream>
#include <string>
#include <chrono>
#include <functional>
#include <iomanip>   // For setw
#include <algorithm> // For swap
#include <numeric>
#include "console.h"
#include <vector>
#include "vector.h"
using namespace std;

const int kColumnWidth = 13;

using Container = vector<int>;

/* Type representing a function that, given a length, returns a list of values of that
 * length.
 */
struct ListGenerator {
    string name;                   // What it's called
    function<Container (int)> fn; // The actual generator
};

/* Type representing a sorting algorithm. */
struct SortingAlgorithm {
    string name;                      // What it's called
    function<void (Container&)> fn; // The actual sorting algorithm
};

/* Generates a sequence in ascending order. */
Container ascendingOrderSequence(int length) {
    Container result(length);
    iota(result.begin(), result.end(), 0);
    return result;
}
Container descendingOrderSequence(int length) {
    auto result = ascendingOrderSequence(length);
    reverse(result.begin(), result.end());
    return result;
}
Container randomOrderSequence(int length) {
    auto result = ascendingOrderSequence(length);
    random_shuffle(result.begin(), result.end());
    return result;
}

/* Runs the given sorting algorithm on the specified list, returning how long it took in ms. */
int timeFor(function<void (Container&)> sortAlg, Container values) {
    auto start = chrono::high_resolution_clock::now();
    sortAlg(values);
    auto elapsed = chrono::high_resolution_clock::now() - start;

    return chrono::duration_cast<chrono::milliseconds>(elapsed).count();
}

/* Times the given sorting algorithm on a cross of the given types of lists and numbers
 * of elements.
 */
void timeSortingAlgorithm(const SortingAlgorithm& alg,
                          const vector<ListGenerator>& generators,
                          const vector<int>& sizes) {
    cout << "=== Timing " << alg.name << " ===" << endl;

    /* Print out column headers */
    cout << setw(kColumnWidth) << "Array Size";
    for (const auto& gen: generators) {
        cout << setw(kColumnWidth) << gen.name;
    }
    cout << endl;

    /* Print out results. */
    for (int size: sizes) {
        cout << setw(kColumnWidth) << size << flush;

        for (const auto& gen: generators) {
            cout << setw(kColumnWidth) << (to_string(timeFor(alg.fn, gen.fn(size))) + "ms") << flush;
        }
        cout << endl;
    }
}


/**
 * Sorts the specified vector using insertion sort.
 *
 * @param v The vector to sort.
 */
void insertionSort(Container& v) {
  for (int i = 0; i < v.size(); i++) {
    /* Scan backwards until either (1) there is no
     * preceding element or the preceding element is
     * no bigger than us.
     */
    for (int j = i - 1; j >= 0; j--) {
      if (v[j] <= v[j + 1]) break;

      /* Swap this element back one step. */
      swap(v[j], v[j + 1]);
    }
  }
}

int main() {
    timeSortingAlgorithm({ "Insertion Sort", insertionSort },
                         {
                             { "Ascending",  ascendingOrderSequence },
                             { "Descending", descendingOrderSequence },
                             { "Random",     randomOrderSequence}
                         },
                         {
                             10000,
                             20000,
                             30000,
                             40000,
                             50000,
                             60000,
                             70000,
                             80000,
                             90000,
                            100000
                         });

    return 0;
}
