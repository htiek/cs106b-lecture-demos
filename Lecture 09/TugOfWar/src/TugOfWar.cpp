/* File: TugOfWar.cpp
 *
 * Functions to divvy up a group of people into two closely-balanced groups.
 */
#include <iostream>
#include <string>
#include <cmath>
#include "set.h"
#include "vector.h"
#include "console.h"
using namespace std;

struct Person {
    string name;
    int    power;
};

/* This function is necessary to let us store a Person in a Set.
 *
 * Internally, the Set type requires that we can compare any two elements
 * using the < operator. Curious to learn more about how this works? Search
 * "operator overloading" or come talk to us after class!
 *
 * Curious why the Set requires this? Stay tuned - we'll talk about this
 * in the back half of the quarter!
 */
bool operator< (const Person& lhs, const Person& rhs) {
    if (lhs.name != rhs.name) return lhs.name < rhs.name;
    return lhs.power < rhs.power;
}

struct Teams {
    Set<Person> one;
    Set<Person> two;
};

/* These functions let us print Person and Teams objects to cout. */
ostream& operator<< (ostream& out, const Person& p) {
    return out << p.name << ": " << p.power;
}
ostream& operator<< (ostream& out, const Teams& t) {
    return out << t.one << " versus " << t.two;
}

int imbalanceOf(const Teams& teams) {
    int difference = 0;
    for (Person person: teams.one) difference += person.power;
    for (Person person: teams.two) difference -= person.power;

    return abs(difference);
}

Teams bestTeamsRec(const Set<Person>& remaining, const Teams& soFar) {
    if (remaining.isEmpty()) {
        return soFar;
    } else {
        auto person = remaining.first();

        /* Could put this person on Team 1. */
        auto bestOne = bestTeamsRec(remaining - person, { soFar.one + person, soFar.two });

        /* Could put this person on Team 2. */
        auto bestTwo = bestTeamsRec(remaining - person, { soFar.one, soFar.two + person });

        /* Return whichever is better! */
        return imbalanceOf(bestOne) < imbalanceOf(bestTwo)? bestOne : bestTwo;
    }
}

Teams bestTeams(const Set<Person>& people) {
    if (people.isEmpty()) {
        return {{}, {}};
    }
    return bestTeamsRec(people - people.first(), {{ people.first() }, {}});
}

int main() {
    Set<Person> people = {
        { "Kate",   250 },
        { "Keith",  300 },
        { "Trisha", 400 },
        { "Libby",  600 },
        { "A",  314 },
        { "B",  159 },
        { "C",  265 },
        { "D",  358 },
        { "E",  979 },
        { "F",  323 },
        { "G",  846 },
        { "H",  264 },
        { "J",  338 },
        { "K",  271 },
        { "L",  828 },
        { "M",  182 },
        { "N",  845 },
        { "O",  904 },
        { "P",  904 },
    };

    cout << bestTeams(people) << endl;

    return 0;
}
