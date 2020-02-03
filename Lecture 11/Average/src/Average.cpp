#include "vector.h"
#include "random.h"
#include "console.h"
#include <iostream>
#include <ctime>
using namespace std;

double averageOf(const Vector<int>& vec) {
    double total = 0.0;

    for (int i = 0; i < vec.size(); i++) {
        total += vec[i];
    }

    return total / vec.size();
}

const int kNumValues = 100000000;

int main() {
    cout << "Filling vector..." << endl;
    Vector<int> values(kNumValues);
    for (int i = 0; i < kNumValues; i++) {
        values[i] = randomInteger(0, 10000);
    }


    cout << "Taking average..." << endl;
    clock_t start = clock();
    double result = averageOf(values);
    clock_t stop = clock();

    cout << "The averageOf function took " << (stop - start) / double(CLOCKS_PER_SEC) << "s to complete." << endl;
    cout << "The average was " << result << endl;
    return 0;
}
