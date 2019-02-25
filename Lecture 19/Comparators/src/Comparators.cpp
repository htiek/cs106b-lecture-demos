/*****************************************************
 * File: Comparators.cpp
 *
 * A program demonstrating custom comparators
 */
#include <iostream>
#include <string>
#include "set.h"
#include "simpio.h"
#include "console.h"
using namespace std;

struct Doctor {
    string name;
    int hoursFree;
};

struct Patient {
    string name;
    int hoursNeeded;
};

bool operator< (const Doctor& lhs, const Doctor& rhs) {
    if (lhs.name != rhs.name) return lhs.name < rhs.name;
    return lhs.hoursFree < rhs.hoursFree;
}

bool operator< (const Patient& lhs, const Patient& rhs) {
    if (lhs.name != rhs.name) return lhs.name < rhs.name;
    return lhs.hoursNeeded < rhs.hoursNeeded;
}

int main() {
    Doctor zhivago   = { "Dr. Zhivago",   8 };
    Doctor doolittle = { "Dr. Doolittle", 6 };
    Doctor acula     = { "Dr. Acula",     4 };

    Patient zero       = { "Patient Zero",         6 };
    Patient lyWaiting  = { "Patient Lee Waiting",  5 };
    Patient saVirtue   = { "Patient S. A. Virtue", 2 };
    Patient im         = { "Patient, Im",          2 };
    Patient compliance = { "Patient Compliance",   6 };

    Map<Doctor, Set<Patient>> schedule;
    schedule[zhivago]   = { zero, lyWaiting };
    schedule[doolittle] = { compliance };
    schedule[acula]     = { saVirtue, im };

    /* This program produces no output. It just shows that it compiles! */

    return 0;
}
