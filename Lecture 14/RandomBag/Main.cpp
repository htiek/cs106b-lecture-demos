#include <iostream>
#include "console.h"
#include "RandomBag.h"
using namespace std;

int main() {
    /* Some sample code using the RandomBag. */
    RandomBag bag;

    for (int i = 0; i < 10; i++) {
        bag.add(i);
    }

    for (int i = 0; i < 10; i++) {
        cout << bag.removeRandom() << " ";
    }

    return 0;
}
