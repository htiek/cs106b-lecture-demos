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
#include <vector>
#include <memory>
#include "GColorConsole.h"
#include "vector.h"
#include "gwindow.h"
#include "ginteractors.h"
#include "strlib.h"
using namespace std;

const int kColumnWidth = 13;

const double kWindowWidth = 1000;
const double kWindowHeight = 800;

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
void timeSortingAlgorithm(GColorConsole& console,
                          const SortingAlgorithm& alg,
                          const vector<ListGenerator>& generators,
                          const vector<int>& sizes) {
    console.doWithStyle("#000080", GColorConsole::BOLD, [&] {
        console << "Timing " << alg.name << "..." << endl;
    });

    /* Print out column headers */
    console << setw(kColumnWidth) << "Array Size";
    for (const auto& gen: generators) {
        console << setw(kColumnWidth) << gen.name;
    }
    console << endl;

    /* Print out results. */
    for (int size: sizes) {
        console << setw(kColumnWidth) << size << flush;

        for (const auto& gen: generators) {
            console << setw(kColumnWidth) << (to_string(timeFor(alg.fn, gen.fn(size))) + "ms") << flush;
        }
        console << endl;
    }

    console.doWithStyle("#000080", GColorConsole::BOLD, [&] {
        console << "All done!" << endl << endl;
    });
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

void merge(Container& result, const Container& lhs, const Container& rhs) {
    result.resize(lhs.size() + rhs.size());
    std::merge(lhs.begin(), lhs.end(), rhs.end(), rhs.end(), result.begin());
}

void splitSort(Container& v) {
    Container lhs, rhs;
    for (size_t i = 0; i < v.size(); i++) {
        if (i % 2 == 0) lhs.push_back(v[i]);
        else rhs.push_back(v[i]);
    }

    insertionSort(lhs);
    insertionSort(rhs);
    merge(v, lhs, rhs);
}

void doubleSplitSort(Container& v) {
    Container a, b, c, d;
    for (size_t i = 0; i < v.size(); i++) {
        if (i % 4 == 0) a.push_back(v[i]);
        else if (i % 4 == 1) b.push_back(v[i]);
        else if (i % 4 == 2) c.push_back(v[i]);
        else d.push_back(v[i]);
    }

    insertionSort(a);
    insertionSort(b);
    insertionSort(c);
    insertionSort(d);

    Container lhs, rhs;
    merge(lhs, a, b);
    merge(rhs, c, d);
    merge(v, lhs, rhs);
}

void mergesort(Container& v) {
    if (v.size() <= 1) return;

    Container lhs, rhs;
    for (size_t i = 0; i < v.size(); i++) {
        if (i % 2 == 0) lhs.push_back(v[i]);
        else rhs.push_back(v[i]);
    }

    mergesort(lhs);
    mergesort(rhs);
    merge(v, lhs, rhs);
}

void hybridMergesort(Container& v) {
    if (v.size() <= 16) {
        insertionSort(v);
        return;
    }

    Container lhs, rhs;
    for (size_t i = 0; i < v.size(); i++) {
        if (i % 2 == 0) lhs.push_back(v[i]);
        else rhs.push_back(v[i]);
    }

    hybridMergesort(lhs);
    hybridMergesort(rhs);
    merge(v, lhs, rhs);
}

void introsort(Container& v) {
    std::sort(v.begin(), v.end());
}

void heapsort(Container& v) {
    std::make_heap(v.begin(), v.end());
    std::sort_heap(v.begin(), v.end());
}

void timeSort(const string& name, function<void(Container&)> sort, GColorConsole& console, int multiplier) {
    timeSortingAlgorithm(console, { name, sort },
                         {
                             { "Ascending",  ascendingOrderSequence },
                             { "Descending", descendingOrderSequence },
                             { "Random",     randomOrderSequence}
                         },
                         {
                             10000 * multiplier,
                             20000 * multiplier,
                             30000 * multiplier,
                             40000 * multiplier,
                             50000 * multiplier,
                             60000 * multiplier,
                             70000 * multiplier,
                             80000 * multiplier,
                             90000 * multiplier,
                            100000 * multiplier
                         });
}

struct Graphics {
    GWindow window{kWindowWidth, kWindowHeight};
    GColorConsole* console;
    GTextField* input;
};

shared_ptr<Graphics> makeGraphics() {
    auto result = make_shared<Graphics>();
    result->window.setExitOnClose(true);

    result->input = new GTextField();
    result->window.addToRegion(new GLabel("Sorting algorithm: "), "SOUTH");
    result->window.addToRegion(result->input, "SOUTH");

    result->console = new GColorConsole();
    result->window.addToRegion(result->console, "CENTER");

    return result;
}

void handleEvent(GColorConsole& console, string command) {
    int multiplier = 1;
    size_t i;
    for (i = command.size(); i > 0 && command[i - 1] == '!'; i--) {
        multiplier *= 10;
    }
    command = string(command.begin(), command.begin() + i);

    if (command == "insertion sort") {
        timeSort("Insertion Sort", insertionSort, console, multiplier);
    } else if (command == "split sort") {
        timeSort("Split Sort", splitSort, console, multiplier);
    } else if (command == "double split sort") {
        timeSort("Double Split Sort", doubleSplitSort, console, multiplier);
    } else if (command == "merge sort" || command == "mergesort") {
        timeSort("Mergesort", mergesort, console, multiplier);
    } else if (command == "hybrid merge sort" || command == "hybrid mergesort") {
        timeSort("Hybrid Mergesort", hybridMergesort, console, multiplier);
    } else if (command == "heapsort" || command == "heap sort") {
        timeSort("Heapsort", heapsort, console, multiplier);
    } else if (command == "introsort") {
        timeSort("Introsort", hybridMergesort, console, multiplier);
    } else if (command == "bogosort") {
        console.doWithStyle("#800000", GColorConsole::ITALIC, [&] {
            console << "Yeah, not gonna do that." << endl;
        });
    } else {
        console.doWithStyle("#800000", GColorConsole::ITALIC, [&] {
            console << "I'm sorry, Keith. I'm afraid I can't do that." << endl;
        });
    }
}

int main() {
    auto graphics = makeGraphics();

    while (true) {
        GEvent e = waitForEvent();
        if (e.getEventClass() == ACTION_EVENT) {
            handleEvent(*graphics->console, toLowerCase(trim(graphics->input->getText())));
        }
    }
}
