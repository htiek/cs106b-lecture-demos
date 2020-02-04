#include "TimedFunctions.h"
#include <vector>
#include <numeric>
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>
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
        Timing::linRange(kBaseSize * multiplier, kBaseSize * 10 * multiplier, kBaseSize / 2 * multiplier),
        { 1 },
        name
    };
}

auto timeSelectionSort() {
    return timeSortingAlgorithm("Selection Sort", selectionSort, randomOrderSequence, 1);
}
auto timeInsertionSort() {
    return timeSortingAlgorithm("Insertion Sort", insertionSort, randomOrderSequence, 1);
}
auto timeInsertionSortAscending() {
    return timeSortingAlgorithm("Insertion Sort", insertionSort, ascendingOrderSequence, 1);
}
auto timeInsertionSortDescending() {
    return timeSortingAlgorithm("Insertion Sort", insertionSort, descendingOrderSequence, 1);
}
auto timeSplitSort() {
    return timeSortingAlgorithm("\"Split Sort\"", splitSort, randomOrderSequence, 1);
}
auto timeDoubleSplitSort() {
    return timeSortingAlgorithm("\"Split Sort\"", doubleSplitSort, randomOrderSequence, 1);
}
auto timeMergesort() {
    return timeSortingAlgorithm("Mergesort", mergesort, randomOrderSequence, 1);
}
auto timeMergesortBang() {
    return timeSortingAlgorithm("Mergesort", mergesort, randomOrderSequence, 10);
}
auto timeMergesortBangBang() {
    return timeSortingAlgorithm("Mergesort", mergesort, randomOrderSequence, 100);
}
auto timeHybridMergesort() {
    return timeSortingAlgorithm("Mergesort", hybridMergesort, randomOrderSequence, 1);
}
auto timeHybridMergesortBang() {
    return timeSortingAlgorithm("Mergesort", hybridMergesort, randomOrderSequence, 10);
}
auto timeHybridMergesortBangBang() {
    return timeSortingAlgorithm("Mergesort", hybridMergesort, randomOrderSequence, 100);
}
