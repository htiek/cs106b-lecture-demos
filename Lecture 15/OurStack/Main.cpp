/******************************************************************************
 * File: Main.cpp
 *
 * A program to run simple tests on our custom Stack.
 */
#include <iostream>
#include "OurStack.h"
#include "console.h"
using namespace std;

const int kNumElems = 4;

int main() {
    OurStack stack;

    /* Load the stack with initial values. */
    for (int i = 0; i < kNumElems; i++) {
        stack.push(i);
    }

    /* Pop them off. */
    cout << "Popping values from the stack: " << endl;
    while (!stack.isEmpty()) {
        cout << "  " << stack.pop() << endl;
    }

    return 0;
}
