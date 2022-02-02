#include <iostream>
#include "console.h"
#include "RandomBag.h"
using namespace std;

void printBagSize(const RandomBag& bag) {
    cout << "The bag has " << bag.size() << " elements in it." << endl;
}

int main() {
    /* Some sample code using the RandomBag. */
    RandomBag bag;

    for (int i = 0; i < 10; i++) {
        bag.add(i);
    }

    printBagSize(bag);

    while (!bag.isEmpty()) {
        cout << bag.removeRandom() << " ";
    }

    return 0;
}
