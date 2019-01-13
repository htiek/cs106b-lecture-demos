/* File: CellTowers.cpp
 *
 * A program that determines the maximum population that can be covered
 * by purchasing cell towers with a single transmitting frequency.
 */
#include <iostream>
#include <algorithm>
#include "vector.h"
#include "console.h"
using namespace std;

/**
 * Given a list of cities, returns the total population of those
 * cities.
 *
 * @param populations The populations of the cities.
 * @return The total population.
 */
int populationOf(const Vector<int>& populations) {
    int result = 0;
    for (int cityPop: populations) {
        result += cityPop;
    }
    return result;
}

int main() {
    Vector<int> populations = { 137, 106, 107, 166, 103, 261, 109 };

    cout << "Total population is " << populationOf(populations) << endl;
    cout << "Best coverage is    " << bestCoverageFor(populations) << endl;

	return 0;
}


