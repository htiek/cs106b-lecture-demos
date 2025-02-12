/******************************************************************************
 * File: OurStack.h
 *
 * A class representing a stack that holds integers.
 */
#pragma once

class OurStack {
public:
    void push(int value);
    int  pop();        // Remove and return the top element of the stack.
    int  peek() const; // Look at - but don't remove - the top of the stack.

    int  size() const;
    bool isEmpty() const;

private:
    int* elems;         // Pointer to the array of elements
    int  allocatedSize; // How much space has been allocated
    int  logicalSize;   // How much space has been used
};










