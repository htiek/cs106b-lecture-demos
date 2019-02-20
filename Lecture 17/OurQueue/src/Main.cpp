/*****************************************************
 * File: Main.cpp
 *
 * A program to run simple tests on our custom Queue.
 */
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include "OurQueue.h"
#include "simpio.h"
#include "random.h"
#include "console.h"
using namespace std;

const int kNumElems = 8;

int main() {
    OurQueue queue;

    /* Load the queue with random values. */
    cout << "Enqueuing elements into the queue:" << endl;
    for (int i = 0; i < kNumElems; i++) {
        int value = randomInteger(0, 1000);
        cout << setw(6) << value;
        queue.enqueue(value);
    }
    cout << endl;

    /* See what those values are. */
    cout << "Dequeuing elements from the queue:" << endl;
    while (!queue.isEmpty()) {
        cout << setw(6) << queue.dequeue();
    }
    cout << endl;

    return 0;
}
