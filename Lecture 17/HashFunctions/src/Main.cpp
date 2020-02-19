/*****************************************************
 * File: Main.cpp
 *
 * A program to play around with our new hash set!
 */
#include <iostream>
#include "HashFunction.h"
#include "vector.h"
#include "console.h"
#include "simpio.h"
using namespace std;

int main() {
    Vector<string> examRooms = {
        "Hewlett 200",
        "Cubberley Auditorium",
        "Dinkelspiel Auditorium",
        "Memorial Auditorium",
        "320-105",
        "Hewlett 201",
        "The CoHo"
    };

    HashFunction<string> hashFn(examRooms.size());

    while (true) {
        string name = getLine("Enter your name: ");
        int hashCode = hashFn(name);
        cout << "You'll take the exam in " << examRooms[hashCode] << endl;
    }

    return 0;
}
