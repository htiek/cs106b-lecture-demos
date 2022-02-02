#include "OurStack.h"
#include "error.h"

/* Constant controlling the default size of our stack. */
const int kInitialSize = 4;

OurStack::OurStack() {
    logicalSize = 0;
    elems = new int[kInitialSize];
    allocatedSize = kInitialSize;
}

OurStack::~OurStack() {
    delete[] elems;
}

void OurStack::push(int value) {
    if (logicalSize == allocatedSize) {
        error("The Digital Fire Marshal would object.");
    }

    elems[logicalSize] = value;
    logicalSize++;
}

int OurStack::peek() const {
    if (isEmpty()) {
        error("What is the sound of one hand clapping?");
    }

    return elems[logicalSize - 1];
}

int OurStack::pop() {
    int result = peek();
    logicalSize--;
    return result;
}

int OurStack::size() const {
    return logicalSize;
}

bool OurStack::isEmpty() const {
    return size() == 0;
}







