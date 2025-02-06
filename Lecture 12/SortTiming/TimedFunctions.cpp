#include "TimedFunctions.h"
#include <vector>
#include <numeric>
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <random>
using namespace std;

using Container = vector<int>;

/**
 * Given a vector and a starting point, returns the index of the smallest
 * element in that vector at or after the starting point
 *
 * @param elems The elements in question.
 * @param startPoint The starting index in the vector.
 * @return The index of the smallest element at or after that point
 */
size_t indexOfSmallest(const Container& elems, int startPoint) {
    size_t smallestIndex = startPoint;
    for (size_t i = startPoint + 1; i < elems.size(); i++) {
        if (elems[i] < elems[smallestIndex]) {
            smallestIndex = i;
        }
    }
    return smallestIndex;
}

/**
 * Sorts the specified vector using the selection sort algorithm.
 *
 * @param elems The elements to sort.
 */
void selectionSort(Container& elems) {
    for (size_t index = 0; index < elems.size(); index++) {
        size_t smallestIndex = indexOfSmallest(elems, index);
        swap(elems[index], elems[smallestIndex]);
    }
}

/**
 * Sorts the specified vector using insertion sort.
 *
 * @param v The vector to sort.
 */
void insertionSort(Container& v) {
    for (int i = 0; i < int(v.size()); i++) {
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
    int half = v.size() / 2;
    Container lhs(v.begin(), v.begin() + half);
    Container rhs(v.begin() + half, v.end());

    selectionSort(lhs);
    selectionSort(rhs);
    merge(v, lhs, rhs);
}

void doubleSplitSort(Container& v) {
    int quarter = v.size() / 4;

    Container a(v.begin(), v.begin() + quarter);
    Container b(v.begin() + quarter, v.begin() + 2 * quarter);
    Container c(v.begin() + 2 * quarter, v.begin() + 3 * quarter);
    Container d(v.begin() + 3 * quarter, v.end());
    selectionSort(a);
    selectionSort(b);
    selectionSort(c);
    selectionSort(d);

    Container lhs, rhs;
    merge(lhs, a, b);
    merge(rhs, c, d);
    merge(v, lhs, rhs);
}

void mergesort(Container& v) {
    if (v.size() <= 1) return;

    int half = v.size() / 2;
    Container lhs(v.begin(), v.begin() + half);
    Container rhs(v.begin() + half, v.end());

    mergesort(lhs);
    mergesort(rhs);
    merge(v, lhs, rhs);
}

void hybridMergesort(Container& v) {
    if (v.size() <= 16) {
        selectionSort(v);
        return;
    }

    int half = v.size() / 2;
    Container lhs(v.begin(), v.begin() + half);
    Container rhs(v.begin() + half, v.end());

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
    static random_device rd;
    static mt19937 generator;

    auto result = ascendingOrderSequence(length);
    shuffle(result.begin(), result.end(), generator);
    return result;
}

const size_t kBaseSize = 2000;

Timing::TimeTest timeSortingAlgorithm(const string& name,
                                      void sortAlgorithm(Container&),
                                      Container generatorFn(int length),
                                      size_t multiplier) {
    return {
        [=] (size_t n, size_t, Timing::Timer& timer) {
            Container seq = generatorFn(n);
            timer.start();
            sortAlgorithm(seq);
            timer.stop();
        },
        Timing::linRange(kBaseSize * multiplier, kBaseSize * 10 * multiplier, kBaseSize * multiplier),
        { 1 },
        name
    };
}

Timing::TimeTest timeSelectionSort() {
    return timeSortingAlgorithm("Selection Sort", selectionSort, randomOrderSequence, 1);
}
Timing::TimeTest timeInsertionSort() {
    return timeSortingAlgorithm("Insertion Sort", insertionSort, randomOrderSequence, 1);
}
Timing::TimeTest timeInsertionSortAscending() {
    return timeSortingAlgorithm("Insertion Sort", insertionSort, ascendingOrderSequence, 1);
}
Timing::TimeTest timeInsertionSortAscendingBang() {
    return timeSortingAlgorithm("Insertion Sort", insertionSort, ascendingOrderSequence, 10);
}
Timing::TimeTest timeInsertionSortAscendingBangBang() {
    return timeSortingAlgorithm("Insertion Sort", insertionSort, ascendingOrderSequence, 100);
}
Timing::TimeTest timeInsertionSortDescending() {
    return timeSortingAlgorithm("Insertion Sort", insertionSort, descendingOrderSequence, 1);
}
Timing::TimeTest timeSplitSort() {
    return timeSortingAlgorithm("\"Split Sort\"", splitSort, randomOrderSequence, 1);
}
Timing::TimeTest timeDoubleSplitSort() {
    return timeSortingAlgorithm("\"Double Split Sort\"", doubleSplitSort, randomOrderSequence, 1);
}
Timing::TimeTest timeMergesort() {
    return timeSortingAlgorithm("Mergesort", mergesort, randomOrderSequence, 1);
}
Timing::TimeTest timeMergesortBang() {
    return timeSortingAlgorithm("Mergesort", mergesort, randomOrderSequence, 10);
}
Timing::TimeTest timeMergesortBangBang() {
    return timeSortingAlgorithm("Mergesort", mergesort, randomOrderSequence, 100);
}
Timing::TimeTest timeHybridMergesort() {
    return timeSortingAlgorithm("Hybrid Mergesort", hybridMergesort, randomOrderSequence, 1);
}
Timing::TimeTest timeHybridMergesortBang() {
    return timeSortingAlgorithm("Hybrid Mergesort", hybridMergesort, randomOrderSequence, 10);
}
Timing::TimeTest timeHybridMergesortBangBang() {
    return timeSortingAlgorithm("Hybrid Mergesort", hybridMergesort, randomOrderSequence, 100);
}
