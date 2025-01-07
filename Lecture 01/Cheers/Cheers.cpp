#include <iostream>
#include "console.h"
using namespace std;

/* This is where things begin! */
int main() {
    cheer(3);
    return 0;
}

void cheer(int numTimes) {
    for (int i = 0; i < numTimes; i++) {
        cout << "Hip hip, hooray!" << endl;
    }
}
