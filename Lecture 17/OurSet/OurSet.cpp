#include "OurSet.h"
using namespace std;

const int kInitialBucketCount = 6; // Or really anything, really.
const double kMaxLoadFactor = 2.0; // Other values work too.

/********************************************
 * private:
 *    Vector<Vector<string>> buckets;
 *    HashFunction<string> hashFn;
 *    int numElems;
 */

OurSet::OurSet() {
    Vector<Vector<string>> ourBuckets(kInitialBucketCount);
    HashFunction<string>   ourHashFn(kInitialBucketCount);

    buckets = ourBuckets;
    hashFn  = ourHashFn;

    numElems = 0;
}

int OurSet::size() const {
    return numElems;
}

bool OurSet::isEmpty() const {
    return size() == 0;
}

bool OurSet::contains(const string& value) const {
    int bucket = hashFn(value);
    return buckets[bucket].contains(value);
}

void OurSet::add(const string& value) {
    if (contains(value)) return;

    int bucket = hashFn(value);
    buckets[bucket] += value;
    numElems++;

    double loadFactor = double(numElems) / buckets.size();
    if (loadFactor > kMaxLoadFactor) {
        rehash();
    }
}

void OurSet::rehash() {
    Vector<Vector<string>> newBuckets(buckets.size() * 2);
    HashFunction<string> newHashFn(newBuckets.size());

    for (int i = 0; i < buckets.size(); i++) {
        for (string elem: buckets[i]) {
            int newIndex = newHashFn(elem);
            newBuckets[newIndex] += elem;
        }
    }

    buckets = newBuckets;
    hashFn  = newHashFn;
}
















