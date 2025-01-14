/* File: PredictionTheThird.cpp
 *
 * What will this program print?
 */
#include <iostream>
#include "vector.h"
#include "console.h"
using namespace std;

void dream(Vector<int> numbers) {
    numbers[1] = 1963;
}

int main() {
    Vector<int> values = { 1929, 1955, 1964 };
    dream(values);
    cout << values << endl; // <-- Here
    return 0;
}















