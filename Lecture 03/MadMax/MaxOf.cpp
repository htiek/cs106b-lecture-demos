/* File: MaxOf.cpp
 *
 * A program showing off several ways to find the maximum element of a Vector.
 */
#include <iostream>
#include <algorithm> // For C++'s max function
#include "vector.h"
#include "console.h"
using namespace std;

int maxOf(const Vector<int>& elems);

int main() {
    Vector<int> v = { 137, 106, 107, 166,
                      103, 261, 109 };
    cout << maxOf(v) << endl;
    return 0;
}

