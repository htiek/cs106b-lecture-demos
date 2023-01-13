/* File: MaxOf.cpp
 *
 * A program showing off several ways to find the maximum element of a Vector.
 */
#include <iostream>
#include <algorithm>
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

int maxOf(const Vector<int>& elems) {
    /* Base Case: If the vector just has one element
     * in it, that element is the biggest element of
     * the vector.
     */
    if (elems.size() == 1) {
        return elems[0];
    }
    /* Recursive Case: If the vector has more than one
     * element, split the vector into two parts: the first
     * element, and everything else. The maximum is then
     * either (1) the first element or (2) the biggest
     * element in what remains.
     */
    else {
        int first = elems[0];
        Vector<int> rest = elems.subList(1);
        return max(first, maxOf(rest));
    }
}








